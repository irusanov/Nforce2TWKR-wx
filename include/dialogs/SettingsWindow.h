#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <wx/wx.h>
#include "AppSettings.h"

class SettingsWindow : public wxDialog {
public:
    SettingsWindow(wxWindow* parent, const wxString& title, AppSettings& appSettings);

private:
    void LoadOptions();

    AppSettings* settings;

    wxCheckBox* CheckBoxMinimizeToTray;
    wxCheckBox* CheckBoxSaveWindowPosition;
    wxButton* ButtonResetSettings;
    wxButton* ButtonClose;
    wxButton* ButtonApplySettings;

    void OnApplySettings(wxCommandEvent& event);
    void OnResetSettings(wxCommandEvent& event);
    void OnClose(wxCommandEvent& event);
    void OnMinimizeToTrayClick(wxCommandEvent& event);
    void OnSaveWindowPositionClick(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // SETTINGSWINDOW_H
