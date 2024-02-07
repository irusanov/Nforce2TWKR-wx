#ifndef NFORCE2TWKRMAIN_H
#define NFORCE2TWKRMAIN_H

/***************************************************************
 * Name:      Nforce2TWKRMain.h
 * Purpose:   Defines Application Frame
 * Author:    Ivan Rusanov (ivan.b.rusanov@gmail.com)
 * Created:   2024-01-24
 * Copyright: Ivan Rusanov (https://github.com/irusanov)
 * License:
 **************************************************************/

using namespace std;

#include <string>
#include "Constants.h"
#include "Types.h"
#include "utils/Utils.h"
#include "Cpu.h"
#include "version.h"
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/taskbar.h>
#include "AppSettings.h"
#include "utils/ProfilesManager.h"
#include "panels/DramPanel.h"
#include "panels/InfoPanel.h"
#include "panels/ChipsetPanel.h"

class Nforce2TWKRFrame: public wxFrame {
public:
    Nforce2TWKRFrame(wxWindow* parent, wxWindowID id = -1);
    virtual ~Nforce2TWKRFrame();

    HMODULE m_hOpenLibSys;
    wxIcon appIcon16x16;
    wxIcon appIcon48x48;
    wxIcon appIcon;
    Cpu* cpu;
    AppSettings settings;
    ProfilesManager profiles;

private:
    int currentPageIndex;

    //(Handlers(Nforce2TWKRFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnOpenSettings(wxCommandEvent& event);
    void OnButtonClick(wxCommandEvent& event);
    void OnRefreshButtonClick(wxCommandEvent& event);
    void OnApplyButtonClick(wxCommandEvent& event);
    void OnPageChanged(wxBookCtrlEvent& event);
    //)

    void RefreshTimings();

    //(Identifiers(Nforce2TWKRFrame)
    static const long MENU_QUIT_ID;
    static const long MENU_ABOUT_ID;
    static const long MENU_SETTINGS_ID;
    static const long STATUSBAR_ID;
    //)

    //(Declarations(Nforce2TWKRFrame)
    wxTaskBarIcon* trayIcon;
    wxStatusBar* statusBar;
    wxPanel* dramPanel;
    wxPanel* chipsetPanel;
    wxPanel* infoPanel;
    wxNotebook* mainTabs;
    TAdvancedEdit* advancedEdit;
    //)

    DECLARE_EVENT_TABLE()
};

#endif // NFORCE2TWKRMAIN_H

