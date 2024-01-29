#include "InfoPanel.h"

InfoPanel::InfoPanel(wxWindow* parent, Cpu* cpu)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxPanelNameStr),
    cpuReference(cpu)
{
    AddControls();
}

void InfoPanel::OnSetFocus(wxFocusEvent& event) {
    // Prevent the control from getting focus
    event.Skip(false);
}

// Label helper
void InfoPanel::Label(wxBoxSizer* sizer, wxWindow* parent, wxString label = wxEmptyString, int width = -1, bool expand = false) {
    if (sizer == wxNullPtr)
        return;

    sizer->Add(new wxStaticText(parent, wxID_ANY, label,
        wxDefaultPosition, wxSize(width, -1), wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL),
        expand ? 1 : 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 0);
}

// Text field helper
void InfoPanel::TextBox(wxBoxSizer* sizer, wxWindow* parent, wxString value = wxEmptyString, int width = -1, bool expand = false) {
    if (sizer == wxNullPtr)
        return;

    wxTextCtrl* textCtrl = new wxTextCtrl(parent, wxID_ANY, value, wxDefaultPosition, wxSize(width, 18), wxTE_READONLY | wxTE_CENTER | wxBORDER_STATIC);
    textCtrl->Bind(wxEVT_SET_FOCUS, &InfoPanel::OnSetFocus, this);
    textCtrl->SetCursor(wxCursor(wxCURSOR_DEFAULT));
    textCtrl->SetForegroundColour(wxColour(0, 0, 128));
    textCtrl->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    // wxFont font = textCtrl->GetFont();
    // font.SetPointSize(font.GetPointSize() - 1);
    // textCtrl->SetFont(font);
    sizer->Add(textCtrl, expand ? 1 : 0, wxEXPAND | wxLEFT, 5);
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
    TextBox(s1, staticBoxCPU, cpuInfo.cpuName, -1, true);
    cpuGroupSizer->Add(s1, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s2 = new wxBoxSizer(wxHORIZONTAL);
    Label(s2, staticBoxCPU, _("Core"), 60);
    TextBox(s2, staticBoxCPU, cpuInfo.codeName, -1, true);
    Label(s2, staticBoxCPU, _("Revision"), 80);
    TextBox(s2, staticBoxCPU, wxEmptyString, 35);
    cpuGroupSizer->Add(s2, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s3 = new wxBoxSizer(wxHORIZONTAL);
    Label(s3, staticBoxCPU, _("Family"), 60);
    TextBox(s3, staticBoxCPU, wxString::Format("%d", cpuInfo.family), 35);
    Label(s3, staticBoxCPU, _("Model"), -1, true);
    TextBox(s3, staticBoxCPU, wxString::Format("%d", cpuInfo.model), 35);
    Label(s3, staticBoxCPU, _("Stepping"), 80);
    TextBox(s3, staticBoxCPU, wxString::Format("%d", cpuInfo.stepping), 35);
    cpuGroupSizer->Add(s3, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s4 = new wxBoxSizer(wxHORIZONTAL);
    Label(s4, staticBoxCPU, _("Ext Family"), 60);
    TextBox(s4, staticBoxCPU, wxString::Format("%d", cpuInfo.extFamily), 35);
    Label(s4, staticBoxCPU, _("Ext Model"), -1, true);
    TextBox(s4, staticBoxCPU, wxString::Format("%d", cpuInfo.extModel), 35);
    Label(s4, staticBoxCPU, _("Man Rev"), 80);
    TextBox(s4, staticBoxCPU, wxString::Format("%d", cpuInfo.manID.minorRev), 35);
    cpuGroupSizer->Add(s4, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    mainSizer->Add(cpuGroupSizer, 0, wxEXPAND | wxALL, 5);

    // Second Row: "Clocks" and "Cache"
    wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

    // "Clocks"
    wxStaticBoxSizer* clocksGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Clocks"));
    wxStaticBox* staticBoxClocks = clocksGroupSizer->GetStaticBox();

    wxBoxSizer* s5 = new wxBoxSizer(wxHORIZONTAL);
    Label(s5, staticBoxClocks, _("Core"), 60);
    TextBox(s5, staticBoxClocks, wxString::Format("%.2f MHz", cpuInfo.frequency), 80);
    clocksGroupSizer->Add(s5, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s6 = new wxBoxSizer(wxHORIZONTAL);
    Label(s6, staticBoxClocks, _("Multi"), 60);
    TextBox(s6, staticBoxClocks, wxString::Format("x %.1f", cpuInfo.multi), 80);
    clocksGroupSizer->Add(s6, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s7 = new wxBoxSizer(wxHORIZONTAL);
    Label(s7, staticBoxClocks, _("FSB"), 60);
    TextBox(s7, staticBoxClocks, wxString::Format("%.2f MHz", cpuInfo.fsb), 80);
    clocksGroupSizer->Add(s7, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s8 = new wxBoxSizer(wxHORIZONTAL);
    Label(s8, staticBoxClocks, _("DRAM"), 60);
    TextBox(s8, staticBoxClocks, wxString::Format("%.2f MHz", cpuInfo.dram), 80);
    clocksGroupSizer->Add(s8, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s9 = new wxBoxSizer(wxHORIZONTAL);
    Label(s9, staticBoxClocks, _("FSB:DRAM"), 60);
    TextBox(s9, staticBoxClocks, wxString::Format("%d:%d", cpuInfo.fsbDiv, cpuInfo.dramDiv), 80);
    clocksGroupSizer->Add(s9, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    rowSizer->Add(clocksGroupSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

    // "Cache"
    wxStaticBoxSizer* cacheGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Cache"));
    wxStaticBox* staticBoxCache = cacheGroupSizer->GetStaticBox();

    wxBoxSizer* s10 = new wxBoxSizer(wxHORIZONTAL);
    Label(s10, staticBoxCache, _("L1 Data"), -1, true);
    TextBox(s10, staticBoxCache, wxString::Format("%.d KBytes", cpuInfo.l1DataCache), 80);
    cacheGroupSizer->Add(s10, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s11 = new wxBoxSizer(wxHORIZONTAL);
    Label(s11, staticBoxCache, _("L1 Inst."), -1, true);
    TextBox(s11, staticBoxCache, wxString::Format("%.d KBytes", cpuInfo.l1InstCache), 80);
    cacheGroupSizer->Add(s11, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s12 = new wxBoxSizer(wxHORIZONTAL);
    Label(s12, staticBoxCache, _("Level 1"), -1, true);
    TextBox(s12, staticBoxCache, wxString::Format("%.d KBytes", cpuInfo.l1Cache), 80);
    cacheGroupSizer->Add(s12, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    wxBoxSizer* s13 = new wxBoxSizer(wxHORIZONTAL);
    Label(s13, staticBoxCache, _("Level 2"), -1, true);
    TextBox(s13, staticBoxCache, wxString::Format("%.d KBytes", cpuInfo.l2Cache), 80);
    cacheGroupSizer->Add(s13, 0, wxEXPAND | wxALL, INFO_PANEL_ROW_SPACING);

    rowSizer->Add(cacheGroupSizer, 1, wxEXPAND | wxRIGHT | wxBOTTOM, 5);

    // Add the row sizer to the main sizer
    mainSizer->Add(rowSizer, 0, wxEXPAND);

    // Set the main sizer for the frame
    SetSizerAndFit(mainSizer);

    // Center the frame on the screen
    Center();
}
