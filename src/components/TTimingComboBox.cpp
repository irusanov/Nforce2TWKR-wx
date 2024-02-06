// TTimingComboBox.cpp

#include "components/TTimingComboBox.h"

TTimingComboBox::TTimingComboBox(wxWindow* parent,
                                 const wxString& name,
                                 const wxString& value,
                                 const wxSize& size,
                                 const int min,
                                 const int max,
                                 const bool editable,
                                 const wxArrayString& choices)
    : wxOwnerDrawnComboBox(parent, wxID_ANY, value, wxDefaultPosition, size, wxArrayString(), editable ? 0 : wxCB_READONLY, wxDefaultValidator, name),
      tMin(min),
      tMax(max),
      tValue(0),
      tIndex(0),
      isChanged(false),
      customItems(choices) {

    originalBackground = GetBackgroundColour();

    if (editable) {
        SetBackgroundColour(originalBackground);
        SetPopupMaxHeight(200);
        //SetEditable(false);
    } else {
        Enable(false);
    }

    wxTextCtrl* textCtrl = this->GetTextCtrl();
    if (textCtrl) {
        textCtrl->SetEditable(false);
        textCtrl->Bind(wxEVT_LEFT_DOWN, &TTimingComboBox::OnTextCtrlClick, this);
        textCtrl->Bind(wxEVT_PAINT, &TTimingComboBox::OnPaint, this);
        SetTextCtrlStyle(wxTE_READONLY | wxBORDER_NONE);
    }

    CreateItems();

    Bind(wxEVT_COMBOBOX, &TTimingComboBox::OnComboBox, this);
    Bind(wxEVT_COMBOBOX_DROPDOWN, &TTimingComboBox::OnDropDown, this);
    Bind(wxEVT_COMBOBOX_CLOSEUP, &TTimingComboBox::OnCloseUp, this);
    //Bind(wxEVT_PAINT, &TTimingComboBox::OnPaint, this);
}

void TTimingComboBox::CreateItems() {
    if (customItems.Count() > 0) {
        Append(customItems);
    } else {
        for (int i = tMin; i <= tMax; i++) {
            Append(wxString::Format("%d", i));
        }
    }
}

/*
void TTimingComboBox::OnDrawItem(wxDC& dc, const wxRect& rect, int item, int flags) const
{
    dc.SetBrush(wxBrush(GetBackgroundColour()));
    dc.SetPen(wxPen(GetBackgroundColour()));

    // Customize the drawing of items if needed
    wxOwnerDrawnComboBox::OnDrawItem(dc, rect, item, flags);
}
*/

void TTimingComboBox::OnDropDown(wxCommandEvent& event) {
    SetBackgroundColour(originalBackground);
    Refresh();
    event.Skip();
}

void TTimingComboBox::OnCloseUp(wxCommandEvent& event) {
    if (isChanged) {
        SetBackgroundColour(*wxYELLOW);
    }
    Refresh();
    event.Skip();
}

void TTimingComboBox::OnComboBox(wxCommandEvent& event) {
    isChanged = (tIndex != GetSelection());
    SetBackgroundColour(isChanged ? *wxYELLOW : originalBackground);
    Refresh();
    event.Skip();
}

// Set selected index corresponding to the value
void TTimingComboBox::SetValue(int value) {
    if (value >= tMin && value <= tMax) {
        SetSelection(value - tMin);
        tValue = value;
        tIndex = GetSelection();
        isChanged = false;
        SetBackgroundColour(originalBackground);
        Refresh();
    }
}

// Set selected index by value
void TTimingComboBox::SetItemValue(int value) {
    if (value >= tMin && value <= tMax) {
        int index = FindString(wxString::Format("%d", value));

        if (index == wxNOT_FOUND) {
            index = 0;
            for (unsigned int i = 0; i < GetCount(); i++) {
                if (value > wxAtoi(GetString(i))) {
                    index++;
                }
            }

            Insert(wxString::Format("%d", value), index);
        }

        SetSelection(index);
        tIndex = index;
        tValue = value;
        isChanged = false;
        SetBackgroundColour(originalBackground);
        Refresh();
    }
}

void TTimingComboBox::SetChanged() {
    isChanged = true;
    SetBackgroundColour(*wxYELLOW);
    Refresh();
}

void TTimingComboBox::OnPaint(wxPaintEvent& event) {
    SetSelection(0, 0);
    HideCaret(NULL);
    SetCursor(wxCursor(wxCURSOR_DEFAULT));
    event.Skip();
}

void TTimingComboBox::OnTextCtrlClick(wxMouseEvent& event) {
    if (IsPopupWindowState(Hidden)) {
        Popup();
    } else if (IsPopupWindowState(Visible)) {
        Dismiss();
    }
    event.Skip(false);
}
