// ValidationBotWindow.cpp
//
// Auto Validation Bot
// Ported from the VCL version (Windows/ValidationBot.cpp).
//
// On each tick the bot brings CPU-Z to the foreground, presses F7 (save validation)
// and then moves the FSB to the next (or previous, in reverse mode) PLL step.

// SendInput/INPUT need at least Windows 2000 SP3 headers; target XP
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include "dialogs/ValidationBotWindow.h"
#include <shellapi.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/valtext.h>

// Polling interval while waiting for a freshly launched CPU-Z to show its main window
#define BOT_LAUNCH_POLL_MS          500
// Give up waiting for CPU-Z after this many polls (60 seconds)
#define BOT_LAUNCH_MAX_ATTEMPTS     120

#define BOT_MIN_SLEEP               1
#define BOT_MAX_SLEEP               3600
#define BOT_DEFAULT_SLEEP           6
#define BOT_MAX_STEP                100

ValidationBotDialog::ValidationBotDialog(wxWindow* parent, const wxString& title, AppSettings& appSettings, Cpu* cpu)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition),
        hWndCpuz(NULL),
        settings(&appSettings),
        cpuReference(cpu),
        state(BOT_IDLE),
        launchAttempts(0),
        targetFsb(0),
        targetPll(0) {

    wxFont font = this->GetFont();
    font.SetFaceName(_T("Tahoma"));
    font.SetPointSize(8);
    this->SetFont(font);

    InitControls();
    CreateLayout();
    LoadBotSettings();
    UpdateFrequencyDisplay(true);

    timerBot.SetOwner(this);
    Bind(wxEVT_TIMER, &ValidationBotDialog::OnTimerBot, this, timerBot.GetId());
    Bind(wxEVT_CLOSE_WINDOW, &ValidationBotDialog::OnClose, this);

    buttonBotRun->Bind(wxEVT_BUTTON, &ValidationBotDialog::OnBotRunClick, this);
    buttonBrowseCpuz->Bind(wxEVT_BUTTON, &ValidationBotDialog::OnBrowseCpuzClick, this);
    buttonSaveBotSettings->Bind(wxEVT_BUTTON, &ValidationBotDialog::OnSaveBotSettingsClick, this);

    editCpuzPath->Bind(wxEVT_TEXT, &ValidationBotDialog::OnBotControlChange, this);
    editBotSleep->Bind(wxEVT_TEXT, &ValidationBotDialog::OnBotControlChange, this);
    editFsbStep->Bind(wxEVT_TEXT, &ValidationBotDialog::OnBotControlChange, this);
    checkBoxUltra->Bind(wxEVT_CHECKBOX, &ValidationBotDialog::OnBotControlChange, this);
    checkBoxReverse->Bind(wxEVT_CHECKBOX, &ValidationBotDialog::OnBotControlChange, this);

    buttonBotRun->SetFocus();
}

ValidationBotDialog::~ValidationBotDialog() {
    if (timerBot.IsRunning()) {
        timerBot.Stop();
    }
}

void ValidationBotDialog::InitControls() {
    wxTextValidator digitsValidator(wxFILTER_DIGITS);

    editCpuzPath = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 18), 0);
    editBotSleep = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 18), 0, digitsValidator);
    editFsbStep = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 18), 0, digitsValidator);
    checkBoxUltra = new wxCheckBox(this, wxID_ANY, wxT("Ultra (no update)"), wxDefaultPosition, wxDefaultSize, 0);
    checkBoxReverse = new wxCheckBox(this, wxID_ANY, wxT("Reverse direction"), wxDefaultPosition, wxDefaultSize, 0);
    panelCurrentFsb = new TReadonlyTextBox(this, wxEmptyString, 80);
    editCoreFrequency = new TReadonlyTextBox(this, wxEmptyString, 80);
    buttonSaveBotSettings = new wxButton(this, wxID_SAVE, wxT("Save Settings"), wxDefaultPosition, wxDefaultSize, 0);
    buttonBotRun = new wxButton(this, wxID_ANY, wxT("Run"), wxDefaultPosition, wxDefaultSize, 0);
    statusBarBot = new wxStatusBar(this, wxID_ANY, 0);
    buttonBrowseCpuz = new wxButton(this, wxID_ANY, wxT("Browse..."), wxDefaultPosition, wxSize(80, 18), 0);
}

