#include "dialogs/ProfilePreloadWindow.h"

wxBEGIN_EVENT_TABLE(ProfilePreloadWindow, wxDialog)
    EVT_BUTTON(wxID_ANY, ProfilePreloadWindow::OnLoadButtonClick)
    EVT_SHOW(ProfilePreloadWindow::OnFormShow)
    EVT_CHECKBOX(wxID_ANY, ProfilePreloadWindow::OnSectionCheckBoxClick)
wxEND_EVENT_TABLE()

ProfilePreloadWindow::ProfilePreloadWindow(wxWindow* parent, const wxString& title)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize) {
    // Initialize controls and layout here
    CenterOnParent();
}

ProfilePreloadWindow::~ProfilePreloadWindow() {
    // Cleanup resources
}

void ProfilePreloadWindow::SetApplyButtonState() {
    ButtonLoadProfile->Enable(
        CheckBoxTimings->GetValue() ||
        CheckBoxDSSR->GetValue() ||
        CheckBoxAdvanced->GetValue() ||
        CheckBoxRomsip->GetValue()
    );
}

void ProfilePreloadWindow::OnLoadButtonClick(wxCommandEvent& event) {
    profile_options_t Options = {};
    Options.timings = CheckBoxTimings->GetValue();
    Options.dssr = CheckBoxDSSR->GetValue();
    Options.advanced = CheckBoxAdvanced->GetValue();
    Options.romsip = CheckBoxRomsip->GetValue();

    // Replace this line with your wxWidgets equivalent to load profiles
    // MainForm->profiles.load(MainForm->profiles.previewMetadata.path, Options);

    EndModal(wxID_OK);
}

void ProfilePreloadWindow::OnFormShow(wxShowEvent& event) {
    // Initialize controls and update UI here
}

void ProfilePreloadWindow::OnSectionCheckBoxClick(wxCommandEvent& event) {
    SetApplyButtonState();
}
