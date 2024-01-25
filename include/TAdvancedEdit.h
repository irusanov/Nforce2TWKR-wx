#ifndef TADVANCEDEDIT_H
#define TADVANCEDEDIT_H

#pragma once

#include <wx/wx.h>

class TAdvancedEdit : public wxTextCtrl {
public:
    TAdvancedEdit(wxWindow* parent, wxWindowID id = wxID_ANY,
                  const wxString& value = wxEmptyString,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxString& name = wxTextCtrlNameStr);
    void SetValue(const wxString& value) override;

protected:
    bool isChanged;

private:
    wxString savedValue;
    wxColor initialBackgroundColor;
    void OnTextChanged(wxCommandEvent& event);
    void OnKeyPress(wxKeyEvent& event);
    void OnKillFocus(wxFocusEvent& event);
    void OnClick(wxMouseEvent& event);
};

#endif // TADVANCEDEDIT_H

