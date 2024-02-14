#include "dialogs/SettingsWindow.h"

wxBEGIN_EVENT_TABLE(SettingsWindow, wxDialog)
    EVT_BUTTON(wxID_APPLY, SettingsWindow::OnApplySettings)
    EVT_BUTTON(wxID_RESET, SettingsWindow::OnResetSettings)
    EVT_BUTTON(wxID_CLOSE, SettingsWindow::OnClose)
    EVT_CHECKBOX(wxID_ANY, SettingsWindow::OnMinimizeToTrayClick)
    EVT_CHECKBOX(wxID_ANY, SettingsWindow::OnSaveWindowPositionClick)
wxEND_EVENT_TABLE()

SettingsWindow::SettingsWindow(wxWindow* parent, const wxString& title, AppSettings& appSettings)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition),
      settings(&appSettings) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Checkboxes
    checkBoxMinimizeToTray = new wxCheckBox(this, wxID_ANY, "Minimize to Tray");
    checkBoxSaveWindowPosition = new wxCheckBox(this, wxID_ANY, "Save Window Position");

    mainSizer->Add(checkBoxMinimizeToTray, 0, wxALL, 10);
    mainSizer->Add(checkBoxSaveWindowPosition, 0, wxALL & ~wxTOP, 10);

    // Buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonResetSettings = new wxButton(this, wxID_RESET, "Reset");
    buttonClose = new wxButton(this, wxID_CLOSE, "Close");
    buttonApplySettings = new wxButton(this, wxID_APPLY, "Apply");

    buttonSizer->Add(buttonResetSettings, 0);
    buttonSizer->Add(buttonClose, 0, wxLEFT, 50);
    buttonSizer->Add(buttonApplySettings, 0, wxLEFT, 5);

    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    SetSizerAndFit(mainSizer);
    CenterOnParent();

    LoadOptions();
}

void SettingsWindow::LoadOptions() {
    checkBoxMinimizeToTray->SetValue(settings->MinimizeToTray);
    checkBoxSaveWindowPosition->SetValue(settings->SaveWindowPosition);
    buttonApplySettings->Enable(false);
}

void SettingsWindow::OnApplySettings(wxCommandEvent& event) {
    settings->MinimizeToTray = checkBoxMinimizeToTray->GetValue();
    settings->SaveWindowPosition = checkBoxSaveWindowPosition->GetValue();
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
    buttonApplySettings->Enable(true);
}

void SettingsWindow::OnSaveWindowPositionClick(wxCommandEvent& event) {
    buttonApplySettings->Enable(true);
}
