#include "dialogs/ProfilePreloadWindow.h"

ProfilePreloadWindow::ProfilePreloadWindow(wxWindow* parent, ProfilesManager& profiles, const wxString& filePath)
    : ProfileWindowBase(parent, _("Preview Profile"), _("Load"), false),
      profiles(&profiles) {

    // data is the base class member (profile metadata)
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

    buttonSave->Enable(data.options.timings || data.options.dssr || data.options.advanced || data.options.romsip);
}

ProfilePreloadWindow::~ProfilePreloadWindow() {
    // profiles is owned by the main frame, don't delete it
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
