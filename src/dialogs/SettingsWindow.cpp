#include "dialogs/SettingsWindow.h"

wxBEGIN_EVENT_TABLE(SettingsWindow, wxDialog)
    EVT_BUTTON(wxID_APPLY, SettingsWindow::OnApplySettings)
    EVT_BUTTON(wxID_RESET, SettingsWindow::OnResetSettings)
    EVT_BUTTON(wxID_CLOSE, SettingsWindow::OnClose)
    EVT_CHECKBOX(wxID_ANY, SettingsWindow::OnMinimizeToTrayClick)
    EVT_CHECKBOX(wxID_ANY, SettingsWindow::OnSaveWindowPositionClick)
wxEND_EVENT_TABLE()

SettingsWindow::SettingsWindow(wxWindow* parent, const wxString& title, AppSettings& appSettings)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    settings = &appSettings;

    // Checkboxes
    CheckBoxMinimizeToTray = new wxCheckBox(this, wxID_ANY, "Minimize to Tray");
    CheckBoxSaveWindowPosition = new wxCheckBox(this, wxID_ANY, "Save Window Position");

    mainSizer->Add(CheckBoxMinimizeToTray, 0, wxALL, 10);
    mainSizer->Add(CheckBoxSaveWindowPosition, 0, wxALL & ~wxTOP, 10);

    // Buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    ButtonResetSettings = new wxButton(this, wxID_RESET, "Reset");
    ButtonClose = new wxButton(this, wxID_CLOSE, "Close");
    ButtonApplySettings = new wxButton(this, wxID_APPLY, "Apply");

    buttonSizer->Add(ButtonResetSettings, 0, wxLEFT | wxRIGHT, 10);
    buttonSizer->Add(ButtonClose, 0, wxLEFT, 40);
    buttonSizer->Add(ButtonApplySettings, 0, wxLEFT | wxRIGHT, 10);

    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxBOTTOM | wxTOP, 5);

    SetSizerAndFit(mainSizer);

    LoadOptions();
}

void SettingsWindow::LoadOptions() {
    CheckBoxMinimizeToTray->SetValue(settings->MinimizeToTray);
    CheckBoxSaveWindowPosition->SetValue(settings->SaveWindowPosition);
    ButtonApplySettings->Enable(false);
}

void SettingsWindow::OnApplySettings(wxCommandEvent& event) {
    settings->MinimizeToTray = CheckBoxMinimizeToTray->GetValue();
    settings->SaveWindowPosition = CheckBoxSaveWindowPosition->GetValue();
    settings->Save();
    LoadOptions();
}

void SettingsWindow::OnResetSettings(wxCommandEvent& event) {
    wxString msg = "Do you want to reset application settings?";

    if (wxMessageBox(msg, "Confirmation", wxOK | wxCANCEL | wxICON_QUESTION) == wxOK) {
        settings->Reset();
        LoadOptions();
    }
}

void SettingsWindow::OnClose(wxCommandEvent& event) {
    Close();
}

void SettingsWindow::OnMinimizeToTrayClick(wxCommandEvent& event) {
    ButtonApplySettings->Enable(true);
}

void SettingsWindow::OnSaveWindowPositionClick(wxCommandEvent& event) {
    ButtonApplySettings->Enable(true);
}
