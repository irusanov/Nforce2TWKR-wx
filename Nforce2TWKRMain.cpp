/***************************************************************
 * Name:      Nforce2TWKRMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Ivan Rusanov (ivan.b.rusanov@gmail.com)
 * Created:   2024-01-24
 * Copyright: Ivan Rusanov (https://github.com/irusanov)
 * License:
 **************************************************************/

#include <windows.h>
#include "Nforce2TWKRMain.h"
#include <wx/aboutdlg.h>

//(*InternalHeaders(Nforce2TWKRFrame)
#include <wx/intl.h>
#include <wx/string.h>
#include "libs/OlsApiInit.h"
//*)

HMODULE m_hOpenLibSys = NULL;
wxIcon appIcon16x16 = NULL;
wxIcon appIcon = NULL;

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(Nforce2TWKRFrame)
const long Nforce2TWKRFrame::idMenuQuit = wxNewId();
const long Nforce2TWKRFrame::idMenuAbout = wxNewId();
const long Nforce2TWKRFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Nforce2TWKRFrame,wxFrame)
    //(*EventTable(Nforce2TWKRFrame)
    //*)
END_EVENT_TABLE()

Nforce2TWKRFrame::Nforce2TWKRFrame(wxWindow* parent,wxWindowID id)
{
    //(Initialize(Nforce2TWKRFrame)
    if (!InitOpenLibSys(&m_hOpenLibSys)) {
        wxMessageBox(_T("Error initializing OpenLibSys"), _T("Error"), wxOK_DEFAULT | wxICON_ERROR);
        exit(-1);
    }

    if (GetDllStatus() != 0x0) {
        wxMessageBox(_T("Error loading WinRing.dll"), _T("Error"), wxOK_DEFAULT | wxICON_ERROR);
        exit(-1);
    }

    if (!pll.init()) {
        wxMessageBox(_T("Not a NForce2 chipset!"), _T("Error"), wxOK_DEFAULT | wxICON_ERROR);
        exit(-1);
    }

    // MenuBar
    wxMenuBar* menuBar = new wxMenuBar();

    // App icon
    appIcon = wxIcon("MAINICON", wxBITMAP_TYPE_ICO_RESOURCE, -1, -1);
    appIcon16x16 = wxIcon("MAINICON", wxBITMAP_TYPE_ICO_RESOURCE, 16, 16);
    // Create main frame and menu bar
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetIcon(appIcon16x16);

    // File menu
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(wxID_ANY, _T("Open Profile\tCtrl+O"), _T("Open saved profile"));
    menuFile->Append(wxID_ANY, _T("Save Profile\tCtrl+S"), _T("Save current settings to a profile"));
    menuFile->Append(wxID_ANY, _T("Refresh\tF5"), _T("Reload settings"));
    menuFile->AppendSeparator();
    menuFile->Append(idMenuQuit, _T("Exit"), _T("Close the application"));
    menuBar->Append(menuFile, _T("&File"));

    // Tools menu
    wxMenu* menuTools = new wxMenu();
    menuTools->Append(new wxMenuItem(menuTools, wxID_ANY, _T("Options\tCtrl+P"), _T("Open settings dialog"), wxITEM_NORMAL));
    menuTools->Append(new wxMenuItem(menuTools, wxID_ANY, _T("Auto Validation Bot\tCtrl+B"), _T("Open Auto Validation Bot"), wxITEM_NORMAL));
    menuBar->Append(menuTools, _T("&Tools"));

    // Help menu
    wxMenu* menuHelp = new wxMenu();
    menuHelp->Append(new wxMenuItem(menuHelp, idMenuAbout, _T("About\tF1"), _T("About the application"), wxITEM_NORMAL));
    menuBar->Append(menuHelp, _T("&Help"));

    SetMenuBar(menuBar);

    // Statusbar
    statusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    statusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    statusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(statusBar);

    Bind(wxEVT_MENU, &Nforce2TWKRFrame::OnQuit, this, idMenuQuit);
    Bind(wxEVT_MENU, &Nforce2TWKRFrame::OnAbout, this, idMenuAbout);

    InitSystemInfo();
    //)
}

