#include "components/TReadonlyTextBox.h"

TReadonlyTextBox::TReadonlyTextBox(wxWindow* parent, const wxString value, int width, const wxString name)
    : wxTextCtrl(parent, wxID_ANY, value, wxDefaultPosition, wxSize(width, 18),
                 wxTE_READONLY | wxTE_CENTER | wxBORDER_STATIC, wxDefaultValidator, name) {

    this->Bind(wxEVT_SET_FOCUS, &TReadonlyTextBox::OnSetFocus, this);
    this->SetCursor(wxCursor(wxCURSOR_DEFAULT));
    this->SetForegroundColour(wxColour(0, 0, 128));
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
}

void TReadonlyTextBox::OnSetFocus(wxFocusEvent& event) {
    // Prevent the control from getting focus
    event.Skip(false);
}
