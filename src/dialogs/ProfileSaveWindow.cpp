
#include "dialogs/ProfileSaveWindow.h"

wxBEGIN_EVENT_TABLE(ProfileSaveWindow, wxDialog)

wxEND_EVENT_TABLE()

ProfileSaveWindow::ProfileSaveWindow(wxWindow* parent, ProfilesManager& profiles)
    : ProfileWindowBase(parent, _("Save Profile"), _("Save...")),
    profiles(&profiles) {
}

ProfileSaveWindow::~ProfileSaveWindow() {
    // Cleanup resources
}

void ProfileSaveWindow::OnAction() {
    profile_options_t options = {};
    options.name = textName->GetValue();
    options.author = textAuthor->GetValue();
    options.comment = textComment->GetValue();
    options.timings = checkBoxTimings->IsChecked();
    options.dssr = checkBoxDSSR->IsChecked();
    options.advanced = checkBoxAdvanced->IsChecked();
    options.romsip = checkBoxRomsip->IsChecked();

    wxFileDialog saveFileDialog(this, _("Save profile as..."), profiles->GetDefaultPath(), options.name, _("Profile (*.profile)|*.profile"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_OK) {
        if (profiles->Save(saveFileDialog.GetPath(), options)) {
            Close();
        }
    }
}
