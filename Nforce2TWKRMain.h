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
#include "utils/Nforce2Pll.h"
#include "utils/QueryPerformance.h"
#include "Cpu.h"
#include "version.h"
#include <wx/wx.h>
#include <wx/notebook.h>

class Nforce2TWKRFrame: public wxFrame {
public:
    Nforce2TWKRFrame(wxWindow* parent, wxWindowID id = -1);
    virtual ~Nforce2TWKRFrame();

    HMODULE m_hOpenLibSys;
    wxIcon appIcon16x16;
    wxIcon appIcon64x64;
    wxIcon appIcon;
    Cpu* cpu;
    Nforce2Pll pll;
    QueryPerformance qpc;

private:

    //(Handlers(Nforce2TWKRFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    //)

    //(Identifiers(Nforce2TWKRFrame)
    static const long MENU_QUIT_ID;
    static const long MENU_ABOUT_ID;
    static const long STATUSBAR_ID;
    //)

    bool __fastcall InitSystemInfo();

    //(Declarations(Nforce2TWKRFrame)
    wxStatusBar* statusBar;
    wxPanel* dramPanel;
    wxPanel* chipsetPanel;
    wxPanel* infoPanel;
    wxNotebook* mainTabs;
    //)

    DECLARE_EVENT_TABLE()
};

#endif // NFORCE2TWKRMAIN_H

