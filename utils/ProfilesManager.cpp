#include "ProfilesManager.h"
#include "Constants.h"

const wxString timings[14] = {
    "TRCDR", "TRCDW", "TRP", "TRAS", "TRC", "TRFC", "TDOE", "TRRD", "TWTP", "TWTR", "TREXT", "TRTP", "TRTW", "TREF"
};

const wxString advanced[5] = {"AutoPrecharge", "SuperBypass", "DataScavengedRate", "DriveStrengthMode", "BurstMode"};

const wxString dssr[9] = {
    "DIMM0DrvStrA", "DIMM0DrvStrB", "DIMM0SlewRate", "DIMM1DrvStrA", "DIMM1DrvStrB", "DIMM1SlewRate", "DIMM2DrvStrA",
    "DIMM2DrvStrB", "DIMM2SlewRate"
};

const wxString romsip[15] = {
    "Romsip48", "Romsip4C", "Romsip4D", "Romsip50", "Romsip65", "Romsip66", "Romsip67", "Romsip68", "Romsip69",
    "Romsip6A", "Romsip6B", "Romsip6C", "Romsip6D", "Romsip6F", "Romsip74"
};

ProfilesManager::ProfilesManager() {
    defaultPath = wxPathOnly(wxStandardPaths::Get().GetExecutablePath()) + wxFILE_SEP_PATH + "profiles" + wxFILE_SEP_PATH;
}

wxString ProfilesManager::GetDefaultPath() {
    return defaultPath;
}

void ProfilesManager::CreateDirIfNotPresent(const wxString& DirPath) {
    if (!wxDirExists(DirPath)) {
        wxMkdir(DirPath);
    }
}

void ProfilesManager::SaveTimings(wxFileConfig* ini, const wxString& section, const wxString* names, int size) {
    int value;
    TTimingComboBox* combo;

    for (int i = 0; i < size; i++) {
        combo = dynamic_cast<TTimingComboBox*>(wxWindow::FindWindowByName(names[i]));

        if (combo != wxNullPtr) {
            //value = static_cast<int>(combo->GetValue());
            ini->Write(section + wxCONFIG_PATH_SEPARATOR + names[i], combo->GetValue());
        }
    }
}

void ProfilesManager::LoadTimings(wxFileConfig* ini, const wxString& section, const wxString* names, int size) {
    int value, currentValue;
    TTimingComboBox* combo;

    for (int i = 0; i < size; i++) {
        if (ini->Read(section + wxCONFIG_PATH_SEPARATOR + names[i], &value)) {
            combo = dynamic_cast<TTimingComboBox*>(wxWindow::FindWindowByName(names[i]));

            if (combo != wxNullPtr) {
                //if (combo->CustomValue)
                //    currentValue = combo->ItemValue;
                //else
                    currentValue = wxAtoi(combo->GetValue());

                if (currentValue != value) {
                    //if (combo->CustomValue)
                    //    combo->ItemValue = value;
                    //else
                        combo->SetValue(value);

                    combo->SetChanged();
                }
            }
        }
    }
}

void ProfilesManager::SaveRomsipValues(wxFileConfig* ini, const wxString& section, const wxString* names, int size) {
    TAdvancedEdit* box;

    for (int i = 0; i < size; i++) {
        box = dynamic_cast<TAdvancedEdit*>(wxWindow::FindWindowByName(names[i]));

        if (box != wxNullPtr) {
            ini->Write(section + wxCONFIG_PATH_SEPARATOR + names[i].AfterFirst('R'), box->GetValue());
        }
    }
}

void ProfilesManager::LoadRomsipValues(wxFileConfig* ini, const wxString& section, const wxString* names, int size) {
    wxString value;
    TAdvancedEdit* box;

    for (int i = 0; i < size; i++) {
        if (ini->Read(section + wxCONFIG_PATH_SEPARATOR + names[i].AfterFirst('R'), &value)) {
            box = dynamic_cast<TAdvancedEdit*>(wxWindow::FindWindowByName(names[i]));

            if (box != wxNullPtr) {
                box->SetValue(value);
            }
        }
    }
}

