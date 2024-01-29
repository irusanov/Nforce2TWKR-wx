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

    rightVerticalSizer->Add(staticBoxTopRight, 1, wxEXPAND | wxBOTTOM, 0);
    rightVerticalSizer->Add(staticBoxBottomRight, 0, wxEXPAND | wxTOP, 5);

    dramPanelSizer->Add(rightVerticalSizer, 1, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM, 5);

     // TAdvancedEdit *obj = static_cast<TAdvancedEdit *>(FindWindowByName("TestName"));
    // ((TAdvancedEdit *)obj)->SetValue("AA");

    // Romsip controls
    wxFlexGridSizer* romsipGridSizer = new wxFlexGridSizer(4, 8, 2, 2);

    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "48", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "4C", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "4D", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "50", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->AddStretchSpacer();
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "65", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "66", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "67", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);

    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip48", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip4C", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip4D", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip50", "6F"), 0);
    romsipGridSizer->AddStretchSpacer();
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip65", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip66", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip67", "6F"), 0);

    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "68", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "69", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "6A", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "6B", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "6C", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "6D", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "6F", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "74", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);

    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip68", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip69", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip6A", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip6B", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip6C", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip6D", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip6F", "6F"), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip74", "6F"), 0);

    staticBoxBottomRight->Add(romsipGridSizer, 0, wxEXPAND | wxBOTTOM, 5);
}
