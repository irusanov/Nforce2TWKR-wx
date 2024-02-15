#ifndef PROFILE_WINDOW_BASE_H
#define PROFILE_WINDOW_BASE_H

#include <wx/wx.h>
#include "../../utils/ProfilesManager.h"

class ProfileWindowBase : public wxDialog {
public:
    ProfileWindowBase(wxWindow* parent, const wxString& title, const wxString& okButtonText = _T("Ok"), const bool editable = true);
    ~ProfileWindowBase();

    virtual void OnAction();

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

private:
    void SetButtonsState();
    // void OnLoadButtonClick(wxCommandEvent& event);
    // void OnFormShow(wxShowEvent& event);
    void OnSectionCheckBoxClick(wxCommandEvent& event);
    void OnActionButtonClick(wxCommandEvent& event);
};

#endif // PROFILE_WINDOW_BASE_H
