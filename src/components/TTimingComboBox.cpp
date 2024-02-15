// TTimingComboBox.cpp

#include "components/TTimingComboBox.h"

TTimingComboBox::TTimingComboBox(wxWindow* parent,
                                 const wxString& name,
                                 const wxString& value,
                                 const wxSize& size,
                                 const int min,
                                 const int max,
                                 const bool editable,
                                 const wxArrayString& choices,
                                 const bool isCustomValue)
    : wxOwnerDrawnComboBox(parent, wxID_ANY, value, wxDefaultPosition, size, wxArrayString(), editable ? 0 : wxCB_READONLY, wxDefaultValidator, name),
    tMin(min),
    tMax(max),
    savedIndex(-1),
    customItems(choices),
    tCustomValue(isCustomValue) {

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
}

// Methods
void TTimingComboBox::CreateItems() {
    Clear();

    if (customItems.Count() > 0) {
        tMin = 0;
        tMax = customItems.Count() - 1;
    }

    if (customItems.Count() > 0) {
        Append(customItems);
    } else {
        for (int i = tMin; i <= tMax; i++) {
            Append(wxString::Format("%d", i));
        }
    }
}

void TTimingComboBox::SetValue(int value, bool resetIndex) {
    int index = -1;

    // custom item different than the index, e.g. "32, 64, ..."
    if (IsCustomValue() && customItems.Count() > 0 && value >= 0) {
        wxString valueStr = wxString::Format("%d", value);
        index = FindString(valueStr);

        if (index == wxNOT_FOUND) {
            index = 0;
            for (size_t i = 0; i < customItems.Count(); i++) {
                long itemValue;
                GetString(i).ToLong(&itemValue);
                if (value > static_cast<int>(itemValue)) {
                    index++;
                }
            }

            // Insert
            customItems.Insert(valueStr, index);
            CreateItems();
        }
    // usual case where values are generated from tMin and tMax or are using index, but have custom labels, e.g. "Disabled/Enabled"
    } else if (value >= tMin && value <= tMax) {
        index = value - tMin;
    }

    SetSelection(index);

    if (resetIndex) {
        savedIndex = index;
    }

    SetBackgroundColour(IsChanged() ? *wxYELLOW : originalBackground);

    // Refresh();
}

int TTimingComboBox::GetValue() {
    // custom value case (text like Disabled/Enabled), assuming the actual value is the index
    if (!IsCustomValue() && customItems.Count() > 0) {
        int index = GetSelection();
        if (index == wxNOT_FOUND) {
            return -1;
        }
        return index;
    }

    // default case, get value as integer
    return wxAtoi(wxComboCtrl::GetValue());
}

bool TTimingComboBox::IsChanged() {
    return savedIndex != GetSelection();
}

bool TTimingComboBox::IsCustomValue() {
    return tCustomValue;
}

// Handlers
void TTimingComboBox::OnDropDown(wxCommandEvent& event) {
    SetBackgroundColour(originalBackground);
    Refresh();
    event.Skip();
}

void TTimingComboBox::OnCloseUp(wxCommandEvent& event) {
    if (IsChanged()) {
        SetBackgroundColour(*wxYELLOW);
    }
    Refresh();
    event.Skip();
}

void TTimingComboBox::OnComboBox(wxCommandEvent& event) {
    SetBackgroundColour(IsChanged() ? *wxYELLOW : originalBackground);
    Refresh();
    event.Skip();
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
