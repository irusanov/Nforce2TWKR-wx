#ifndef PROFILESMANAGER_H
#define PROFILESMANAGER_H

#define VERSION_MAJOR 1
#define VERSION_MINOR 3

#include <wx/wx.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include "TAdvancedEdit.h"
#include "TTimingComboBox.h"

using namespace std;

struct profile_options_t {
    wxString name;
    wxString author;
    wxString comment;
    bool timings;
    bool dssr;
    bool advanced;
    bool romsip;
};

struct profile_metadata_t {
    int versionMajor;
    int versionMinor;
    wxString path;
    profile_options_t options;
};

class ProfilesManager {
private:
    wxString DefaultPath;

    void CreateDirIfNotPresent(const wxString& DirPath);

    void SaveTimings(wxFileConfig* ini, const wxString& section, const wxString* names, int size);

    void LoadTimings(wxFileConfig* ini, const wxString& section, const wxString* names, int size);

    void SaveRomsipValues(wxFileConfig* ini, const wxString& section, const wxString* names, int size);

    void LoadRomsipValues(wxFileConfig* ini, const wxString& section, const wxString* names, int size);

public:
    ProfilesManager();

    wxString GetDefaultPath();

    profile_metadata_t ReadMetadata(const wxString& FilePath);

    void WriteMetadata(wxFileConfig* ini, const profile_options_t& Opts);

    void Load(const wxString& FilePath, const profile_options_t& Opts);

    bool Save(const wxString& FilePath, const profile_options_t& Opts);

    void Init();

    // Preload profile data
    profile_metadata_t PreviewMetadata;
};
#endif // PROFILESMANAGER_H