profile_metadata_t ProfilesManager::ReadMetadata(const wxString& FilePath) {
    wxFileConfig iniFile(FilePath);

    previewMetadata.path = FilePath;

    iniFile.Read("PMVersion/Major", &previewMetadata.versionMajor, 0);
    iniFile.Read("PMVersion/Minor", &previewMetadata.versionMinor, 0);
    iniFile.Read("Metadata/Name", &previewMetadata.options.name);
    iniFile.Read("Metadata/Author", &previewMetadata.options.author);
    iniFile.Read("Metadata/Comment", &previewMetadata.options.comment);

    previewMetadata.options.timings = iniFile.HasGroup("Timings");
    previewMetadata.options.dssr = iniFile.HasGroup("DSSR");
    previewMetadata.options.advanced = iniFile.HasGroup("Advanced");
    previewMetadata.options.romsip = iniFile.HasGroup("ROMSIP");

    return previewMetadata;
}

void ProfilesManager::WriteMetadata(wxFileConfig* ini, const profile_options_t& Opts) {
    ini->Write("PMVersion/Major", static_cast<long>(VERSION_MAJOR));
    ini->Write("PMVersion/Minor", static_cast<long>(VERSION_MINOR));
    ini->Write("Metadata/Name", Opts.name);
    ini->Write("Metadata/Author", Opts.author);
    ini->Write("Metadata/Comment", Opts.comment);
}

void ProfilesManager::Load(const wxString& FilePath, const profile_options_t& Opts) {
    wxFileConfig iniFile(FilePath);

    if (Opts.timings) {
        LoadTimings(&iniFile, "Timings", timings, COUNT_OF(timings));
    }

    if (Opts.dssr) {
        LoadTimings(&iniFile, "DSSR", dssr, COUNT_OF(dssr));
    }

    if (Opts.advanced) {
        LoadTimings(&iniFile, "Advanced", advanced, COUNT_OF(advanced));
    }

    if (Opts.romsip) {
        LoadRomsipValues(&iniFile, "ROMSIP", romsip, COUNT_OF(romsip));
    }
}

bool ProfilesManager::Save(const wxString& FilePath, const profile_options_t& Opts) {
    wxFileConfig iniFile(wxEmptyString, wxEmptyString, FilePath, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);

    if (wxFileExists(FilePath)) {
        wxString msg = "Profile already exists. Do you want to overwrite it?";

        if (wxMessageBox(msg, "Confirmation", wxYES_NO | wxICON_QUESTION) != wxYES) {
            return false;
        }

        // Save existing name, author, and comment
        if (Opts.name.IsEmpty()) {
            iniFile.Read("Metadata/Name", Opts.name);
        }

        if (Opts.author.IsEmpty()) {
            iniFile.Read("Metadata/Author", Opts.author);
        }

        if (Opts.comment.IsEmpty()) {
            iniFile.Read("Metadata/Comment", Opts.comment);
        }

        iniFile.DeleteGroup("Timings");
        iniFile.DeleteGroup("DSSR");
        iniFile.DeleteGroup("Advanced");
        iniFile.DeleteGroup("ROMSIP");
    }

    WriteMetadata(&iniFile, Opts);

    if (Opts.timings) {
        SaveTimings(&iniFile, "Timings", timings, WXSIZEOF(timings));
    }

    if (Opts.dssr) {
        SaveTimings(&iniFile, "DSSR", dssr, WXSIZEOF(dssr));
    }

    if (Opts.advanced) {
        SaveTimings(&iniFile, "Advanced", advanced, WXSIZEOF(advanced));
    }

    if (Opts.romsip) {
        SaveRomsipValues(&iniFile, "ROMSIP", romsip, WXSIZEOF(romsip));
    }

    return true;
}

void ProfilesManager::Init() {
    CreateDirIfNotPresent(defaultPath);
}
