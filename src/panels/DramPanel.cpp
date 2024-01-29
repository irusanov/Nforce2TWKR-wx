#include "panels/DramPanel.h"

DramPanel::DramPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                     const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    AddControls();
}

void DramPanel::AddControls()
{
    wxBoxSizer* dramPanelSizer = new wxBoxSizer(wxHORIZONTAL);

    CreateLeftStaticBox(dramPanelSizer);
    CreateRightStaticBoxes(dramPanelSizer);

    // Set the main sizer for the frame
    SetSizerAndFit(dramPanelSizer);
}

void DramPanel::CreateLeftStaticBox(wxSizer* dramPanelSizer)
{
    wxStaticBoxSizer* staticBoxLeft = new wxStaticBoxSizer(wxVERTICAL, this, "Timings");

    // Create a flex grid sizer with 16 rows and 2 columns
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(16, 2, 2, 0);

    // Labels and Comboboxes
    for (int i = 0; i < 16; i++) {
        // Static text label
        wxStaticText* label = new wxStaticText(this, wxID_ANY, "TRCDW");

        // ComboBox
        TTimingComboBox* comboBox = new TTimingComboBox(this, "CAS", "2", wxDefaultPosition, wxSize(52, 21), 2, 3);

        // Add label and combobox to the grid sizer
        gridSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        gridSizer->Add(comboBox, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
    }

    // Add the grid sizer to the main sizer
    staticBoxLeft->Add(gridSizer, 1, wxEXPAND, 0);

    /*
    wxArrayString choices;
    choices.Add("111");
    choices.Add("123");
    choices.Add("333");

    wxComboBox* combo = new wxComboBox(this, wxID_ANY, "123", wxDefaultPosition, wxDefaultSize, choices, wxCB_READONLY);
    CustomComboBox* customComboBox = new CustomComboBox(this, wxID_ANY, "123", wxDefaultPosition, wxDefaultSize, choices);

    staticBoxLeft->Add(combo, 0, wxEXPAND | wxALL, 5);
    staticBoxLeft->Add(customComboBox, 0, wxALL, 5);
    */

    dramPanelSizer->Add(staticBoxLeft, 0, wxEXPAND | wxALL, 5);
}

void DramPanel::CreateRightStaticBoxes(wxSizer* dramPanelSizer)
{
    wxBoxSizer* rightVerticalSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticBoxSizer* staticBoxTopRight = new wxStaticBoxSizer(wxVERTICAL, this, "Advanced");
    wxStaticBoxSizer* staticBoxBottomRight = new wxStaticBoxSizer(wxVERTICAL, this, "ROMSIP");

    rightVerticalSizer->Add(staticBoxTopRight, 2, wxEXPAND | wxBOTTOM, 0);
    rightVerticalSizer->Add(staticBoxBottomRight, 1, wxEXPAND | wxTOP, 10);

    dramPanelSizer->Add(rightVerticalSizer, 1, wxEXPAND | wxALL, 5);

    TAdvancedEdit* advancedEdit = new TAdvancedEdit(this, "TestName", "6F");
    wxButton* button = new wxButton(this, wxID_ANY, "Get Value");

     TAdvancedEdit *obj = static_cast<TAdvancedEdit *>(FindWindowByName("TestName"));
    ((TAdvancedEdit *)obj)->SetValue("AA");

    staticBoxTopRight->Add(advancedEdit, 0, wxEXPAND);
    staticBoxBottomRight->Add(button, 0, wxEXPAND);
}
