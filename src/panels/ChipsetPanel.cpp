#include "ChipsetPanel.h"
#include "components/TTimingComboBox.h"
#include "components/TReadonlyTextBox.h"

ChipsetPanel::ChipsetPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxPanelNameStr) {
    AddControls();
}

void ChipsetPanel::AddControls() {
    // Create the main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

    // "General"
    wxStaticBoxSizer* generalGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("General"));
    //wxStaticBox* staticBoxGeneral = generalGroupSizer->GetStaticBox();
    rowSizer->Add(generalGroupSizer, 1, wxEXPAND);
    wxFlexGridSizer* gridSizerGeneral = new wxFlexGridSizer(8, 2, 2, 0);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("CPU Disconnect")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("CPUDisconnect"), "Disabled", wxSize(76, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("HALT State")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("HALTDisconnect"), "Disabled", wxSize(76, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("STPGNT State")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("STPGNTDisconnect"), "Disabled", wxSize(76, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("AGP Fast Write")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("AGPFastWrite"), "Disabled", wxSize(76, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("AGP SBA")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("AGPSBA"), "Disabled", wxSize(76, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("AGP Ctrl Latency")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("AGPControllerLatency"), "2", wxSize(76, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("AGP Bus Latency")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("AGPBusLatency"), "2", wxSize(76, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("PCI Latency Timer")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("PCILatencyTimer"), "2", wxSize(76, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    generalGroupSizer->Add(gridSizerGeneral, 1, wxEXPAND | wxBOTTOM, 5);

    // "S2K"
    wxStaticBoxSizer* s2kGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("S2K"));
    //wxStaticBox* staticBoxS2k = s2kGroupSizer->GetStaticBox();
    rowSizer->Add(s2kGroupSizer, 1, wxEXPAND | wxLEFT, 5);

    wxFlexGridSizer* gridSizerS2k = new wxFlexGridSizer(8, 2, 2, 0);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("WRCOUNT")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("XCAARB_WRCOUNT"), "0", wxSize(48, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("RDCOUNT")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("XCAARB_RDCOUNT"), "0", wxSize(48, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("PRCOUNT")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("XCAARB_PRCOUNT"), "0", wxSize(48, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("WRDATA Delay")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("WRDATA_Delay"), "0", wxSize(48, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("WRTORD Delay")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("WRTORD_Delay"), "0", wxSize(48, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("RDTOWR Delay")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("RDTOWR_Delay"), "2", wxSize(48, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("SYSDCOUT Delay")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("SYSDCOUT_Delay"), "2", wxSize(48, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("SYSDCIN Delay")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("SYSDCIN_Delay"), "2", wxSize(48, 21), 0, 1), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    s2kGroupSizer->Add(gridSizerS2k, 1, wxEXPAND | wxBOTTOM, 5);

    // "FSB"
    wxStaticBoxSizer* fsbGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("FSB"));
    //wxStaticBox* staticBoxFsb = fsbGroupSizer->GetStaticBox();

    wxBoxSizer* s1 = new wxBoxSizer(wxHORIZONTAL);
    wxSlider* pllSlider = new wxSlider(this, wxID_ANY, 50, 30, 350);
    TReadonlyTextBox* pllSliderValue = new TReadonlyTextBox(this, wxString::Format("%.2f MHz", 222.34), 84, _T("PllSliderValue"));

    wxButton* buttonPllPrev = new wxButton(this, wxID_ANY, _T("3"), wxDefaultPosition, wxSize(18, 18));
    wxFont btnFont = buttonPllPrev->GetFont();
    btnFont.SetFaceName(_T("Webdings"));
    btnFont.SetPointSize(10);
    buttonPllPrev->SetFont(btnFont);

    wxButton* buttonPllNext = new wxButton(this, wxID_ANY, "4", wxDefaultPosition, wxSize(18, 18));
    buttonPllNext->SetFont(btnFont);

    s1->Add(pllSlider, 1, wxEXPAND | wxALL, 0);
    s1->Add(buttonPllPrev, 0);
    s1->Add(buttonPllNext, 0, wxLEFT, 2);
    s1->Add(pllSliderValue, 0, wxLEFT, 10);

    fsbGroupSizer->Add(s1, 1, wxEXPAND | wxALIGN_CENTRE_VERTICAL | wxALL, 5);

    // "AGP"
    wxStaticBoxSizer* agpGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("AGP / PCI"));
    //wxStaticBox* staticBoxAgp = agpGroupSizer->GetStaticBox();

    wxBoxSizer* s2 = new wxBoxSizer(wxHORIZONTAL);
    wxSlider* pciSlider = new wxSlider(this, wxID_ANY, 66, 0, 166);
    TReadonlyTextBox* pciSliderValue = new TReadonlyTextBox(this, wxString::Format("%.2f / %.2f", 66.67, 33.33), 84, _T("PciSliderValue"));

    wxButton* buttonPciPrev = new wxButton(this, wxID_ANY, _T("3"), wxDefaultPosition, wxSize(18, 18));
    //wxFont btnFont = buttonPciPrev->GetFont();
    //btnFont.SetFaceName(_T("Webdings"));
    //btnFont.SetPointSize(10);
    buttonPciPrev->SetFont(btnFont);

    wxButton* buttonPciNext = new wxButton(this, wxID_ANY, "4", wxDefaultPosition, wxSize(18, 18));
    buttonPciNext->SetFont(btnFont);

    s2->Add(pciSlider, 1, wxEXPAND | wxALL, 0);
    s2->Add(buttonPciPrev, 0);
    s2->Add(buttonPciNext, 0, wxLEFT, 2);
    s2->Add(pciSliderValue, 0, wxLEFT, 10);

    agpGroupSizer->Add(s2, 1, wxEXPAND | wxALIGN_CENTRE_VERTICAL | wxALL, 5);

    // Add child sizers
    mainSizer->Add(rowSizer, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(fsbGroupSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    mainSizer->Add(agpGroupSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

    // Set the main sizer for the frame
    SetSizerAndFit(mainSizer);
}

