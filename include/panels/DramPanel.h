#ifndef DRAMPANEL_H
#define DRAMPANEL_H

#include <vector>
#include <utility>
#include <wx/wx.h>
#include <wx/statbox.h>
#include "Types.h"
#include "components/CustomComboBox.h"
#include "components/TAdvancedEdit.h"
#include "components/TTimingComboBox.h"

class DramPanel : public wxPanel {
public:
    DramPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL,
              const wxString& name = wxPanelNameStr);

private:
    void AddControls();
    void CreateLeftStaticBox(wxSizer* dramPanelSizer);
    void CreateRightStaticBoxes(wxSizer* dramPanelSizer);
    //std::vector<control_def_t> controls;
};

#endif // DRAMPANEL_H
