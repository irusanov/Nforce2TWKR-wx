#ifndef DRAMPANEL_H
#define DRAMPANEL_H

#include <wx/wx.h>
#include <wx/statbox.h>
#include "TTimingComboBox.h"
#include "CustomComboBox.h"
#include "TAdvancedEdit.h"

class DramPanel : public wxPanel
{
public:
    DramPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL,
              const wxString& name = wxPanelNameStr);

private:
    void AddControls();
    void CreateLeftStaticBox(wxSizer* dramPanelSizer);
    void CreateRightStaticBoxes(wxSizer* dramPanelSizer);
};

#endif // DRAMPANEL_H
