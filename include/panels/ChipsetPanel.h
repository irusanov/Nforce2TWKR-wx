#ifndef CHIPSET_H
#define CHIPSET_H

#include "wx/wx.h"

#define CHIPSET_PANEL_ROW_SPACING 2

class ChipsetPanel: public wxPanel {
public:
    ChipsetPanel(wxWindow* parent);

private:
    void AddControls();
};

#endif // CHIPSET_H

