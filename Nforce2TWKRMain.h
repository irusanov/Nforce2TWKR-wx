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
//(*Headers(Nforce2TWKRFrame)
#include "utils/Utils.h"
#include "utils/Nforce2Pll.h"
#include "utils/QueryPerformance.h"
#include "utils/CPUDetection.h"
#include "Constants.h"
#include "version.h"
#include <wx/wx.h>
#include <string>
//*)

class Nforce2TWKRFrame: public wxFrame
{
    public:

        // MANID Register, MSR C001_001Eh
        typedef struct {
            unsigned char reticleSite; // [9-8]
            unsigned char majorRev; // [7-4]
            unsigned char minorRev; // [3-0]
        } man_id_t;

        typedef struct {
            unsigned int cpuid;
            string codeName;
            string cpuName;
            unsigned char family;
            unsigned char model;
            unsigned char extFamily;
            unsigned char extModel;
            unsigned char stepping;
            unsigned char patchLevel;
            double frequency;
            double fsbFromPll;
            double fsb;
            double multi;
            double dram;
            unsigned int pciMul;
            unsigned int pciDiv;
            unsigned char fsbDiv;
            unsigned char dramDiv;
            unsigned int maxVid;
            unsigned int startVid;
            unsigned int currVid;
            unsigned int maxFid;
            unsigned int startFid;
            unsigned int currFid;
            unsigned int fid;
            bool MP;
            int l1DataCache;
            int l1InstCache;
            int l1Cache;
            int l2Cache;
            man_id_t manID;
        } cpu_info_t;

        Nforce2TWKRFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Nforce2TWKRFrame();
        Nforce2Pll pll;
        cpu_info_t cpu_info;
        QueryPerformance qpc;

    private:

        //(*Handlers(Nforce2TWKRFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(Nforce2TWKRFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        bool __fastcall InitSystemInfo();

        //(*Declarations(Nforce2TWKRFrame)
        wxStatusBar* statusBar;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // NFORCE2TWKRMAIN_H

