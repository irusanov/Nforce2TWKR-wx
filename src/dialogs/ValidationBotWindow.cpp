// ValidationBotDialog.cpp

#include "dialogs/ValidationBotWindow.h"

wxBEGIN_EVENT_TABLE(ValidationBotDialog, wxDialog)
    EVT_BUTTON(wxID_SAVE, ValidationBotDialog::SaveBotSettingsClick)
wxEND_EVENT_TABLE()

ValidationBotDialog::ValidationBotDialog(wxWindow* parent, const wxString& title, AppSettings& appSettings)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition),
        hWndCpuz(NULL),
        settings(&appSettings) {

    wxFont font = this->GetFont();
    font.SetFaceName(_T("Tahoma"));
    font.SetPointSize(8);
    this->SetFont(font);

    InitControls();
    CreateLayout();
}

ValidationBotDialog::~ValidationBotDialog() {
    if (timerBot->IsRunning()) {
        timerBot->Stop();
    }
}

void ValidationBotDialog::InitControls() {
    timerBot = new wxTimer();

    editCpuzPath = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 18), 0);
    editBotSleep = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 18), 0);
    editFsbStep = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 18), 0);
    checkBoxUltra = new wxCheckBox(this, wxID_ANY, wxT("Ultra (no update)"), wxDefaultPosition, wxDefaultSize, 0);
    checkBoxReverse = new wxCheckBox(this, wxID_ANY, wxT("Reverse direction"), wxDefaultPosition, wxDefaultSize, 0);
    panelCurrentFsb = new TReadonlyTextBox(this, wxEmptyString, 80);
    editCoreFrequency = new TReadonlyTextBox(this, wxEmptyString, 80);
    buttonSaveBotSettings = new wxButton(this, wxID_SAVE, wxT("Save Settings"), wxDefaultPosition, wxDefaultSize, 0);
    buttonBotRun = new wxButton(this, wxID_ANY, wxT("Run"), wxDefaultPosition, wxDefaultSize, 0);
    statusBarBot = new wxStatusBar(this, wxID_ANY, 0);
    buttonBrowseCpuz = new wxButton(this, wxID_ANY, wxT("Browse..."), wxDefaultPosition, wxSize(80, 18), 0);
    //openFileDialogBot = new wxFileDialog(this, wxT("Select CPU-Z Path"), wxEmptyString, wxEmptyString,
    //                                     wxT("Executable files (*.exe)|*.exe"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
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

void ValidationBotDialog::SaveBotSettings() {
    settings->CpuzPath = editCpuzPath->GetValue();

    long sleepValue;
    editBotSleep->GetValue().ToLong(&sleepValue);
    settings->Sleep = static_cast<int>(sleepValue);

    long int fsbValue;
    editFsbStep->GetValue().ToLong(&fsbValue);
    settings->Step = static_cast<int>(fsbValue);
    settings->Ultra = checkBoxUltra->GetValue();

    settings->Save();
    buttonSaveBotSettings->Enable(false);
    statusBarBot->SetStatusText("Bot settings saved.");
}

void ValidationBotDialog::SaveBotSettingsClick(wxCommandEvent& event) {
    SaveBotSettings();
}

