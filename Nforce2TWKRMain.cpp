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
#include "dialogs/ProfilePreloadWindow.h"
#include "dialogs/ProfileSaveWindow.h"
#include "dialogs/SettingsWindow.h"
#include "dialogs/ValidationBotWindow.h"
#include "Registers.h"

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
const long Nforce2TWKRFrame::MENU_SETTINGS_ID = wxNewId();
const long Nforce2TWKRFrame::MENU_REFRESH_ID = wxNewId();
const long Nforce2TWKRFrame::MENU_PROFILE_SAVE_ID = wxNewId();
const long Nforce2TWKRFrame::MENU_PROFILE_LOAD_ID = wxNewId();
const long Nforce2TWKRFrame::MENU_BOT_ID = wxNewId();
const long Nforce2TWKRFrame::STATUSBAR_ID = wxNewId();

// Static events, add menus here
BEGIN_EVENT_TABLE(Nforce2TWKRFrame, wxFrame)
    EVT_MENU(MENU_QUIT_ID, Nforce2TWKRFrame::OnQuit)
    EVT_MENU(MENU_ABOUT_ID, Nforce2TWKRFrame::OnAbout)
    EVT_MENU(MENU_SETTINGS_ID, Nforce2TWKRFrame::OnOpenSettings)
    EVT_MENU(MENU_REFRESH_ID, Nforce2TWKRFrame::OnRefreshButtonClick)
    EVT_MENU(MENU_PROFILE_SAVE_ID, Nforce2TWKRFrame::OnProfileSaveMenuClick)
    EVT_MENU(MENU_PROFILE_LOAD_ID, Nforce2TWKRFrame::OnProfileLoadMenuClick)
    EVT_MENU(MENU_BOT_ID, Nforce2TWKRFrame::OnBotMenuClick)
    EVT_BUTTON(wxID_REFRESH, Nforce2TWKRFrame::OnRefreshButtonClick)
    EVT_BUTTON(wxID_APPLY, Nforce2TWKRFrame::OnApplyButtonClick)
    EVT_NOTEBOOK_PAGE_CHANGED(wxID_ANY, Nforce2TWKRFrame::OnPageChanged)
END_EVENT_TABLE()

