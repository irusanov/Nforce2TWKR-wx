#ifndef T_TIMING_COMBO_BOX_H
#define T_TIMING_COMBO_BOX_H

#include <wx/wx.h>
#include <wx/odcombo.h>

class TTimingComboBox : public wxOwnerDrawnComboBox
{
public:
    TTimingComboBox(wxWindow* parent,
                  const wxString& name = wxTextCtrlNameStr,
                  const wxString& value = wxEmptyString,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  const int min = 0,
                  const int max = 7);

    void SetValue(int value);
    void SetItemValue(int value);
    void SetChanged();

private:
    wxColour originalBackground;

    bool isChanged;
    int tMin;
    int tMax;

    int tValue;
    int tIndex;

    void CreateItems();
    // void OnDrawItem(wxDC& dc, const wxRect& rect, int item, int flags) const override;
    void OnDropDown(wxCommandEvent& event);
    void OnCloseUp(wxCommandEvent& event);
    void OnComboBox(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);

    // wxDECLARE_EVENT_TABLE();
};

#endif // T_TIMING_COMBO_BOX_H
