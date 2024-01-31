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

    wxCheckBox* checkBoxMinimizeToTray;
    wxCheckBox* checkBoxSaveWindowPosition;
    wxButton* buttonResetSettings;
    wxButton* buttonClose;
    wxButton* buttonApplySettings;

    void OnApplySettings(wxCommandEvent& event);
    void OnResetSettings(wxCommandEvent& event);
    void OnClose(wxCommandEvent& event);
    void OnMinimizeToTrayClick(wxCommandEvent& event);
    void OnSaveWindowPositionClick(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // SETTINGSWINDOW_H
