#ifndef PROFILE_PRELOAD_WINDOW_H
#define PROFILE_PRELOAD_WINDOW_H

#include "ProfileWindowBase.h"

class ProfilePreloadWindow : public ProfileWindowBase {
public:
    ProfilePreloadWindow(wxWindow* parent);
    ~ProfilePreloadWindow();

private:
    DECLARE_EVENT_TABLE();
};

#endif // PROFILE_PRELOAD_WINDOW_H

