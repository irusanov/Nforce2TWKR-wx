#include "dialogs/ProfileWindowBase.h"

wxBEGIN_EVENT_TABLE(ProfileWindowBase, wxDialog)
    // EVT_BUTTON(wxID_APPLY, ProfileWindowBase::OnActionButtonClick)
    // EVT_SHOW(ProfileWindowBase::OnFormShow)
    EVT_CHECKBOX(wxID_ANY, ProfileWindowBase::OnSectionCheckBoxClick)
wxEND_EVENT_TABLE()

ProfileWindowBase::ProfileWindowBase(wxWindow* parent, const wxString& title, const wxString& okButtonText, const bool editable)
    : wxDialog(parent, wxID_ANY, title) {

    wxFont font = this->GetFont();
    font.SetFaceName(_T("Tahoma"));
    font.SetPointSize(8);
    this->SetFont(font);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* sizer = new wxFlexGridSizer(4, 2, 5, 10);

    unsigned int FLAG_READONLY = editable ? 0 : wxTE_READONLY;

    sizer->Add(new wxStaticText(this, wxID_ANY, "Name"), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
    textName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(240, 22), FLAG_READONLY);
    sizer->Add(textName, 1, wxRIGHT, 10);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Author"), 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
    textAuthor = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(240, 22), FLAG_READONLY);
    sizer->Add(textAuthor, 1, wxEXPAND | wxRIGHT, 10);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Comment"), 0, wxALIGN_TOP | wxLEFT | wxRIGHT, 10);
    textComment = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(240, 66), wxTE_MULTILINE | FLAG_READONLY);
    sizer->Add(textComment, 1, wxEXPAND | wxRIGHT, 10);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Sections"), 0, wxLEFT | wxRIGHT, 10);
    wxBoxSizer* checkboxSizer = new wxBoxSizer(wxVERTICAL);
    checkBoxTimings = new wxCheckBox(this, wxID_ANY, "Main Timings");
    checkBoxTimings->SetValue(true);
    checkboxSizer->Add(checkBoxTimings, 0, wxBOTTOM, 5);
    checkBoxDSSR = new wxCheckBox(this, wxID_ANY, "Drive Strength and Slew Rate");
    checkboxSizer->Add(checkBoxDSSR, 0, wxTOP | wxBOTTOM, 5);
    checkBoxAdvanced = new wxCheckBox(this, wxID_ANY, "Advanced");
    checkboxSizer->Add(checkBoxAdvanced, 0, wxTOP | wxBOTTOM, 5);
    checkBoxRomsip = new wxCheckBox(this, wxID_ANY, "ROMSIP");
    checkboxSizer->Add(checkBoxRomsip, 0, wxTOP | wxBOTTOM, 5);
    sizer->Add(checkboxSizer, 1, wxEXPAND | wxTOP, 1);

    mainSizer->Add(sizer, 1, wxEXPAND | wxTOP | wxBOTTOM, 10);

    // Buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonCancel = new wxButton(this, wxID_CANCEL, "Cancel", wxDefaultPosition, wxSize(70, 25));
    buttonSave = new wxButton(this, wxID_ANY, okButtonText, wxDefaultPosition, wxSize(70, 25));
    buttonSave->Bind(wxEVT_BUTTON, &ProfileWindowBase::OnActionButtonClick, this);

    buttonSizer->Add(buttonCancel, 0, wxRIGHT, 5);
    buttonSizer->Add(buttonSave, 0);
    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    SetSizerAndFit(mainSizer);
    CenterOnParent();
}

ProfileWindowBase::~ProfileWindowBase() {
    // Cleanup resources
}

void ProfileWindowBase::SetButtonsState() {
    buttonSave->Enable(
        checkBoxTimings->IsChecked() ||
        checkBoxDSSR->IsChecked() ||
        checkBoxAdvanced->IsChecked() ||
        checkBoxRomsip->IsChecked()
    );
}

void ProfileWindowBase::OnSectionCheckBoxClick(wxCommandEvent& event) {
    SetButtonsState();
}

void ProfileWindowBase::OnActionButtonClick(wxCommandEvent& event) {
    OnAction();
}

void ProfileWindowBase::OnAction() {
    Close();
}