Nforce2TWKRFrame::Nforce2TWKRFrame(wxWindow* parent, wxWindowID id): cpu(NULL), currentPageIndex(-1) {
    if(!InitOpenLibSys(&m_hOpenLibSys)) {
        wxMessageBox(_T("Error initializing OpenLibSys"), _T("Error"), wxOK_DEFAULT | wxICON_ERROR);
        exit(-1);
    }

    if(GetDllStatus() != 0x0) {
        wxMessageBox(_T("Error loading WinRing.dll"), _T("Error"), wxOK_DEFAULT | wxICON_ERROR);
        exit(-1);
    }

    try {
        cpu = new Cpu();
    } catch (const char* s) {
        wxMessageBox(_T(s), _T("Error"), wxOK_DEFAULT | wxICON_ERROR);
        exit(-1);
    }

    wxFont font = this->GetFont();
    font.SetFaceName(_T("Tahoma"));
    font.SetPointSize(8);
    this->SetFont(font);

    settings.Load();
    profiles.Init();

    // App icon
    Nforce2TWKRFrame::appIcon = wxIcon("MAINICON", wxBITMAP_TYPE_ICO_RESOURCE, -1, -1);
    Nforce2TWKRFrame::appIcon16x16 = wxIcon("MAINICON", wxBITMAP_TYPE_ICO_RESOURCE, 16, 16);
    Nforce2TWKRFrame::appIcon48x48 = wxIcon("MAINICON", wxBITMAP_TYPE_ICO_RESOURCE, 48, 48);

    trayIcon = new wxTaskBarIcon();
    trayIcon->SetIcon(appIcon);

    // Create main frame and menu bar
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX), _T("id"));
    SetIcon(appIcon16x16);
    //SetClientSize(wxSize(380, 478));
    SetMaxClientSize(wxSize(380, -1));
    SetTitle(_("NForce2 TWKR " + Utils::GetAppVersion()));
    Center(wxCENTER_ON_SCREEN);

    // MainPanel
    mainTabs = new wxNotebook(this, wxID_ANY);
    mainTabs->SetDoubleBuffered(true);

    wxColor bgColor = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);
    if (bgColor.IsOk()) {
        SetBackgroundColour(bgColor);
    }

    dramPanel = new DramPanel(mainTabs);
    chipsetPanel = new ChipsetPanel(mainTabs, cpu);
    infoPanel = new InfoPanel(mainTabs, cpu);

    mainTabs->AddPage(dramPanel, _T("DRAM"), true);
    mainTabs->AddPage(chipsetPanel, _T("Chipset"));
    mainTabs->AddPage(infoPanel, _T("Info"));

    // Set mainTabs as the main sizer for the frame
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(mainTabs, 1, wxEXPAND | wxALL, 1);

    // Buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->AddStretchSpacer();
    wxButton* refreshButton = new wxButton(this, wxID_REFRESH, "Refresh");
    buttonSizer->Add(refreshButton, 0, wxRIGHT | wxLEFT, 2);
    wxButton* applyButton = new wxButton(this, wxID_APPLY, "Apply");
    refreshButton->SetDefault();
    buttonSizer->Add(applyButton, 0);
    mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 2);

    // MenuBar
    wxMenuBar* menuBar = new wxMenuBar();

    // File menu
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(MENU_PROFILE_LOAD_ID, _T("Open Profile\tCtrl+O"), _T("Open saved profile"));
    menuFile->Append(MENU_PROFILE_SAVE_ID, _T("Save Profile\tCtrl+S"), _T("Save current settings to a profile"));
    menuFile->Append(MENU_REFRESH_ID, _T("Refresh\tF5"), _T("Reload settings"));
    menuFile->AppendSeparator();
    menuFile->Append(MENU_QUIT_ID, _T("Exit"), _T("Close the application"));
    menuBar->Append(menuFile, _T("&File"));

    // Tools menu
    wxMenu* menuTools = new wxMenu();
    menuTools->Append(new wxMenuItem(menuTools, MENU_SETTINGS_ID, _T("Options\tCtrl+P"), _T("Open settings dialog"), wxITEM_NORMAL));
    menuTools->Append(new wxMenuItem(menuTools, MENU_BOT_ID, _T("Auto Validation Bot\tCtrl+B"), _T("Open Auto Validation Bot"), wxITEM_NORMAL));
    menuBar->Append(menuTools, _T("&Tools"));

    // Help menu
    wxMenu* menuHelp = new wxMenu();
    menuHelp->Append(new wxMenuItem(menuHelp, MENU_ABOUT_ID, _T("About\tF1"), _T("About the application"), wxITEM_NORMAL));
    menuBar->Append(menuHelp, _T("&Help"));

    SetMenuBar(menuBar);

    // Statusbar
    /*
    statusBar = new wxStatusBar(this, STATUSBAR_ID, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    statusBar->SetFieldsCount(1, __wxStatusBarWidths_1);
    statusBar->SetStatusStyles(1, __wxStatusBarStyles_1);
    statusBar->SetDoubleBuffered(true);
    SetStatusBar(statusBar);
    */

    SetSizerAndFit(mainSizer);
    RefreshDramTimings();
    RefreshChipsetTimings();
    wxLogStatus(_T("OK"));
}

Nforce2TWKRFrame::~Nforce2TWKRFrame() {
    settings.Save();
    trayIcon->Destroy();
    delete cpu;
    DeinitOpenLibSys(&m_hOpenLibSys);
}

void Nforce2TWKRFrame::RefreshDramTimings() {
    Registers::ReadTimings(timingDefs, COUNT_OF(timingDefs));
    Registers::ReadTimings(doubledTimingDefs, COUNT_OF(doubledTimingDefs));
    Registers::ReadRomsipValues(romsipDefs, COUNT_OF(romsipDefs));
}