Nforce2TWKRFrame::~Nforce2TWKRFrame()
{
    //(*Destroy(Nforce2TWKRFrame)
       DeinitOpenLibSys(&m_hOpenLibSys);
    //*)
}

// Read CPU and system info, invoked once
bool __fastcall Nforce2TWKRFrame::InitSystemInfo() {
    unsigned long eax = 0, ebx = 0, ecx = 0, edx = 0;

    // CPUID information
    if (Cpuid(0x00000001, &eax, &ebx, &ecx, &edx)) {
        cpu_info.cpuid = eax;
        cpu_info.stepping = eax & 0xf;
        cpu_info.family = eax >> 8 & 0xf;
        cpu_info.model = eax >> 4 & 0xf;
    }
    else {
        return false;
    }

    // Extended CPUID information
    if (Cpuid(0x80000001, &eax, &ebx, &ecx, &edx)) {
        cpu_info.extFamily = eax >> 8 & 0xf;
        cpu_info.extModel = eax >> 4 & 0xf;
        cpu_info.MP = edx >> FEATURE_K7_ECC_BIT & 1;
    }
    else {
        return false;
    }

    // L1 Data cache
    if (Cpuid(0x80000005, &eax, &ebx, &ecx, &edx)) {
        cpu_info.l1DataCache = (ecx >> 24 & 0xff);
        cpu_info.l1InstCache = (edx >> 24 & 0xff);
        cpu_info.l1Cache = cpu_info.l1DataCache + cpu_info.l1InstCache;
    }

    // L2 cache
    if (Cpuid(0x80000006, &eax, &ebx, &ecx, &edx)) {
        cpu_info.l2Cache = (ecx >> 16 & 0xffff);
    }

    if (Rdmsr(MSR_K7_MANID, &eax, &edx)) {
        cpu_info.manID.minorRev = GetBits(eax, 0, 4);
        cpu_info.manID.majorRev = GetBits(eax, 4, 4);
        cpu_info.manID.reticleSite = GetBits(eax, 8, 2);
    }

    // Read CPU FID and VID values
    if (Rdmsr(MSR_K7_FID_VID_STATUS, &eax, &edx)) {
        cpu_info.currVid = GetBits(edx, 0, 6);
        cpu_info.startVid = GetBits(edx, 8, 6);
        cpu_info.maxVid = GetBits(edx, 16, 6);

        cpu_info.currFid = GetBits(eax, 0, 6);
        cpu_info.startFid = GetBits(eax, 8, 6);
        cpu_info.maxFid = GetBits(eax, 16, 6);
    }

    cpu_info.cpuName = GetCpuName();
    decode_amd_model_string(cpu_info.cpuName);
    // decode_amd_model_string("Athlon XP-M");

    // @TODO: Implement RefreshCpuSpeed
    //RefreshCpuSpeed();

    switch (cpu_info.cpuid) {
    default: ;
    }

    return true;
}

void Nforce2TWKRFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Nforce2TWKRFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo aboutInfo;
    aboutInfo.SetIcon(appIcon);
    aboutInfo.SetName("NForce2 TWKR");
    wxString versionString = wxString::Format(wxT("%d"), (int)AutoVersion::MAJOR) + "." + wxString::Format(wxT("%d"), (int)AutoVersion::MINOR) + "." + wxString::Format(wxT("%d"), (int)AutoVersion::BUILD);
    aboutInfo.SetVersion(versionString);
    aboutInfo.SetDescription(_("A new generation tweaker for\n NVidia nForce2 motherboards."));
    aboutInfo.SetCopyright("(C) 2019-2024 Ivan Rusanov");
    aboutInfo.SetWebSite("https://github.com/irusanov/Nforce2TWKR-wx");

    wxAboutBox(aboutInfo);
}
