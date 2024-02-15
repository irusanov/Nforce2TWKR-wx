#ifndef PROFILE_PRELOAD_WINDOW_H
#define PROFILE_PRELOAD_WINDOW_H

#include "ProfileWindowBase.h"

class ProfilePreloadWindow : public ProfileWindowBase {
public:
    ProfilePreloadWindow(wxWindow* parent, ProfilesManager& profiles);
    ~ProfilePreloadWindow();

private:
    ProfilesManager* profiles;
    profile_metadata_t data;

    void OnAction() override;
    void OnTimerCloseWindow(wxTimerEvent& event);

    DECLARE_EVENT_TABLE();
};

#endif // PROFILE_PRELOAD_WINDOW_H

