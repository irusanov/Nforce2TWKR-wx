#include "ChipsetPanel.h"
#include "../../utils/Nforce2Pll.h"

ChipsetPanel::ChipsetPanel(wxWindow* parent, Cpu* cpu)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxPanelNameStr),
      cpuReference(cpu) {
    AddControls();
    Update();
}

void ChipsetPanel::AddControls() {
    // Create the main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

    wxArrayString booleanChoicesArray = Utils::ConvertToWxArrayString(booleanChoices);
    wxArrayString latencyChoicesArray = Utils::ConvertToWxArrayString(latencyChoices);

    // "General"
    wxStaticBoxSizer* generalGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("General"));
    //wxStaticBox* staticBoxGeneral = generalGroupSizer->GetStaticBox();
    rowSizer->Add(generalGroupSizer, 1, wxEXPAND);
    wxFlexGridSizer* gridSizerGeneral = new wxFlexGridSizer(8, 2, 2, 0);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("CPU Disconnect")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("CPUDisconnect"), "", wxSize(76, 21), 0, 1, true, booleanChoicesArray), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("HALT State")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("HALTDisconnect"), "", wxSize(76, 21), 0, 1, true, booleanChoicesArray), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("STPGNT State")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("STPGNTDisconnect"), "", wxSize(76, 21), 0, 1, true, Utils::ConvertToWxArrayString(booleanChoicesReversed)), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("AGP Fast Write")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("AGPFastWrite"), "", wxSize(76, 21), 0, 1, true, booleanChoicesArray), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("AGP SBA")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("AGPSBA"), "", wxSize(76, 21), 0, 1, true, booleanChoicesArray), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("AGP Ctrl Latency")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("AGPControllerLatency"), "", wxSize(76, 21), 0, 1, true, latencyChoicesArray), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("AGP Bus Latency")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("AGPBusLatency"), "", wxSize(76, 21), 0, 1, true, latencyChoicesArray), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerGeneral->Add(new wxStaticText(this, wxID_ANY, _("PCI Latency Timer")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerGeneral->Add(new TTimingComboBox(this, _T("PCILatencyTimer"), "", wxSize(76, 21), 0, 1, true, Utils::ConvertToWxArrayString(pciLatencyChoices)), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    generalGroupSizer->Add(gridSizerGeneral, 1, wxEXPAND | wxBOTTOM, 5);

    // "S2K"
    wxStaticBoxSizer* s2kGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("S2K"));
    //wxStaticBox* staticBoxS2k = s2kGroupSizer->GetStaticBox();
    rowSizer->Add(s2kGroupSizer, 1, wxEXPAND | wxLEFT, 5);

    wxFlexGridSizer* gridSizerS2k = new wxFlexGridSizer(8, 2, 2, 0);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("WRCOUNT")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("XCAARB_WRCOUNT"), "", wxSize(48, 21), 0, 7), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("RDCOUNT")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("XCAARB_RDCOUNT"), "", wxSize(48, 21), 0, 7), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("PRCOUNT")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("XCAARB_PRCOUNT"), "", wxSize(48, 21), 0, 7), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("WRDATA Delay")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("WRDATA_Delay"), "", wxSize(48, 21), 0, 7), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("WRTORD Delay")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("WRTORD_Delay"), "", wxSize(48, 21), 1, 2), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("RDTOWR Delay")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("RDTOWR_Delay"), "", wxSize(48, 21), 1, 4), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("SYSDCOUT Delay")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("SYSDCOUT_Delay"), "", wxSize(48, 21), 0, 3), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    gridSizerS2k->Add(new wxStaticText(this, wxID_ANY, _("SYSDCIN Delay")), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    gridSizerS2k->Add(new TTimingComboBox(this, _T("SYSDCIN_Delay"), "", wxSize(48, 21), 0, 15), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    s2kGroupSizer->Add(gridSizerS2k, 1, wxEXPAND | wxBOTTOM, 5);

    // "FSB"
    wxStaticBoxSizer* fsbGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("FSB"));
    //wxStaticBox* staticBoxFsb = fsbGroupSizer->GetStaticBox();

    wxBoxSizer* s1 = new wxBoxSizer(wxHORIZONTAL);
    pllSlider = new wxSlider(this, wxID_ANY, -1, NFORCE2_MIN_FSB, NFORCE2_MAX_FSB);
    pllSliderValue = new TReadonlyTextBox(this, wxEmptyString, 84, _T("PllSliderValue"));

    buttonPllPrev = new wxButton(this, wxID_ANY, _T("3"), wxDefaultPosition, wxSize(18, 18));
    wxFont btnFont = buttonPllPrev->GetFont();
    btnFont.SetFaceName(_T("Webdings"));
    btnFont.SetPointSize(10);
    buttonPllPrev->SetFont(btnFont);

    buttonPllNext = new wxButton(this, wxID_ANY, _T("4"), wxDefaultPosition, wxSize(18, 18));
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
    pciSlider = new wxSlider(this, wxID_ANY, -1, 36, 200);
    pciSliderValue = new TReadonlyTextBox(this, wxEmptyString, 84, _T("PciSliderValue"));

    buttonPciPrev = new wxButton(this, wxID_ANY, _T("3"), wxDefaultPosition, wxSize(18, 18));
    //wxFont btnFont = buttonPciPrev->GetFont();
    //btnFont.SetFaceName(_T("Webdings"));
    //btnFont.SetPointSize(10);
    buttonPciPrev->SetFont(btnFont);

    buttonPciNext = new wxButton(this, wxID_ANY, _T("4"), wxDefaultPosition, wxSize(18, 18));
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

    pciSlider->Bind(wxEVT_SCROLL_THUMBTRACK, &ChipsetPanel::OnPciSliderChange, this);
    pciSlider->Bind(wxEVT_SCROLL_CHANGED, &ChipsetPanel::OnPciSliderChange, this);
    pllSlider->Bind(wxEVT_SCROLL_THUMBTRACK, &ChipsetPanel::OnPllSliderChange, this);
    pllSlider->Bind(wxEVT_SCROLL_CHANGED, &ChipsetPanel::OnPllSliderChange, this);
    buttonPciNext->Bind(wxEVT_BUTTON, &ChipsetPanel::OnButtonPciNextClick, this);
    buttonPciPrev->Bind(wxEVT_BUTTON, &ChipsetPanel::OnButtonPciPrevClick, this);
    buttonPllNext->Bind(wxEVT_BUTTON, &ChipsetPanel::OnButtonPllNextClick, this);
    buttonPllPrev->Bind(wxEVT_BUTTON, &ChipsetPanel::OnButtonPllPrevClick, this);
}

