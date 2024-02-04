#ifndef T_TIMING_COMBO_BOX_H
#define T_TIMING_COMBO_BOX_H

#include <wx/wx.h>
#include <wx/odcombo.h>

class TTimingComboBox : public wxOwnerDrawnComboBox {
public:
    TTimingComboBox(wxWindow* parent,
                    const wxString& name = wxTextCtrlNameStr,
                    const wxString& value = wxEmptyString,
                    const wxSize& size = wxDefaultSize,
                    const int min = 0,
                    const int max = 7,
                    const bool editable = true);

    void SetValue(int value);
    void SetItemValue(int value);
    void SetChanged();

private:
    wxColour originalBackground;

    int tMin;
    int tMax;
    int tValue;
    int tIndex;
    bool isChanged;
    bool isOpened;

    void CreateItems();
    // void OnDrawItem(wxDC& dc, const wxRect& rect, int item, int flags) const override;
    void OnDropDown(wxCommandEvent& event);
    void OnCloseUp(wxCommandEvent& event);
    void OnComboBox(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnTextCtrlClick(wxMouseEvent& event);

    // wxDECLARE_EVENT_TABLE();
};

#endif // T_TIMING_COMBO_BOX_H
