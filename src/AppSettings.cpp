#include "AppSettings.h"

AppSettings::AppSettings() {
    ExeName = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetFullName();
    FileName = wxFileName(ExeName).GetFullName() + ".ini";
    Path = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPathWithSep() + FileName;
}

void AppSettings::Load() {
    wxFileConfig Settings(wxEmptyString, wxEmptyString, Path, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);

    MinimizeToTray = Settings.ReadBool("Options/MinimizeToTray", false);
    MinimizeHintShown = Settings.ReadBool("Options/MinimizeHintShown", false);
    SaveWindowPosition = Settings.ReadBool("Options/SaveWindowPosition", false);

    Settings.Read("Options/WindowTop", &WindowTop, 0);
    Settings.Read("Options/WindowLeft", &WindowLeft, 0);

    Settings.Read("Bot/CpuzPath", &CpuzPath, "");
    Settings.Read("Bot/Sleep", &Sleep, 6);
    Settings.Read("Bot/Step", &Step, 0);
    Ultra = Settings.ReadBool("Bot/Ultra", false);

    // Sanitize values (older versions could save garbage)
    if (Sleep < 1 || Sleep > 3600) {
        Sleep = 6;
    }

    if (Step < 0 || Step > 100) {
        Step = 0;
    }
}

void AppSettings::Save() {
    wxFileConfig Settings(wxEmptyString, wxEmptyString, Path, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);

    Settings.Write("Options/MinimizeToTray", MinimizeToTray);
    Settings.Write("Options/MinimizeHintShown", MinimizeHintShown);
    Settings.Write("Options/SaveWindowPosition", SaveWindowPosition);

    Settings.Write("Options/WindowTop", SaveWindowPosition ? WindowTop : 0);
    Settings.Write("Options/WindowLeft", SaveWindowPosition ? WindowLeft : 0);

    Settings.Write("Bot/CpuzPath", CpuzPath);
    Settings.Write("Bot/Sleep", Sleep);
    Settings.Write("Bot/Step", Step);
    Settings.Write("Bot/Ultra", Ultra);
}

void AppSettings::Reset() {
    wxRemoveFile(Path);
    Load();
}
