#ifndef VALIDATIONBOTDIALOG_H
#define VALIDATIONBOTDIALOG_H

#include <windows.h>
#include <functional>
#include <wx/wx.h>
#include <wx/timer.h>
#include "AppSettings.h"
#include "Cpu.h"
#include "components/TReadonlyTextBox.h"

class ValidationBotDialog : public wxDialog {
public:
    ValidationBotDialog(wxWindow* parent, const wxString& title, AppSettings& appSettings, Cpu* cpu);

    ~ValidationBotDialog();

    // Called after each FSB change when Ultra mode is off (keeps the main window in sync)
    void SetFsbChangedCallback(const std::function<void(double)>& callback);

private:
    enum BotState {
        BOT_IDLE,
        BOT_LAUNCHING,
        BOT_RUNNING
    };

    HWND hWndCpuz;
    AppSettings* settings;
    Cpu* cpuReference;

    BotState state;
    int launchAttempts;
    double targetFsb;
    int targetPll;
    std::function<void(double)> fsbChangedCallback;

    wxButton *buttonBotRun;
    wxButton *buttonSaveBotSettings;
    wxButton *buttonBrowseCpuz;

    wxTextCtrl *editCpuzPath;
    wxTextCtrl *editBotSleep;
    TReadonlyTextBox *panelCurrentFsb;
    TReadonlyTextBox *editCoreFrequency;
    wxTextCtrl *editFsbStep;

    wxStatusBar *statusBarBot;
    wxTimer timerBot;

    wxCheckBox *checkBoxUltra;
    wxCheckBox *checkBoxReverse;

    void InitControls();
    void CreateLayout();
    void LoadBotSettings();
    void SaveBotSettings();
    void UpdateFrequencyDisplay(bool measure);
    void SetStatus(const wxString& text);

    int GetIntValue(wxTextCtrl* ctrl, int defaultValue, int minValue, int maxValue);
    static HWND FindCpuzWindow();

    void StartBot();
    void StopBot(const wxString& reason);
    bool LaunchCpuz();
    void BotStep();

    void OnBotRunClick(wxCommandEvent& event);
    void OnBrowseCpuzClick(wxCommandEvent& event);
    void OnSaveBotSettingsClick(wxCommandEvent& event);
    void OnBotControlChange(wxCommandEvent& event);
    void OnTimerBot(wxTimerEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnCharHook(wxKeyEvent& event);
};

#endif // VALIDATIONBOTDIALOG_H
