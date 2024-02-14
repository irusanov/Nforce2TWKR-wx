#ifndef PROFILE_SAVE_WINDOW_H
#define PROFILE_SAVE_WINDOW_H

#include <wx/wx.h>
#include "../../Nforce2TWKRMain.h"
#include "../../utils/ProfilesManager.h"

class ProfileSaveWindow : public wxDialog {
public:
    ProfileSaveWindow(wxWindow* parent, const wxString& title);
    ~ProfileSaveWindow();

private:
    void SetApplyButtonState();
    void OnLoadButtonClick(wxCommandEvent& event);
    void OnFormShow(wxShowEvent& event);
    void OnSectionCheckBoxClick(wxCommandEvent& event);

    profile_metadata_t data;

    wxCheckBox* checkBoxTimings;
    wxCheckBox* checkBoxDSSR;
    wxCheckBox* checkBoxAdvanced;
    wxCheckBox* checkBoxRomsip;
    wxTextCtrl* textName;
    wxTextCtrl* textAuthor;
    wxTextCtrl* textComment;
    wxButton* buttonCancel;
    wxButton* buttonSave;

    DECLARE_EVENT_TABLE()
};

#endif // PROFILE_SAVE_WINDOW_H

