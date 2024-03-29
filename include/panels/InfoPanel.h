#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "wx/wx.h"
#include "Cpu.h"

#define INFO_PANEL_ROW_SPACING 2

class InfoPanel: public wxPanel {
public:
    InfoPanel(wxWindow* parent, Cpu* cpu);
    void Update();

private:
    Cpu* cpuReference;
    void AddControls();
    void Label(wxBoxSizer* sizer, wxWindow* parent, wxString label = wxEmptyString, int width = -1, bool expand = false);
};

#endif // INFOPANEL_H
