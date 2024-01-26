#ifndef HEADER_A6FCFEEAB0C09B6
#define HEADER_A6FCFEEAB0C09B6

#pragma once

#include <wx/wx.h>
#include <wx/choice.h>

class TimingComboBoxData : public wxObject {
public:
    TimingComboBoxData(long value) : m_value(value) {}
    long GetValue() const { return m_value; }

private:
    long m_value;
};

class TTimingComboBox : public wxChoice {
public:
    TTimingComboBox(wxWindow* parent, wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0,
                    const wxValidator& validator = wxDefaultValidator,
                    const wxString& name = wxChoiceNameStr);

    // Destructor
    virtual ~TTimingComboBox();

    // Setters
    void SetMin(int value);
    void SetMax(int value);
    void SetValue(int value);
    void SetItemValue(int value);
    void SetChanged();

private:
    void Init();
    void OptionChange(wxCommandEvent& event);
    void DropDown(wxCommandEvent& event);
    void CloseUp(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);

    int tMin;
    int tMax;
    bool tCustomItems;
    bool tCustomValue;
    int tValue;
    int tIndex;
    bool tChanged;

    // DECLARE_EVENT_TABLE();
};
#endif // header guard

