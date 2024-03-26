// ValidationBotDialog.cpp

#include "dialogs/ValidationBotWindow.h"

wxBEGIN_EVENT_TABLE(ValidationBotDialog, wxDialog)
    EVT_BUTTON(wxID_ANY, ValidationBotDialog::OnButtonBotRunClick)
    EVT_TIMER(wxID_ANY, ValidationBotDialog::OnTimerBot)
    EVT_CLOSE(ValidationBotDialog::CloseValidationBotDialog)
    EVT_BUTTON(wxID_ANY, ValidationBotDialog::BrowseCpuzPath)
    EVT_BUTTON(wxID_ANY, ValidationBotDialog::SaveBotSettingsClick)
    EVT_TEXT(wxID_ANY, ValidationBotDialog::BotControlChange)
    EVT_KEY_UP(ValidationBotDialog::KeyUp)
wxEND_EVENT_TABLE()

ValidationBotDialog::ValidationBotDialog(wxWindow* parent, const wxString& title, AppSettings& appSettings)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition), hWndCpuz(NULL),
      settings(&appSettings) {
    InitControls();
    CreateLayout();
    LoadBotSettings();
    UpdateFrequencyDisplay();
}

ValidationBotDialog::~ValidationBotDialog() {
    if (timerBot.IsRunning()) {
        timerBot.Stop();
    }
}

void ValidationBotDialog::InitControls() {
    editCpuzPath = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    editBotSleep = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    editFsbStep = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    checkBoxUltra = new wxCheckBox(this, wxID_ANY, wxT("Ultra"), wxDefaultPosition, wxDefaultSize, 0);
    panelCurrentFsb = new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    editCoreFrequency = new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    buttonSaveBotSettings = new wxButton(this, wxID_ANY, wxT("Save Settings"), wxDefaultPosition, wxDefaultSize, 0);
    statusBarBot = new wxStatusBar(this, wxID_ANY, 0);
    buttonBotRun = new wxButton(this, wxID_ANY, wxT("Run"), wxDefaultPosition, wxDefaultSize, 0);
    buttonBrowseCpuz = new wxButton(this, wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0);
    openFileDialogBot = new wxFileDialog(this, wxT("Select CPU-Z Path"), wxEmptyString, wxEmptyString,
                                         wxT("Executable files (*.exe)|*.exe"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
}

void ValidationBotDialog::CreateLayout() {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 2, 5, 5);
    gridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("CPU-Z Path:")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(editCpuzPath, 1, wxEXPAND);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Sleep Interval (seconds):")), 0,
                   wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(editBotSleep, 1, wxEXPAND);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("FSB Step:")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(editFsbStep, 1, wxEXPAND);

    gridSizer->Add(checkBoxUltra, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Current FSB:")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(panelCurrentFsb, 0, wxEXPAND);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Core Frequency:")), 0,
                   wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(editCoreFrequency, 0, wxEXPAND);

    sizer->Add(gridSizer, 1, wxEXPAND | wxALL, 10);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(buttonSaveBotSettings, 0, wxALIGN_LEFT);
    buttonSizer->Add(buttonBrowseCpuz, 0, wxALIGN_LEFT);
    buttonSizer->Add(buttonBotRun, 0, wxALIGN_RIGHT);

    sizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);
    sizer->Add(statusBarBot, 0, wxEXPAND | wxALL, 5);

    SetSizerAndFit(sizer);
    CenterOnParent();
}

void ValidationBotDialog::LoadBotSettings() {
    editCpuzPath->SetValue(settings->CpuzPath);
    editBotSleep->SetValue(wxString::Format("%d", settings->Sleep));
    editFsbStep->SetValue(wxString::Format("%d", settings->Step));
    checkBoxUltra->SetValue(settings->Ultra);

    //panelCurrentFsb->SetLabelText(wxString::Format("%.2f MHz", cpu_info.fsb));
    //editCoreFrequency->SetLabelText(wxString::Format("%.2f MHz", cpu_info.frequency));

    buttonSaveBotSettings->Enable(false);
}

