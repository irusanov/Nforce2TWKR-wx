#ifndef T_ADVANCED_EDIT_H
#define T_ADVANCED_EDIT_H

#pragma once

#include <wx/wx.h>

class TAdvancedEdit : public wxTextCtrl {
public:
    TAdvancedEdit(wxWindow* parent,
                  const wxString& name = wxTextCtrlNameStr,
                  const wxString& value = wxEmptyString,
                  const wxPoint& pos = wxDefaultPosition);

    void SetValue(const wxString& value) override;
    bool isChanged;

private:
    wxString savedValue;
    wxColor initialBackgroundColor;
    void OnTextChanged(wxCommandEvent& event);
    void OnKeyPress(wxKeyEvent& event);
    void OnKillFocus(wxFocusEvent& event);
    void OnClick(wxMouseEvent& event);
};

#endif // T_ADVANCED_EDIT_H