void Nforce2TWKRFrame::RefreshChipsetTimings() {
    Registers::ReadTimings(chipsetTimingDefs, COUNT_OF(chipsetTimingDefs));
    Registers::ReadTimings(s2kTimings, COUNT_OF(s2kTimings));
}

void Nforce2TWKRFrame::OnQuit(wxCommandEvent& event) {
    Close();
}

void Nforce2TWKRFrame::OnOpenSettings(wxCommandEvent& event) {
    SettingsWindow* settingsDialog = new SettingsWindow(this, _("Options"), settings);
    settingsDialog->ShowWindowModal();
}

void Nforce2TWKRFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
    wxAboutDialogInfo aboutInfo;
    aboutInfo.SetIcon(appIcon48x48);
    aboutInfo.SetName("NForce2 TWKR");
    aboutInfo.SetVersion(Utils::GetAppVersion());
    aboutInfo.SetDescription(wxString::Format("Build %s, %s", Utils::GetBuildCount(), Utils::GetBuildDate()));
    aboutInfo.SetCopyright("(C) 2021-2024 Ivan Rusanov");
    aboutInfo.SetWebSite("https://github.com/irusanov/Nforce2TWKR-wx");

    wxAboutBox(aboutInfo, this);
}

void Nforce2TWKRFrame::OnRefreshButtonClick(wxCommandEvent& event) {

    switch(currentPageIndex) {
    case 0:
        RefreshDramTimings();
        break;
    case 1:
        RefreshChipsetTimings();
        chipsetPanel->Update();
        break;
    case 2:
        infoPanel->Update();
        break;
    default:
        ;
    }
}

void Nforce2TWKRFrame::OnApplyButtonClick(wxCommandEvent& event) {
    if (currentPageIndex == 0) {
        Registers::WriteTimings(timingDefs, COUNT_OF(timingDefs), false);
        Registers::WriteTimings(doubledTimingDefs, COUNT_OF(doubledTimingDefs), true);
        Registers::WriteRomsipValues(romsipDefs, COUNT_OF(romsipDefs));
        Registers::WriteBurstMode(timingDefs, COUNT_OF(timingDefs));
        Registers::WriteDriveStrengthMode(timingDefs, COUNT_OF(timingDefs));
        RefreshDramTimings();
    }

    if (currentPageIndex == 1) {
        Registers::WriteTimings(chipsetTimingDefs, COUNT_OF(chipsetTimingDefs), false);
        Registers::WriteTimings(s2kTimings, COUNT_OF(s2kTimings), false);
        Registers::WriteBusDisconnect();
        cpu->WritePciFrequency(chipsetPanel->GetTargetPci() << 8 | 0xf);
        double targetFsb = chipsetPanel->GetTargetFsb();
        int targetPll = cpu->GetPll().GetPllFromFsb(targetFsb);
        if (targetFsb != 0 && targetPll != 0) {
            cpu->GetPll().nforce2_set_fsb_pll(targetFsb, targetPll);
        }
        RefreshChipsetTimings();
        chipsetPanel->Update();
    }
}

void Nforce2TWKRFrame::OnPageChanged(wxBookCtrlEvent& event) {
    currentPageIndex = event.GetSelection();

    if (currentPageIndex == 2) {
        infoPanel->Update();
    }
}

void Nforce2TWKRFrame::OnProfileSaveMenuClick(wxCommandEvent& event) {
    ProfileSaveWindow* profileDialog = new ProfileSaveWindow(this, profiles);
    profileDialog->ShowWindowModal();
}

void Nforce2TWKRFrame::OnProfileLoadMenuClick(wxCommandEvent& event) {
    ProfilePreloadWindow* profileDialog = new ProfilePreloadWindow(this, profiles);
    profileDialog->ShowWindowModal();
}

void Nforce2TWKRFrame::OnBotMenuClick(wxCommandEvent& event) {
    ValidationBotDialog* botDialog = new ValidationBotDialog(this, "Auto Validation Bot", settings);
    botDialog->Show();
}
