#include "components/CustomComboBox.h"

CustomComboBox::CustomComboBox(wxWindow* parent, wxWindowID id, const wxString& value,
                               const wxPoint& pos, const wxSize& size,
                               const wxArrayString& choices, long style,
                               const wxValidator& validator, const wxString& name)
    : wxComboBox(parent, id, value, pos, size, choices, style, validator, name),
    isDropdownOpen(false)
{
    SetEditable(false);
    SetCursor(wxCursor(wxCURSOR_DEFAULT));
    Enable(false);

    // Bind events
    Bind(wxEVT_COMBOBOX, &CustomComboBox::OnComboBox, this);
    Bind(wxEVT_COMBOBOX_DROPDOWN, &CustomComboBox::OnDropDown, this);
    Bind(wxEVT_COMBOBOX_CLOSEUP, &CustomComboBox::OnCloseUp, this);

    // Set the initial background color
    originalBackground = GetBackgroundColour();
}

void CustomComboBox::OnComboBox(wxCommandEvent& event)
{
    // User changed the selection, set background to yellow
    SetBackgroundColour(wxColour(255, 255, 0)); // Yellow
    Refresh();
}

void CustomComboBox::OnDropDown(wxCommandEvent& event)
{
    // Dropdown opened, reset background to default
    SetBackgroundColour(originalBackground);
    isDropdownOpen = true;
    Refresh();
}

void CustomComboBox::OnCloseUp(wxCommandEvent& event)
{
    // Dropdown closed, set background back to yellow
    SetBackgroundColour(wxColour(255, 255, 0)); // Yellow
    isDropdownOpen = false;
    Refresh();
}

void CustomComboBox::OnFocus(wxFocusEvent& event) {
    event.Skip(false);
}

void CustomComboBox::OnPaint(wxPaintEvent& event)
{
    event.Skip();
    SetSelection(0, 0);
    HideCaret(NULL);
    SetCursor(wxCursor(wxCURSOR_DEFAULT));
}

wxBEGIN_EVENT_TABLE(CustomComboBox, wxComboBox)
    EVT_COMBOBOX(wxID_ANY, CustomComboBox::OnComboBox)
    EVT_COMBOBOX_DROPDOWN(wxID_ANY, CustomComboBox::OnDropDown)
    EVT_COMBOBOX_CLOSEUP(wxID_ANY, CustomComboBox::OnCloseUp)
    // EVT_SET_FOCUS(CustomComboBox::OnFocus)
    EVT_PAINT(CustomComboBox::OnPaint)
wxEND_EVENT_TABLE()