void ChipsetPanel::UpdatePciSlider(unsigned int mul) {
    double pci = (mul / 15.0) * 6.25;
    double agp = pci * 2.0;

    if (mul < pciSlider->GetMin()) {
        pciSlider->SetMin(mul);
    } else if (mul > pciSlider->GetMax()) {
        pciSlider->SetMax(mul);
    }

    pciSlider->SetValue(mul);
    pciSliderValue->SetValue(wxString::Format("%.2f / %.2f", agp, pci));

    int sliderValue = pllSlider->GetValue();
    bool minReached = sliderValue <= pciSlider->GetMin();
    bool maxReached = sliderValue >= pciSlider->GetMax();

    buttonPciNext->Enable(!maxReached);
    buttonPciPrev->Enable(!minReached);
}

void ChipsetPanel::UpdatePllSlider(double fsb) {
    if (fsb > 0) {
        targetFsb = fsb;
        pllSlider->SetValue(static_cast<int>(fsb));
        pllSliderValue->SetValue(wxString::Format("%.2f MHz", targetFsb));

        int sliderValue = pllSlider->GetValue();
        bool minReached = ceil(fsb) <= pllSlider->GetMin();
        bool maxReached = floor(fsb) >= pllSlider->GetMax();

        buttonPllNext->Enable(!maxReached);
        buttonPllPrev->Enable(!minReached);
    }
}

void ChipsetPanel::Update() {
    cpu_info_t cpuInfo = cpuReference->GetCpuInfo();
    UpdatePciSlider(cpuInfo.pciMul);
    UpdatePllSlider(cpuInfo.fsb);
}

// PCI/AGP
void ChipsetPanel::OnPciSliderChange(wxScrollEvent& event) {
    UpdatePciSlider(pciSlider->GetValue());
}

void ChipsetPanel::OnButtonPciPrevClick(wxCommandEvent& event) {
    UpdatePciSlider(pciSlider->GetValue() - 1);
}

void ChipsetPanel::OnButtonPciNextClick(wxCommandEvent& event){
    UpdatePciSlider(pciSlider->GetValue() + 1);
}

int ChipsetPanel::GetTargetPci() {
    return pciSlider->GetValue();
}

// Pll
void ChipsetPanel::OnPllSliderChange(wxScrollEvent& event) {
    int position = pllSlider->GetValue();
    pair<double, int> p;

    if (position < static_cast<int>(targetFsb)) {
        p = cpuReference->GetPll().GetPrevPll(position);
    } else {
        p = cpuReference->GetPll().GetNextPll(position);
    }

    UpdatePllSlider(p.first);
}

void ChipsetPanel::OnButtonPllPrevClick(wxCommandEvent& event) {
    pair<double, int>prevPll = cpuReference->GetPll().GetPrevPll(targetFsb);
    double fsb = prevPll.first;

    if (fsb > 0) {
        UpdatePllSlider(fsb);
    }
}

void ChipsetPanel::OnButtonPllNextClick(wxCommandEvent& event){
    pair<double, int>nextPll = cpuReference->GetPll().GetNextPll(targetFsb);
    double fsb = nextPll.first;

    if (fsb > 0) {
        UpdatePllSlider(fsb);
    }
}

double ChipsetPanel::GetTargetFsb() {
    return targetFsb;
}
