#include "TTimingComboBox.h"

TTimingComboBox::TTimingComboBox(wxWindow* parent, wxWindowID id,
                                 const wxPoint& pos,
                                 const wxSize& size,
                                 long style,
                                 const wxValidator& validator,
                                 const wxString& name)
    : wxChoice(parent, id, pos, size, 0, NULL, style, validator, name) {
    Init();
}

TTimingComboBox::~TTimingComboBox() {
    // Destructor
}

void TTimingComboBox::Init() {
    tMin = 0;
    tMax = 100; // Set your desired maximum value
    tCustomItems = false;
    tCustomValue = true;
    tValue = 0;
    tIndex = -1;
    tChanged = false;

    Bind(wxEVT_CHOICE, &TTimingComboBox::OptionChange, this);
    Bind(wxEVT_COMBOBOX_DROPDOWN, &TTimingComboBox::DropDown, this);
    Bind(wxEVT_COMBOBOX_CLOSEUP, &TTimingComboBox::CloseUp, this);
}

void TTimingComboBox::OptionChange(wxCommandEvent& event) {
    tChanged = tIndex != GetSelection();
    SetBackgroundColour(tChanged ? *wxLIGHT_GREY : *wxWHITE);
}

void TTimingComboBox::DropDown(wxCommandEvent& event) {
    SetBackgroundColour(*wxWHITE);
}

void TTimingComboBox::CloseUp(wxCommandEvent& event) {
    if (tChanged) {
        SetBackgroundColour(*wxLIGHT_GREY);
    }
}

void TTimingComboBox::SetMin(int value) {
    if (value >= 0) {
        tMin = value;

        if (!tCustomItems) {
            Clear();

            for (int i = tMin; i <= tMax; i++) {
                Append(wxString::Format(wxT("%d"), i), new TimingComboBoxData(i));
            }
        }
    }
}

void TTimingComboBox::SetMax(int value) {
    if (value > 0 && value > tMin) {
        tMax = value;

        if (!tCustomItems) {
            Clear();

            for (int i = tMin; i <= tMax; i++) {
                Append(wxString::Format(wxT("%d"), i), new TimingComboBoxData(i));
            }
        }
    }
}

void TTimingComboBox::SetValue(int value) {
    if (value >= 0) {
        SetSelection(value - tMin);
        tValue = value;
        tIndex = GetSelection();
        tChanged = false;
        SetBackgroundColour(*wxWHITE);
    }
}

void TTimingComboBox::SetItemValue(int value) {
    if (!tCustomValue) {
        return;
    }

    if (value >= 0) {
        int index = FindString(wxString::Format(wxT("%d"), value));

        if (index != wxNOT_FOUND) {
            SetSelection(index);
            tIndex = index;
        } else {
            index = 0;
            for (size_t i = 0; i < GetCount(); i++) {
                TimingComboBoxData* data = dynamic_cast<TimingComboBoxData*>(GetClientObject(i));
                if (data && value > data->GetValue()) {
                    index++;
                }
            }

            TimingComboBoxData* data = new TimingComboBoxData(value);
            Insert(wxString::Format(wxT("%d"), value), index, data);
            SetSelection(index);
        }

        tValue = value;
        tChanged = false;
        SetBackgroundColour(*wxWHITE);
    }
}

void TTimingComboBox::SetChanged() {
    tChanged = true;
    SetBackgroundColour(*wxLIGHT_GREY);
}

void TTimingComboBox::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);

    wxRect rect = GetClientRect();

    wxBrush brush(GetBackgroundColour());
    dc.SetBackground(brush);
    dc.Clear();

    // Call the base class handler
    event.Skip();
}
