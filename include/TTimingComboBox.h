#ifndef T_TIMING_COMBO_BOX_H
#define T_TIMING_COMBO_BOX_H

#include <wx/wx.h>
#include <wx/odcombo.h>

class TTimingComboBox : public wxOwnerDrawnComboBox
{
public:
    TTimingComboBox(wxWindow* parent,
                    wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    const wxArrayString& choices = wxArrayString(),
                    long style = 0,
                    const wxValidator& validator = wxDefaultValidator,
                    const wxString& name = "TTimingComboBox");


    void SetValue(int value);
    void SetItemValue(int value);
    void SetChanged();

private:
    wxColour originalBackground;

    int tMin = 0; // Replace tMin and tMax with your actual minimum and maximum values
    int tMax = 10; // Replace tMin and tMax with your actual minimum and maximum values

    int tValue;
    int tIndex;
    bool tChanged;

    void CreateItems();
    // void OnDrawItem(wxDC& dc, const wxRect& rect, int item, int flags) const override;
    void OnDropDown(wxCommandEvent& event);
    void OnCloseUp(wxCommandEvent& event);
    void OnComboBox(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);

    // wxDECLARE_EVENT_TABLE();
};

#endif // T_TIMING_COMBO_BOX_H
