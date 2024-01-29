#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "wx/wx.h"
#include "Cpu.h"

#define INFO_PANEL_ROW_SPACING 2

class InfoPanel: public wxPanel
{
public:
    InfoPanel(wxWindow* parent, Cpu* cpu);

private:
    Cpu* cpuReference;
    void AddControls();
    void Label(wxBoxSizer* sizer, wxWindow* parent, wxString label, int width, bool expand);
    void TextBox(wxBoxSizer* sizer, wxWindow* parent, wxString value, int width, bool expand);
    void OnSetFocus(wxFocusEvent& event);
};

#endif // INFOPANEL_H