void ValidationBotDialog::SaveBotSettings() {
    settings->CpuzPath = editCpuzPath->GetValue();

    long sleepValue;
    editBotSleep->GetValue().ToLong(&sleepValue);
    settings->Sleep = static_cast<int>(sleepValue);

    long int fsbValue;
    editFsbStep->GetValue().ToLong(&fsbValue);
    settings->Step = static_cast<int>(fsbValue);

    settings->Ultra = checkBoxUltra->GetValue();
    buttonSaveBotSettings->Enable(false);
    statusBarBot->SetStatusText("Bot settings saved.");
}

void ValidationBotDialog::UpdateBotControlsState() {
    buttonSaveBotSettings->Enable(true);
}

void ValidationBotDialog::UpdateFrequencyDisplay() {
    if (checkBoxUltra->GetValue()) {
        editCoreFrequency->SetLabelText("N/A");
    } else {
        // TODO: Add appropriate code to get frequency from the main form
        // editCoreFrequency->SetLabelText(wxString::Format("%.2f MHz", MainForm->cpu_info.frequency));
    }
}

void ValidationBotDialog::CheckUltra() {
    // TODO: Add appropriate code to handle Ultra checkbox logic
}

void ValidationBotDialog::CloseValidationBotDialog(wxCloseEvent& event) {
    // TODO: Add appropriate code to handle dialog close event
}

void ValidationBotDialog::BrowseCpuzPath(wxCommandEvent& event) {
    if (openFileDialogBot->ShowModal() == wxID_OK) {
        editCpuzPath->SetValue(openFileDialogBot->GetPath());
    }
}

void ValidationBotDialog::SaveBotSettingsClick(wxCommandEvent& event) {
    SaveBotSettings();
}

void ValidationBotDialog::BotControlChange(wxCommandEvent& event) {
    UpdateBotControlsState();
    CheckUltra();
}

void ValidationBotDialog::KeyUp(wxKeyEvent& event) {
    if (event.GetKeyCode() == WXK_ESCAPE) {
        Close();
    }
}

HWND ValidationBotDialog::FindCpuzWindow() {
    // TODO: Add appropriate code to find the CPU-Z window
    return NULL;
}

void ValidationBotDialog::OnButtonBotRunClick(wxCommandEvent& event) {
    long int interval = 6;
    editBotSleep->GetValue().ToLong(&interval);
    int convertedInterval = static_cast<int>(interval);

    hWndCpuz = FindCpuzWindow();

    if (timerBot.IsRunning()) {
        timerBot.Stop();
        statusBarBot->SetStatusText("Bot stopped.");
        buttonBotRun->SetLabel("Run");
    } else {
        if (hWndCpuz == NULL) {
            wxString path = editCpuzPath->GetValue();

            if (path.IsEmpty()) {
                statusBarBot->SetStatusText("CPU-Z path not selected and no CPU-Z running.");
                return;
            }

            buttonBotRun->Enable(false);
            statusBarBot->SetStatusText("Launching CPU-Z");

            std::wstring path_wstr(path.begin(), path.end());

            SHELLEXECUTEINFO ShExecInfo = {0};
            ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            ShExecInfo.hwnd = NULL;
            ShExecInfo.lpVerb = _T("open");
            ShExecInfo.lpFile = path.c_str();
            ShExecInfo.lpParameters = NULL;
            ShExecInfo.lpDirectory = NULL;
            ShExecInfo.nShow = SW_SHOW;
            ShExecInfo.hInstApp = NULL;

            if (!ShellExecuteEx(&ShExecInfo)) {
                statusBarBot->SetStatusText("CPU-Z not found, please check path to cpu_z.exe");
                buttonBotRun->Enable(true);
                buttonBotRun->SetLabel("Run");
                return;
            }

            HANDLE hThread;
            DWORD dwRet;
            do {
                dwRet = ::WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

                if (dwRet != WAIT_OBJECT_0) {
                    MSG msg;
                    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }
            } while ((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED));

            CloseHandle(ShExecInfo.hProcess);

            do {
                hWndCpuz = FindCpuzWindow();
            } while (hWndCpuz == NULL);
        }

        buttonBotRun->Enable(true);
        buttonBotRun->SetLabel("Stop");

        timerBot.Start(convertedInterval * 1000);
        statusBarBot->SetStatusText("Running");
    }
}

void ValidationBotDialog::OnTimerBot(wxTimerEvent& event) {
    // TODO: Add appropriate code to handle timer event
}

// TODO: Add other methods as needed

