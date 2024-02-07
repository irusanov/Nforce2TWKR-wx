#include "panels/DramPanel.h"
#include "Constants.h"
#include <wx/gbsizer.h>

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

    std::vector<control_def_t> controls = {
        { "CAS", "TCL", true, 0, 2, tcasChoices, false },
        { "TRCDR", "TRCDR", true, 0, 15, {}, false },
        { "TRCDW", "TRCDW", true, 0, 15, {}, false },
        { "TRP", "TRP", true, 0, 15, {}, false },
        { "TRAS", "TRAS", true, 0, 31, {}, false },
        { "TRC", "TRC", true, 0, 31, {}, false },
        { "TRFC", "TRFC", true, 0, 31, {}, false },
        { "CR", "CR", true, 1, 2, tcrChoices, false },
        { "TDOE", "TDOE", true, 0, 7, {}, false },
        { "TRRD", "TRRD", true, 0, 7, {}, false },
        { "TWTP", "TWTP", true, 0, 7, {}, false },
        { "TWTR", "TWTR", true, 0, 7, {}, false },
        { "TREXT", "TREXT", true, 0, 3, {}, false },
        { "TRTP", "TRTP", true, 0, 7, {}, false },
        { "TRTW", "TRTW", true, 0, 7, {}, false },
        { "TREF", "TREF", true, 0, 7, trefChoices, true },
    };

    for (const control_def_t control : controls) {
        // Static text label
        wxStaticText* label = new wxStaticText(this, wxID_ANY, control.label);

        // ComboBox
        TTimingComboBox* comboBox = new TTimingComboBox(this, control.name, "", wxSize(52, 21), control.min, control.max,
                                                        control.editable, Utils::ConvertToWxArrayString(control.customChoices), control.customItems);

        // Add label and combobox to the grid sizer
        gridSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        gridSizer->Add(comboBox, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

        // std::cout << "String: " << stringPart << ", Bool: " << std::boolalpha << boolPart << std::endl;
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

    // TTimingComboBox *obj = static_cast<TTimingComboBox *>(FindWindowByName("TRAS"));
    // ((TTimingComboBox *)obj)->SetValue("7");
}

void DramPanel::CreateRightStaticBoxes(wxSizer* dramPanelSizer)
{
    wxBoxSizer* rightVerticalSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticBoxSizer* staticBoxTopRight = new wxStaticBoxSizer(wxVERTICAL, this, "Advanced");
    wxStaticBoxSizer* staticBoxBottomRight = new wxStaticBoxSizer(wxVERTICAL, this, "ROMSIP");

    rightVerticalSizer->Add(staticBoxTopRight, 1, wxEXPAND | wxBOTTOM, 0);
    rightVerticalSizer->Add(staticBoxBottomRight, 0, wxEXPAND | wxTOP, 0);

    dramPanelSizer->Add(rightVerticalSizer, 1, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM, 5);

     // TAdvancedEdit *obj = static_cast<TAdvancedEdit *>(FindWindowByName("TestName"));
    // ((TAdvancedEdit *)obj)->SetValue("AA");

    // Advanced Controls

    wxGridBagSizer* advancedGridSizer = new wxGridBagSizer(2, 2);
    wxStaticBox* advancedStaticBox = staticBoxTopRight->GetStaticBox();

    wxArrayString booleanChoicesArray = Utils::ConvertToWxArrayString(booleanChoices);

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "DIMM0 Drive Strengths", wxDefaultPosition, wxSize(130, -1)), wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL, 0);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DIMM0DrvStrA", "", wxSize(40, 21), 0, 15), wxGBPosition(0, 1), wxGBSpan(1, 1));
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DIMM0DrvStrB", "", wxSize(40, 21), 0, 15), wxGBPosition(0, 2), wxGBSpan(1, 1));

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "DIMM0 Slew Rate"), wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DIMM0SlewRate", "", wxSize(40, 21), 0, 15), wxGBPosition(1, 1), wxGBSpan(1, 1));

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "DIMM1 Drive Strengths"), wxGBPosition(2, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DIMM1DrvStrA", "", wxSize(40, 21), 0, 15), wxGBPosition(2, 1), wxGBSpan(1, 1));
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DIMM1DrvStrB", "", wxSize(40, 21), 0, 15), wxGBPosition(2, 2), wxGBSpan(1, 1));

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "DIMM1 Slew Rate"), wxGBPosition(3, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DIMM1SlewRate", "", wxSize(40, 21), 0, 15), wxGBPosition(3, 1), wxGBSpan(1, 1));

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "DIMM2 Drive Strengths"), wxGBPosition(4, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DIMM2DrvStrA", "", wxSize(40, 21), 0, 15), wxGBPosition(4, 1), wxGBSpan(1, 1));
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DIMM2DrvStrB", "", wxSize(40, 21), 0, 15), wxGBPosition(4, 2), wxGBSpan(1, 1));

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "DIMM2 Slew Rate"), wxGBPosition(5, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DIMM2SlewRate", "7", wxSize(40, 21), 0, 15), wxGBPosition(5, 1), wxGBSpan(1, 1));

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "Auto Precharge"), wxGBPosition(6, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "AutoPrecharge", "", wxSize(85, 21), 0, 1, true, booleanChoicesArray), wxGBPosition(6, 1), wxGBSpan(1, 2));

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "Super Bypass"), wxGBPosition(7, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "SuperBypass", "", wxSize(85, 21), 0, 1, true, booleanChoicesArray), wxGBPosition(7, 1), wxGBSpan(1, 2));

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "Data Scavenged Rate"), wxGBPosition(8, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DataScavengedRate", "", wxSize(85, 21), 0, 1, true, Utils::ConvertToWxArrayString(dataScavengedRateChoices)), wxGBPosition(8, 1), wxGBSpan(1, 2));

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "Drive Strength Mode"), wxGBPosition(9, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "DriveStrengthMode", "", wxSize(85, 21), 0, 1, true, Utils::ConvertToWxArrayString(driveStrengthModeChoices)), wxGBPosition(9, 1), wxGBSpan(1, 2));

    advancedGridSizer->Add(new wxStaticText(advancedStaticBox, wxID_ANY, "Burst Mode"), wxGBPosition(10, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL);
    advancedGridSizer->Add(new TTimingComboBox(advancedStaticBox, "BurstMode", "", wxSize(85, 21), 0, 1, true, Utils::ConvertToWxArrayString(burstModeChoices)), wxGBPosition(10, 1), wxGBSpan(1, 2));

    staticBoxTopRight->Add(advancedGridSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);


    // Romsip controls
    wxFlexGridSizer* romsipGridSizer = new wxFlexGridSizer(4, 8, 2, 2);

    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->AddStretchSpacer();
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 5);

    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip48", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip4C", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip4D", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip50", ""), 0);
    romsipGridSizer->AddStretchSpacer();
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip65", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip66", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip67", ""), 0);

    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 7);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 7);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 7);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 7);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 7);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 7);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 7);
    romsipGridSizer->Add(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(26, -1), wxTE_CENTER), 0, wxALIGN_BOTTOM | wxTOP, 7);

    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip68", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip69", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip6A", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip6B", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip6C", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip6D", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip6F", ""), 0);
    romsipGridSizer->Add(new TAdvancedEdit(this, "Romsip74", ""), 0);

    staticBoxBottomRight->Add(romsipGridSizer, 0, wxEXPAND | wxBOTTOM, 5);
}
