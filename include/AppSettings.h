#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <wx/string.h>
#include <wx/fileconf.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

class AppSettings {
private:
    wxString ExeName;
    wxString FileName;
    wxString Path;

public:
    // General options
    bool MinimizeToTray;
    bool MinimizeHintShown;
    bool SaveWindowPosition;
    int WindowTop;
    int WindowLeft;

    // Auto-validation Bot options
    wxString CpuzPath;
    int Sleep;
    int Step;
    bool Ultra;

    AppSettings();

    // Load settings.ini
    void Load();

    // Save settings.ini
    void Save();

    void Reset();
};

#endif // APPSETTINGS_H
