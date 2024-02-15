#ifndef T_TIMING_COMBO_BOX_H
#define T_TIMING_COMBO_BOX_H

#include <wx/wx.h>
#include <wx/odcombo.h>
#include "../../utils/Utils.h"

class TTimingComboBox : public wxOwnerDrawnComboBox {
public:
    TTimingComboBox(wxWindow* parent,
                    const wxString& name = wxTextCtrlNameStr,
                    const wxString& value = wxEmptyString,
                    const wxSize& size = wxDefaultSize,
                    const int min = 0,
                    const int max = 7,
                    const bool editable = true,
                    const wxArrayString& choices = wxArrayString(),
                    const bool isCustomValue = false);

    void SetValue(int value, bool resetIndex = true);
    int GetValue();
    bool IsChanged();
    bool IsCustomValue();

private:
    // Variables
    int tMin;
    int tMax;
    int savedIndex;
    bool tCustomValue;
    wxColour originalBackground;
    wxArrayString customItems;

    // Methods
    void CreateItems();

    // Handlers
    void OnDropDown(wxCommandEvent& event);
    void OnCloseUp(wxCommandEvent& event);
    void OnComboBox(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnTextCtrlClick(wxMouseEvent& event);

    // wxDECLARE_EVENT_TABLE();
};

#endif // T_TIMING_COMBO_BOX_H
