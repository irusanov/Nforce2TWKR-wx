#ifndef VALIDATIONBOTDIALOG_H
#define VALIDATIONBOTDIALOG_H

#include <wx/wx.h>
#include <wx/timer.h>
#include "AppSettings.h"
#include "components/TReadonlyTextBox.h"

class ValidationBotDialog : public wxDialog {
public:
    ValidationBotDialog(wxWindow* parent, const wxString& title, AppSettings& appSettings);

    ~ValidationBotDialog();

private:
    HANDLE hWndCpuz;
    AppSettings* settings;

    wxButton *buttonBotRun;
    wxButton *buttonSaveBotSettings;
    wxButton *buttonBrowseCpuz;

    wxTextCtrl *editCpuzPath;
    wxTextCtrl *editBotSleep;
    TReadonlyTextBox *panelCurrentFsb;
    wxTextCtrl *editCoreFrequency;
    wxTextCtrl *editFsbStep;

    wxStatusBar *statusBarBot;
    wxTimer *timerBot;
    wxFileDialog *openDialogBot;

    wxCheckBox *checkBoxUltra;
	wxCheckBox *checkBoxReverse;

    void InitControls();
    void CreateLayout();
    void SaveBotSettings();
    void SaveBotSettingsClick(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // VALIDATIONBOTDIALOG_H
