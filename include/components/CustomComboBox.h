#ifndef CUSTOM_COMBO_BOX_H
#define CUSTOM_COMBO_BOX_H

#include <wx/wx.h>
#include <wx/combo.h>

class CustomComboBox : public wxComboBox {
public:
    CustomComboBox(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString,
                   const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
                   const wxArrayString& choices = wxArrayString(), long style = 0,
                   const wxValidator& validator = wxDefaultValidator,
                   const wxString& name = wxTextCtrlNameStr);

private:
    wxColour originalBackground;
    bool isDropdownOpen;

    void OnComboBox(wxCommandEvent& event);
    void OnDropDown(wxCommandEvent& event);
    void OnCloseUp(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnFocus(wxFocusEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // CUSTOM_COMBO_BOX_H
