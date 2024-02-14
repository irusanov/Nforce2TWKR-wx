
#include "dialogs/ProfilePreloadWindow.h"

wxBEGIN_EVENT_TABLE(ProfilePreloadWindow, wxDialog)

wxEND_EVENT_TABLE()

ProfilePreloadWindow::ProfilePreloadWindow(wxWindow* parent) : ProfileWindowBase(parent, _("Load Profile"), _("Load"), false) {
}

ProfilePreloadWindow::~ProfilePreloadWindow() {
    // Cleanup resources
}
