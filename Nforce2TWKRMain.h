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

class Nforce2TWKRFrame;

// System tray icon, shown only while the app is minimized to tray
class AppTrayIcon : public wxTaskBarIcon {
public:
    AppTrayIcon(Nforce2TWKRFrame* frame);

protected:
    virtual wxMenu* CreatePopupMenu();

private:
    Nforce2TWKRFrame* m_frame;

    void OnLeftDoubleClick(wxTaskBarIconEvent& event);
    void OnMenuShow(wxCommandEvent& event);
    void OnMenuExit(wxCommandEvent& event);
};

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

    void RestoreFromTray();

private:
    int currentPageIndex;

    //(Handlers(Nforce2TWKRFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnOpenSettings(wxCommandEvent& event);
    void OnRefreshButtonClick(wxCommandEvent& event);
    void OnProfileSaveMenuClick(wxCommandEvent& event);
    void OnProfileLoadMenuClick(wxCommandEvent& event);
    void OnBotMenuClick(wxCommandEvent& event);
    void OnApplyButtonClick(wxCommandEvent& event);
    void OnPageChanged(wxBookCtrlEvent& event);
    void OnIconize(wxIconizeEvent& event);
    void OnMove(wxMoveEvent& event);
    void OnClose(wxCloseEvent& event);
    //)

    void RefreshDramTimings();
    void RefreshChipsetTimings();
    void RestoreWindowPosition();
    void StoreWindowPosition();

    //(Identifiers(Nforce2TWKRFrame)
    static const long MENU_QUIT_ID;
    static const long MENU_ABOUT_ID;
    static const long MENU_SETTINGS_ID;
    static const long MENU_REFRESH_ID;
    static const long MENU_PROFILE_SAVE_ID;
    static const long MENU_PROFILE_LOAD_ID;
    static const long MENU_BOT_ID;
    static const long STATUSBAR_ID;
    //)

    //(Declarations(Nforce2TWKRFrame)
    AppTrayIcon* trayIcon;
    wxStatusBar* statusBar;
    wxPanel* dramPanel;
    ChipsetPanel* chipsetPanel;
    wxPanel* infoPanel;
    wxNotebook* mainTabs;
    TAdvancedEdit* advancedEdit;
    //)

    DECLARE_EVENT_TABLE()
};

#endif // NFORCE2TWKRMAIN_H

