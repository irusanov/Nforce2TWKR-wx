/***************************************************************
 * Name:      Nforce2TWKRApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Ivan Rusanov (ivan.b.rusanov@gmail.com)
 * Created:   2024-01-24
 * Copyright: Ivan Rusanov (https://github.com/irusanov)
 * License:
 **************************************************************/

#include "Nforce2TWKRApp.h"

//(AppHeaders
#include "Nforce2TWKRMain.h"
#include <wx/image.h>
//)

IMPLEMENT_APP(Nforce2TWKRApp);

bool Nforce2TWKRApp::OnInit() {
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if(wxsOK) {
        Nforce2TWKRFrame* Frame = new Nforce2TWKRFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    return wxsOK;
}
