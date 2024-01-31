#include "ChipsetPanel.h"

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
    wxStaticBox* staticBoxGeneral = generalGroupSizer->GetStaticBox();
    rowSizer->Add(generalGroupSizer, 1, wxEXPAND);

    // "S2K"
    wxStaticBoxSizer* s2kGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("S2K"));
    wxStaticBox* staticBoxS2k = s2kGroupSizer->GetStaticBox();
    rowSizer->Add(s2kGroupSizer, 1, wxEXPAND | wxLEFT, 5);

    // "FSB"
    wxStaticBoxSizer* fsbGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("FSB"));
    wxStaticBox* staticBoxFsb = fsbGroupSizer->GetStaticBox();

    // "AGP"
    wxStaticBoxSizer* agpGroupSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("AGP / PCI"));
    wxStaticBox* staticBoxAgp = agpGroupSizer->GetStaticBox();

    mainSizer->Add(rowSizer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(fsbGroupSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    mainSizer->Add(agpGroupSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

    // Set the main sizer for the frame
    SetSizerAndFit(mainSizer);
}

