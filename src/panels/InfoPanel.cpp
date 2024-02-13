#include "InfoPanel.h"
#include "components/TReadonlyTextBox.h"

InfoPanel::InfoPanel(wxWindow* parent, Cpu* cpu)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxPanelNameStr),
      cpuReference(cpu) {
    AddControls();
}

// Label helper
void InfoPanel::Label(wxBoxSizer* sizer, wxWindow* parent, wxString label, int width, bool expand) {
    if (sizer == wxNullPtr)
        return;

    sizer->Add(new wxStaticText(parent, wxID_ANY, label,
                                wxDefaultPosition, wxSize(width, -1), wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL),
               expand ? 1 : 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 0);
}

void InfoPanel::AddControls() {
    // Create the main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    cpu_info_t cpuInfo = cpuReference->GetCpuInfo();

    // "CPU"
    wxStaticBoxSizer* cpuGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("CPU"));
    wxStaticBox* staticBoxCPU = cpuGroupSizer->GetStaticBox();

    wxBoxSizer* s1 = new wxBoxSizer(wxHORIZONTAL);
    Label(s1, staticBoxCPU, _("Name"), 60);
    s1->Add(new TReadonlyTextBox(staticBoxCPU, cpuInfo.cpuName), 1, wxEXPAND | wxLEFT, 5);
    cpuGroupSizer->Add(s1, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s2 = new wxBoxSizer(wxHORIZONTAL);
    Label(s2, staticBoxCPU, _("Core"), 60);
    s2->Add(new TReadonlyTextBox(staticBoxCPU, cpuInfo.codeName), 1, wxEXPAND | wxLEFT, 5);
    Label(s2, staticBoxCPU, _("Revision"), 80);
    s2->Add(new TReadonlyTextBox(staticBoxCPU, wxEmptyString, 35), 0, wxEXPAND | wxLEFT, 5);
    cpuGroupSizer->Add(s2, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s3 = new wxBoxSizer(wxHORIZONTAL);
    Label(s3, staticBoxCPU, _("Family"), 60);
    s3->Add(new TReadonlyTextBox(staticBoxCPU, wxString::Format("%d", cpuInfo.family), 35), 0, wxEXPAND | wxLEFT, 5);
    Label(s3, staticBoxCPU, _("Model"), -1, true);
    s3->Add(new TReadonlyTextBox(staticBoxCPU, wxString::Format("%d", cpuInfo.model), 35), 0, wxEXPAND | wxLEFT, 5);
    Label(s3, staticBoxCPU, _("Stepping"), 80);
    s3->Add(new TReadonlyTextBox(staticBoxCPU, wxString::Format("%d", cpuInfo.stepping), 35), 0, wxEXPAND | wxLEFT, 5);
    cpuGroupSizer->Add(s3, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s4 = new wxBoxSizer(wxHORIZONTAL);
    Label(s4, staticBoxCPU, _("Ext Family"), 60);
    s4->Add(new TReadonlyTextBox(staticBoxCPU, wxString::Format("%d", cpuInfo.extFamily), 35), 0, wxEXPAND | wxLEFT, 5);
    Label(s4, staticBoxCPU, _("Ext Model"), -1, true);
    s4->Add(new TReadonlyTextBox(staticBoxCPU, wxString::Format("%d", cpuInfo.extModel), 35), 0, wxEXPAND | wxLEFT, 5);
    Label(s4, staticBoxCPU, _("Man Rev"), 80);
    s4->Add(new TReadonlyTextBox(staticBoxCPU, wxString::Format("%d", cpuInfo.manID.minorRev), 35), 0, wxEXPAND | wxLEFT, 5);
    cpuGroupSizer->Add(s4, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    mainSizer->Add(cpuGroupSizer, 0, wxEXPAND | wxALL, 5);

    // Second Row: "Clocks" and "Cache"
    wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

    // "Clocks"
    wxStaticBoxSizer* clocksGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Clocks"));
    wxStaticBox* staticBoxClocks = clocksGroupSizer->GetStaticBox();

    wxBoxSizer* s5 = new wxBoxSizer(wxHORIZONTAL);
    Label(s5, staticBoxClocks, _("Core"), 60);
    s5->Add(new TReadonlyTextBox(staticBoxClocks, wxString::Format("%.2f MHz", cpuInfo.frequency), 80, _T("FrequencyTextBox")), 0, wxEXPAND | wxLEFT, 5);
    clocksGroupSizer->Add(s5, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s6 = new wxBoxSizer(wxHORIZONTAL);
    Label(s6, staticBoxClocks, _("Multi"), 60);
    s6->Add(new TReadonlyTextBox(staticBoxClocks, wxString::Format("x %.1f", cpuInfo.multi), 80, _T("MultiTextBox")), 0, wxEXPAND | wxLEFT, 5);
    clocksGroupSizer->Add(s6, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s7 = new wxBoxSizer(wxHORIZONTAL);
    Label(s7, staticBoxClocks, _("FSB"), 60);
    s7->Add(new TReadonlyTextBox(staticBoxClocks, wxString::Format("%.2f MHz", cpuInfo.fsb), 80, _T("FsbTextBox")), 0, wxEXPAND | wxLEFT, 5);
    clocksGroupSizer->Add(s7, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s8 = new wxBoxSizer(wxHORIZONTAL);
    Label(s8, staticBoxClocks, _("DRAM"), 60);
    s8->Add(new TReadonlyTextBox(staticBoxClocks, wxString::Format("%.2f MHz", cpuInfo.dram), 80, _T("DramTextBox")), 0, wxEXPAND | wxLEFT, 5);
    clocksGroupSizer->Add(s8, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s9 = new wxBoxSizer(wxHORIZONTAL);
    Label(s9, staticBoxClocks, _("FSB:DRAM"), 60);
    s9->Add(new TReadonlyTextBox(staticBoxClocks, wxString::Format("%d:%d", cpuInfo.fsbDiv, cpuInfo.dramDiv), 80), 0, wxEXPAND | wxLEFT, 5);
    clocksGroupSizer->Add(s9, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    rowSizer->Add(clocksGroupSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

    // "Cache"
    wxStaticBoxSizer* cacheGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Cache"));
    wxStaticBox* staticBoxCache = cacheGroupSizer->GetStaticBox();

    wxBoxSizer* s10 = new wxBoxSizer(wxHORIZONTAL);
    Label(s10, staticBoxCache, _("L1 Data"), -1, true);
    s10->Add(new TReadonlyTextBox(staticBoxCache, wxString::Format("%.d KBytes", cpuInfo.l1DataCache), 80), 0, wxEXPAND | wxLEFT, 5);
    cacheGroupSizer->Add(s10, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s11 = new wxBoxSizer(wxHORIZONTAL);
    Label(s11, staticBoxCache, _("L1 Inst."), -1, true);
    s11->Add(new TReadonlyTextBox(staticBoxCache, wxString::Format("%.d KBytes", cpuInfo.l1InstCache), 80), 0, wxEXPAND | wxLEFT, 5);
    cacheGroupSizer->Add(s11, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s12 = new wxBoxSizer(wxHORIZONTAL);
    Label(s12, staticBoxCache, _("Level 1"), -1, true);
    s12->Add(new TReadonlyTextBox(staticBoxCache, wxString::Format("%.d KBytes", cpuInfo.l1Cache), 80), 0, wxEXPAND | wxLEFT, 5);
    cacheGroupSizer->Add(s12, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s13 = new wxBoxSizer(wxHORIZONTAL);
    Label(s13, staticBoxCache, _("Level 2"), -1, true);
    s13->Add(new TReadonlyTextBox(staticBoxCache, wxString::Format("%.d KBytes", cpuInfo.l2Cache), 80), 0, wxEXPAND | wxLEFT, 5);
    cacheGroupSizer->Add(s13, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    rowSizer->Add(cacheGroupSizer, 1, wxEXPAND | wxRIGHT | wxBOTTOM, 5);

    // Add the row sizer to the main sizer
    mainSizer->Add(rowSizer, 0, wxEXPAND);

    // Set the main sizer for the frame
    SetSizerAndFit(mainSizer);

    // Center the frame on the screen
    Center();
}

// TODO: Add pointers to needed controls in header
void InfoPanel::Update() {
    cpuReference->RefreshCpuSpeed();
    cpu_info_t cpuInfo = cpuReference->GetCpuInfo();
    wxTextCtrl* obj = static_cast<wxTextCtrl *>(FindWindowByName("FrequencyTextBox"));
    ((wxTextCtrl *)obj)->SetValue(wxString::Format("%.2f MHz", cpuInfo.frequency));
    obj = static_cast<wxTextCtrl *>(FindWindowByName("MultiTextBox"));
    ((wxTextCtrl *)obj)->SetValue(wxString::Format("x %.1f", cpuInfo.multi));
    obj = static_cast<wxTextCtrl *>(FindWindowByName("FsbTextBox"));
    ((wxTextCtrl *)obj)->SetValue(wxString::Format("%.2f MHz", cpuInfo.fsb));
    obj = static_cast<wxTextCtrl *>(FindWindowByName("DramTextBox"));
    ((wxTextCtrl *)obj)->SetValue(wxString::Format("%.2f MHz", cpuInfo.dram));
}
