
#include "dialogs/ProfileSaveWindow.h"

wxBEGIN_EVENT_TABLE(ProfileSaveWindow, wxDialog)
    // EVT_BUTTON(wxID_ANY, ProfileSaveWindow::OnLoadButtonClick)
    // EVT_SHOW(ProfileSaveWindow::OnFormShow)
    // EVT_CHECKBOX(wxID_ANY, ProfileSaveWindow::OnSectionCheckBoxClick)
wxEND_EVENT_TABLE()

ProfileSaveWindow::ProfileSaveWindow(wxWindow* parent, const wxString& title)
    : wxDialog(parent, wxID_ANY, title) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* sizer = new wxFlexGridSizer(4, 2, 5, 10);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Name"), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
    sizer->Add(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(240, 22)), 1, wxRIGHT, 10);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Author"), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
    sizer->Add(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(240, 22)), 1, wxEXPAND | wxRIGHT, 10);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Comment"), 0, wxALIGN_TOP | wxLEFT | wxRIGHT, 10);
    sizer->Add(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(240, 66), wxTE_MULTILINE), 1, wxEXPAND | wxRIGHT, 10);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Sections"), 0, wxLEFT | wxRIGHT, 10);
    wxBoxSizer* checkboxSizer = new wxBoxSizer(wxVERTICAL);
    checkboxSizer->Add(new wxCheckBox(this, wxID_ANY, "Main Timings"), 0, wxBOTTOM, 5);
    checkboxSizer->Add(new wxCheckBox(this, wxID_ANY, "Drive Strength and Slew Rate"), 0, wxTOP | wxBOTTOM, 5);
    checkboxSizer->Add(new wxCheckBox(this, wxID_ANY, "Advanced"), 0, wxTOP | wxBOTTOM, 5);
    checkboxSizer->Add(new wxCheckBox(this, wxID_ANY, "ROMSIP"), 0, wxTOP | wxBOTTOM, 5);
    sizer->Add(checkboxSizer, 1, wxEXPAND | wxTOP, 1);

    mainSizer->Add(sizer, 1, wxEXPAND | wxTOP | wxBOTTOM, 10);

    // Buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonCancel = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(70, -1));
    buttonSave = new wxButton(this, wxID_SAVE, "Save...", wxDefaultPosition, wxSize(70, -1));

    buttonSizer->Add(buttonCancel, 0, wxRIGHT, 5);
    buttonSizer->Add(buttonSave, 0);
    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    SetSizerAndFit(mainSizer);
    CenterOnParent();
}

ProfileSaveWindow::~ProfileSaveWindow() {
    // Cleanup resources
}
