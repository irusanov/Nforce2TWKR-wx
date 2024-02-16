// TAdvancedEdit.cpp

#include "components/TAdvancedEdit.h"

TAdvancedEdit::TAdvancedEdit(wxWindow* parent, const wxString& name, const wxString& value, const wxPoint& pos)
    : wxTextCtrl(parent, wxID_ANY, value, pos, wxSize(26, 21), (wxTE_CAPITALIZE | wxTE_CENTRE | wxTE_NO_VSCROLL | wxTE_DONTWRAP) & ~wxHSCROLL, wxDefaultValidator, name),
      isChanged(false),
      savedValue(value),
      initialBackgroundColor(GetBackgroundColour()) {

    SetMaxLength(2);
    SetMaxSize(wxSize(26, -1));
    SetMinSize(wxSize(26, -1));
    SetModified(false);

    Bind(wxEVT_TEXT, &TAdvancedEdit::OnTextChanged, this);
    Bind(wxEVT_KEY_DOWN, &TAdvancedEdit::OnKeyPress, this);
    Bind(wxEVT_KILL_FOCUS, &TAdvancedEdit::OnKillFocus, this);
    Bind(wxEVT_LEFT_UP, &TAdvancedEdit::OnClick, this);
}

void TAdvancedEdit::OnTextChanged(wxCommandEvent& event) {
    long insertionPoint = this->GetInsertionPoint();
    wxString newValue = event.GetString().Upper();
    isChanged = newValue != savedValue;
    ChangeValue(newValue);
    SetInsertionPoint(insertionPoint);

    if (isChanged) {
        SetOwnBackgroundColour(wxColor("#ffffcc"));
    } else {
        SetOwnBackgroundColour(initialBackgroundColor);
    }

    SetModified(isChanged);
}

void TAdvancedEdit::OnKeyPress(wxKeyEvent& event) {
    // Allowed key codes "abcdefABCDEF0123456789" and BACKSPACE
    int keyCode = event.GetKeyCode();

    // Use ASCII values directly for comparison
    if ((keyCode >= 48 && keyCode <= 57) ||        // '0' to '9'
        (keyCode >= 65 && keyCode <= 70) ||        // 'A' to 'F'
        (keyCode >= 97 && keyCode <= 102) ||       // 'a' to 'f'
        keyCode == WXK_BACK || keyCode == WXK_LEFT || keyCode == WXK_RIGHT) {
        event.Skip();
    } else {
        event.Skip(false);
    }
}

void TAdvancedEdit::SetValue(const wxString& value, bool resetIndex) {
    if (!value.IsEmpty()) {
        if (resetIndex) {
            savedValue = value;
            SetBackgroundColour(initialBackgroundColor);
        } else {
            SetBackgroundColour(wxColor("#ffffcc"));
        }

        isChanged = !resetIndex;
        SetModified(!resetIndex);
    }
    wxTextCtrl::SetValue(value);
}

void TAdvancedEdit::OnKillFocus(wxFocusEvent& event) {
    SetSelection(0, 0);
    event.Skip();
}

void TAdvancedEdit::OnClick(wxMouseEvent& event) {
    SelectAll();
    event.Skip();
}
