#ifndef VALIDATIONBOTDIALOG_H
#define VALIDATIONBOTDIALOG_H

#include <wx/wx.h>
#include <wx/timer.h>
#include "AppSettings.h"

class ValidationBotDialog : public wxDialog {
public:
    ValidationBotDialog(wxWindow* parent, const wxString& title, AppSettings& appSettings);

    ~ValidationBotDialog();

private:
    HWND FindCpuzWindow();
    void OnButtonBotRunClick(wxCommandEvent& event);
    void OnTimerBot(wxTimerEvent& event);

    AppSettings* settings;
    wxTimer timerBot;
    wxTextCtrl* editCpuzPath;
    wxTextCtrl* editBotSleep;
    wxTextCtrl* editFsbStep;
    wxCheckBox* checkBoxUltra;
    wxStaticText* panelCurrentFsb;
    wxStaticText* editCoreFrequency;
    wxButton* buttonSaveBotSettings;
    wxStatusBar* statusBarBot;
    wxButton* buttonBotRun;
    wxButton* buttonBrowseCpuz;
    wxFileDialog* openFileDialogBot;
    HANDLE hWndCpuz;

    void InitControls();
    void CreateLayout();
    void LoadBotSettings();
    void SaveBotSettings();
    void UpdateBotControlsState();
    void UpdateFrequencyDisplay();
    void CheckUltra();
    void CloseValidationBotDialog(wxCloseEvent& event);
    void BrowseCpuzPath(wxCommandEvent& event);
    void SaveBotSettingsClick(wxCommandEvent& event);
    void BotControlChange(wxCommandEvent& event);
    void KeyUp(wxKeyEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // VALIDATIONBOTDIALOG_H
