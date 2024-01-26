#ifndef PROFILEPRELOADWINDOW_H
#define PROFILEPRELOADWINDOW_H

#include <wx/wx.h>
#include "../../Nforce2TWKRMain.h"
#include "../../utils/ProfilesManager.h"

class ProfilePreloadWindow : public wxDialog {
public:
    ProfilePreloadWindow(wxWindow* parent, const wxString& title);
    ~ProfilePreloadWindow();

private:
    void SetApplyButtonState();
    void OnLoadButtonClick(wxCommandEvent& event);
    void OnFormShow(wxShowEvent& event);
    void OnSectionCheckBoxClick(wxCommandEvent& event);

    profile_metadata_t data;

    wxCheckBox* CheckBoxTimings;
    wxCheckBox* CheckBoxDSSR;
    wxCheckBox* CheckBoxAdvanced;
    wxCheckBox* CheckBoxRomsip;
    wxPanel* PanelName;
    wxPanel* PanelAuthor;
    wxPanel* PanelComment;
    wxButton* ButtonLoadProfile;

    DECLARE_EVENT_TABLE()
};

#endif // PROFILEPRELOADWINDOW_H

