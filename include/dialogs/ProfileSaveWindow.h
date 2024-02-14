#ifndef PROFILE_SAVE_WINDOW_H
#define PROFILE_SAVE_WINDOW_H

#include "ProfileWindowBase.h"

class ProfileSaveWindow : public ProfileWindowBase {
public:
    ProfileSaveWindow(wxWindow* parent, ProfilesManager& profiles);
    ~ProfileSaveWindow();

    void OnAction() override;

private:
    ProfilesManager* profiles;
    DECLARE_EVENT_TABLE();
};

#endif // PROFILE_SAVE_WINDOW_H

