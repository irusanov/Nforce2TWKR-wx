#include "dialogs/ProfilePreloadWindow.h"

wxBEGIN_EVENT_TABLE(ProfilePreloadWindow, wxDialog)
    EVT_TIMER(wxID_ANY, ProfilePreloadWindow::OnTimerCloseWindow)
wxEND_EVENT_TABLE()

ProfilePreloadWindow::ProfilePreloadWindow(wxWindow* parent, ProfilesManager& profiles)
    : ProfileWindowBase(parent, _("Preview Profile"), _("Load"), false),
      profiles(&profiles) {

    wxFileDialog openFileDialog(this, "Load Profile", profiles.GetDefaultPath(), wxEmptyString, _("Profile (*.profile)|*.profile"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    // Show the file dialog
    if (openFileDialog.ShowModal() == wxID_OK) {
        wxString filePath = openFileDialog.GetPath();

        // Check if the file exists
        if (wxFileExists(filePath)) {
            data = profiles.ReadMetadata(filePath);

            checkBoxTimings->SetValue(data.options.timings);
            checkBoxDSSR->SetValue(data.options.dssr);
            checkBoxAdvanced->SetValue(data.options.advanced);
            checkBoxRomsip->SetValue(data.options.romsip);

            checkBoxTimings->Enable(data.options.timings);
            checkBoxDSSR->Enable(data.options.dssr);
            checkBoxAdvanced->Enable(data.options.advanced);
            checkBoxRomsip->Enable(data.options.romsip);

            textName->SetValue(data.options.name);
            textAuthor->SetValue(data.options.author);
            textComment->SetValue(data.options.comment);
        }
    } else {
        // Use a timer to destroy the window after a short delay
        Show(false);
        wxTimer* timer = new wxTimer(this, wxID_ANY);
        timer->StartOnce(1);
    }
}

void ProfilePreloadWindow::OnTimerCloseWindow(wxTimerEvent& event) {
    // Destroy the window after the timer expires
    Destroy();
}

ProfilePreloadWindow::~ProfilePreloadWindow() {
    delete profiles;
}

void ProfilePreloadWindow::OnAction() {
    profile_options_t options = {};

    options.timings = checkBoxTimings->IsChecked();
    options.dssr = checkBoxDSSR->IsChecked();
    options.advanced = checkBoxAdvanced->IsChecked();
    options.romsip = checkBoxRomsip->IsChecked();

    profiles->Load(data.path, options);
    ProfileWindowBase::OnAction();
}