void ValidationBotDialog::CreateLayout() {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* s1 = new wxBoxSizer(wxHORIZONTAL);
    s1->Add(new wxStaticText(this, wxID_ANY, _T("CPU-Z Path"), wxDefaultPosition, wxSize(80, -1)), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
    s1->Add(editCpuzPath, 1, wxEXPAND | wxLEFT, 5);
    s1->Add(buttonBrowseCpuz, 0, wxLEFT, 5);
    sizer->Add(s1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    wxBoxSizer* s2 = new wxBoxSizer(wxHORIZONTAL);
    s2->Add(new wxStaticText(this, wxID_ANY, _T("Sleep"), wxDefaultPosition, wxSize(80, -1)), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
    s2->Add(editBotSleep, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
    s2->Add(new wxStaticText(this, wxID_ANY, _T("s")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
    s2->Add(new wxStaticText(this, wxID_ANY, _T("FSB")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    s2->Add(panelCurrentFsb, 0, wxLEFT, 5);
    sizer->Add(s2, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    wxBoxSizer* s3 = new wxBoxSizer(wxHORIZONTAL);
    s3->Add(new wxStaticText(this, wxID_ANY, _T("Step"), wxDefaultPosition, wxSize(80, -1)), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
    s3->Add(editFsbStep, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
    s3->Add(new wxStaticText(this, wxID_ANY, _T("MHz (0 for auto)")), 1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
    s3->Add(new wxStaticText(this, wxID_ANY, _T("CPU")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    s3->Add(editCoreFrequency, 0, wxLEFT, 5);
    sizer->Add(s3, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    sizer->Add(checkBoxUltra, 0, wxALL, 10);
    sizer->Add(checkBoxReverse, 0, wxALL & ~wxTOP, 10);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(buttonSaveBotSettings, 0, wxLEFT, 100);
    buttonSizer->Add(buttonBotRun, 0, wxLEFT, 10);
    sizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxLEFT | wxRIGHT, 10);

    sizer->Add(statusBarBot, 0, wxEXPAND | wxALL, 10);

    SetSizerAndFit(sizer);
    CenterOnParent();
}

// ---------------------------------------------------------------------------
// Settings
// ---------------------------------------------------------------------------

void ValidationBotDialog::LoadBotSettings() {
    int sleep = settings->Sleep;
    if (sleep < BOT_MIN_SLEEP || sleep > BOT_MAX_SLEEP) {
        sleep = BOT_DEFAULT_SLEEP;
    }

    int step = settings->Step;
    if (step < 0 || step > BOT_MAX_STEP) {
        step = 0;
    }

    // ChangeValue doesn't emit wxEVT_TEXT, so the Save button stays disabled
    editCpuzPath->ChangeValue(settings->CpuzPath);
    editBotSleep->ChangeValue(wxString::Format("%d", sleep));
    editFsbStep->ChangeValue(wxString::Format("%d", step));
    checkBoxUltra->SetValue(settings->Ultra);
    checkBoxReverse->SetValue(settings->Reverse);

    buttonSaveBotSettings->Enable(false);
}

void ValidationBotDialog::SaveBotSettings() {
    settings->CpuzPath = editCpuzPath->GetValue();
    settings->Sleep = GetIntValue(editBotSleep, BOT_DEFAULT_SLEEP, BOT_MIN_SLEEP, BOT_MAX_SLEEP);
    settings->Step = GetIntValue(editFsbStep, 0, 0, BOT_MAX_STEP);
    settings->Ultra = checkBoxUltra->GetValue();
    settings->Reverse = checkBoxReverse->GetValue();
    settings->Save();

    // Reflect the sanitized values back in the UI
    LoadBotSettings();
    SetStatus("Bot settings saved.");
}

int ValidationBotDialog::GetIntValue(wxTextCtrl* ctrl, int defaultValue, int minValue, int maxValue) {
    long value;

    if (!ctrl->GetValue().ToLong(&value)) {
        return defaultValue;
    }

    if (value < minValue) {
        return minValue;
    }

    if (value > maxValue) {
        return maxValue;
    }

    return static_cast<int>(value);
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

void ValidationBotDialog::SetStatus(const wxString& text) {
    statusBarBot->SetStatusText(text);
}

void ValidationBotDialog::UpdateFrequencyDisplay(bool measure) {
    if (measure) {
        cpuReference->RefreshCpuSpeed();
    }

    const cpu_info_t& cpuInfo = cpuReference->GetCpuInfo();
    double fsb = targetFsb > 0 ? targetFsb : cpuInfo.fsb;

    panelCurrentFsb->SetValue(wxString::Format("%.2f MHz", fsb));

    if (measure) {
        editCoreFrequency->SetValue(wxString::Format("%.2f MHz", cpuInfo.frequency));
    } else {
        editCoreFrequency->SetValue("N/A");
    }
}

HWND ValidationBotDialog::FindCpuzWindow() {
    DWORD currentProcessId = GetCurrentProcessId();

    for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT)) {
        if (!IsWindowVisible(hwnd)) {
            continue;
        }

        // Skip our own windows
        DWORD processId = 0;
        GetWindowThreadProcessId(hwnd, &processId);
        if (processId == currentProcessId) {
            continue;
        }

        int length = GetWindowTextLengthA(hwnd);
        if (length < 5) {
            continue;
        }

        char title[256] = { 0 };
        GetWindowTextA(hwnd, title, sizeof(title));

        if (strncmp(title, "CPU-Z", 5) == 0) {
            return hwnd;
        }
    }

    return NULL;
}

bool ValidationBotDialog::LaunchCpuz() {
    wxString path = editCpuzPath->GetValue();
    path.Trim(true).Trim(false);

    if (path.IsEmpty()) {
        SetStatus("CPU-Z path not selected and no CPU-Z running.");
        return false;
    }

    wxString directory = wxFileName(path).GetPath();
    wxCharBuffer fileBuffer = path.mb_str();
    wxCharBuffer dirBuffer = directory.mb_str();

    SHELLEXECUTEINFOA shExecInfo;
    ZeroMemory(&shExecInfo, sizeof(shExecInfo));
    shExecInfo.cbSize = sizeof(shExecInfo);
    shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shExecInfo.hwnd = (HWND)GetHWND();
    shExecInfo.lpVerb = "open";
    shExecInfo.lpFile = fileBuffer.data();
    shExecInfo.lpParameters = NULL;
    shExecInfo.lpDirectory = directory.IsEmpty() ? NULL : dirBuffer.data();
    shExecInfo.nShow = SW_SHOW;
    shExecInfo.hInstApp = NULL;

    if (!ShellExecuteExA(&shExecInfo)) {
        SetStatus("CPU-Z not found, please check path to cpuz.exe");
        return false;
    }

    // We don't need to wait for the process, the main window is polled by the timer
    if (shExecInfo.hProcess != NULL) {
        CloseHandle(shExecInfo.hProcess);
    }

    return true;
}

// ---------------------------------------------------------------------------
// Bot control
// ---------------------------------------------------------------------------

void ValidationBotDialog::StartBot() {
    // Start from the current FSB
    cpuReference->RefreshCpuSpeed();
    targetFsb = cpuReference->GetCpuInfo().fsb;
    targetPll = 0;
    UpdateFrequencyDisplay(true);

    editCpuzPath->Enable(false);
    buttonBrowseCpuz->Enable(false);
    editBotSleep->Enable(false);
    buttonBotRun->SetLabel("Stop");

    hWndCpuz = FindCpuzWindow();

    if (hWndCpuz == NULL) {
        if (!LaunchCpuz()) {
            StopBot(wxEmptyString);
            return;
        }

        // Wait (without blocking the UI) for CPU-Z to finish detection and show its main window
        state = BOT_LAUNCHING;
        launchAttempts = 0;
        timerBot.Start(BOT_LAUNCH_POLL_MS);
        SetStatus("Launching CPU-Z...");
        return;
    }

    state = BOT_RUNNING;
    timerBot.Start(GetIntValue(editBotSleep, BOT_DEFAULT_SLEEP, BOT_MIN_SLEEP, BOT_MAX_SLEEP) * 1000);
    SetStatus("Running");
}

void ValidationBotDialog::StopBot(const wxString& reason) {
    if (timerBot.IsRunning()) {
        timerBot.Stop();
    }

    state = BOT_IDLE;

    editCpuzPath->Enable(true);
    buttonBrowseCpuz->Enable(true);
    editBotSleep->Enable(true);
    buttonBotRun->SetLabel("Run");
    buttonBotRun->Enable(true);

    if (!reason.IsEmpty()) {
        SetStatus(reason);
    }
}

void ValidationBotDialog::BotStep() {
    // Activate CPU-Z window
    if (hWndCpuz == NULL || !IsWindow(hWndCpuz)) {
        StopBot("CPU-Z window lost. Bot stopped.");
        return;
    }

    if (IsIconic(hWndCpuz)) {
        ShowWindow(hWndCpuz, SW_RESTORE);
    }

    if (!SetForegroundWindow(hWndCpuz)) {
        StopBot("CPU-Z window lost. Bot stopped.");
        return;
    }

    // Press and release F7 (save validation)
    INPUT ip[2];
    ZeroMemory(ip, sizeof(ip));

    ip[0].type = INPUT_KEYBOARD;
    ip[0].ki.wVk = VK_F7;
    ip[0].ki.dwFlags = 0;

    ip[1].type = INPUT_KEYBOARD;
    ip[1].ki.wVk = VK_F7;
    ip[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, ip, sizeof(INPUT));

    // Calculate next FSB
    int step = GetIntValue(editFsbStep, 0, 0, BOT_MAX_STEP);
    bool reverse = checkBoxReverse->GetValue();
    pair<double, int> next;

    if (reverse) {
        next = Nforce2Pll::GetPrevPll(targetFsb - step);
    } else {
        next = Nforce2Pll::GetNextPll(targetFsb + step);
    }

    if (next.first <= 0 || next.second == 0) {
        StopBot(reverse ? "Minimum FSB reached. Bot stopped." : "Maximum FSB reached. Bot stopped.");
        return;
    }

    targetFsb = next.first;
    targetPll = next.second;

    if (Nforce2Pll::nforce2_set_fsb_pll(targetFsb, targetPll) != 0) {
        StopBot("Error setting FSB. Bot stopped.");
        return;
    }

    // In Ultra mode skip the CPU frequency measurement
    UpdateFrequencyDisplay(!checkBoxUltra->GetValue());
}

// ---------------------------------------------------------------------------
// Events
// ---------------------------------------------------------------------------

void ValidationBotDialog::OnBotRunClick(wxCommandEvent& event) {
    if (state != BOT_IDLE) {
        StopBot("Bot stopped.");
    } else {
        StartBot();
    }
}

void ValidationBotDialog::OnTimerBot(wxTimerEvent& event) {
    switch (state) {
    case BOT_LAUNCHING:
        hWndCpuz = FindCpuzWindow();

        if (hWndCpuz != NULL) {
            state = BOT_RUNNING;
            timerBot.Stop();
            timerBot.Start(GetIntValue(editBotSleep, BOT_DEFAULT_SLEEP, BOT_MIN_SLEEP, BOT_MAX_SLEEP) * 1000);
            SetStatus("Running");
        } else if (++launchAttempts >= BOT_LAUNCH_MAX_ATTEMPTS) {
            StopBot("CPU-Z window not found. Bot stopped.");
        }
        break;

    case BOT_RUNNING:
        BotStep();
        break;

    default:
        timerBot.Stop();
        break;
    }
}

void ValidationBotDialog::OnBrowseCpuzClick(wxCommandEvent& event) {
    wxString defaultDir, defaultFile;
    wxString current = editCpuzPath->GetValue();

    if (!current.IsEmpty()) {
        wxFileName fn(current);
        defaultDir = fn.GetPath();
        defaultFile = fn.GetFullName();
    }

    wxFileDialog openDialog(this, wxT("Select CPU-Z executable"), defaultDir, defaultFile,
                            wxT("Executable files (*.exe)|*.exe|All files (*.*)|*.*"),
                            wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openDialog.ShowModal() == wxID_OK) {
        editCpuzPath->SetValue(openDialog.GetPath());
    }
}

void ValidationBotDialog::OnSaveBotSettingsClick(wxCommandEvent& event) {
    SaveBotSettings();
}

void ValidationBotDialog::OnBotControlChange(wxCommandEvent& event) {
    buttonSaveBotSettings->Enable(true);
}

void ValidationBotDialog::OnClose(wxCloseEvent& event) {
    StopBot(wxEmptyString);
    event.Skip();
}
