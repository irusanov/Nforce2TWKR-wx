#ifndef PROFILE_PRELOAD_WINDOW_H
#define PROFILE_PRELOAD_WINDOW_H

#include "ProfileWindowBase.h"

class ProfilePreloadWindow : public ProfileWindowBase {
public:
    ProfilePreloadWindow(wxWindow* parent, ProfilesManager& profiles, const wxString& filePath);
    ~ProfilePreloadWindow();

private:
    ProfilesManager* profiles;

    void OnAction() override;
};

#endif // PROFILE_PRELOAD_WINDOW_H

