#ifndef T_READONLY_TEXT_BOX_H
#define T_READONLY_TEXT_BOX_H

#pragma once

#include <wx/wx.h>

class TReadonlyTextBox : public wxTextCtrl {
public:
    TReadonlyTextBox(wxWindow* parent, const wxString value = wxEmptyString, int width = -1, const wxString name = wxTextCtrlNameStr);

    // void SetValue(const wxString& value) override;

protected:

private:
    void OnSetFocus(wxFocusEvent& event);
};

#endif // T_READONLY_TEXT_BOX_H
