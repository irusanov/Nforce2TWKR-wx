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
#include <wx/intl.h>
#include <wx/string.h>
#include "ols/OlsApiInit.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format) {
    wxString wxbuild(wxVERSION_STRING);

    if(format == long_f) {
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

// IDs
const long Nforce2TWKRFrame::MENU_QUIT_ID = wxNewId();
const long Nforce2TWKRFrame::MENU_ABOUT_ID = wxNewId();
const long Nforce2TWKRFrame::STATUSBAR_ID = wxNewId();

// Static events, add menus here
BEGIN_EVENT_TABLE(Nforce2TWKRFrame, wxFrame)
    EVT_MENU(MENU_QUIT_ID, Nforce2TWKRFrame::OnQuit)
    EVT_MENU(MENU_ABOUT_ID, Nforce2TWKRFrame::OnAbout)
END_EVENT_TABLE()

Nforce2TWKRFrame::Nforce2TWKRFrame(wxWindow* parent, wxWindowID id) {
    if(!InitOpenLibSys(&m_hOpenLibSys)) {
        wxMessageBox(_T("Error initializing OpenLibSys"), _T("Error"), wxOK_DEFAULT | wxICON_ERROR);
        exit(-1);
    }

    if(GetDllStatus() != 0x0) {
        wxMessageBox(_T("Error loading WinRing.dll"), _T("Error"), wxOK_DEFAULT | wxICON_ERROR);
        exit(-1);
    }

    try {
        this->cpu = new Cpu();
    } catch (const char* s) {
        wxMessageBox(_T(s), _T("Error"), wxOK_DEFAULT | wxICON_ERROR);
        exit(-1);
    }

    // App icon
    Nforce2TWKRFrame::appIcon = wxIcon("MAINICON", wxBITMAP_TYPE_ICO_RESOURCE, -1, -1);
    Nforce2TWKRFrame::appIcon16x16 = wxIcon("MAINICON", wxBITMAP_TYPE_ICO_RESOURCE, 16, 16);
    Nforce2TWKRFrame::appIcon64x64 = wxIcon("MAINICON", wxBITMAP_TYPE_ICO_RESOURCE, 64, 64);
    // Create main frame and menu bar
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX), _T("id"));
    SetIcon(appIcon16x16);
    SetClientSize(wxSize(380, 480));
    SetTitle(_("NForce2 TWKR " + GetAppVersion()));
    this->Center(wxCENTER_ON_SCREEN);

    // MainPanel
    mainTabs = new wxNotebook(this, wxID_ANY);
    dramPanel = new wxPanel(mainTabs);
    chipsetPanel = new wxPanel(mainTabs);
    infoPanel = new wxPanel(mainTabs);
    mainTabs->AddPage(dramPanel, _T("DRAM"), true);
    mainTabs->AddPage(chipsetPanel, _T("Chipset"), false);
    mainTabs->AddPage(infoPanel, _T("Info"), false);

    wxStaticBox* timingsGroupBox = new wxStaticBox(dramPanel, wxID_ANY, "Timings", wxDefaultPosition, wxSize(70, -1));

    // MenuBar
    wxMenuBar* menuBar = new wxMenuBar();

    // File menu
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(wxID_ANY, _T("Open Profile\tCtrl+O"), _T("Open saved profile"));
    menuFile->Append(wxID_ANY, _T("Save Profile\tCtrl+S"), _T("Save current settings to a profile"));
    menuFile->Append(wxID_ANY, _T("Refresh\tF5"), _T("Reload settings"));
    menuFile->AppendSeparator();
    menuFile->Append(MENU_QUIT_ID, _T("Exit"), _T("Close the application"));
    menuBar->Append(menuFile, _T("&File"));

    // Tools menu
    wxMenu* menuTools = new wxMenu();
    menuTools->Append(new wxMenuItem(menuTools, wxID_ANY, _T("Options\tCtrl+P"), _T("Open settings dialog"), wxITEM_NORMAL));
    menuTools->Append(new wxMenuItem(menuTools, wxID_ANY, _T("Auto Validation Bot\tCtrl+B"), _T("Open Auto Validation Bot"), wxITEM_NORMAL));
    menuBar->Append(menuTools, _T("&Tools"));

    // Help menu
    wxMenu* menuHelp = new wxMenu();
    menuHelp->Append(new wxMenuItem(menuHelp, MENU_ABOUT_ID, _T("About\tF1"), _T("About the application"), wxITEM_NORMAL));
    menuBar->Append(menuHelp, _T("&Help"));

    SetMenuBar(menuBar);

    // Statusbar
    statusBar = new wxStatusBar(this, STATUSBAR_ID, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    statusBar->SetFieldsCount(1, __wxStatusBarWidths_1);
    statusBar->SetStatusStyles(1, __wxStatusBarStyles_1);
    SetStatusBar(statusBar);

    wxLogStatus(_T("OK"));
}

Nforce2TWKRFrame::~Nforce2TWKRFrame() {
    DeinitOpenLibSys(&m_hOpenLibSys);
}

void Nforce2TWKRFrame::OnQuit(wxCommandEvent& event) {
    Close();
}

void Nforce2TWKRFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
    wxAboutDialogInfo aboutInfo;
    aboutInfo.SetIcon(appIcon64x64);
    aboutInfo.SetName("NForce2 TWKR");
    aboutInfo.SetVersion(GetAppVersion());
    aboutInfo.SetDescription(wxString::Format("Build date: %s", GetBuildDate()));
    aboutInfo.SetCopyright("(C) 2019-2024 Ivan Rusanov");
    aboutInfo.SetWebSite("https://github.com/irusanov/Nforce2TWKR-wx");

    wxAboutBox(aboutInfo);
}
