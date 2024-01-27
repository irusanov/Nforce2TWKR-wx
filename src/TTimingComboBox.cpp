// TTimingComboBox.cpp

#include "TTimingComboBox.h"

TTimingComboBox::TTimingComboBox(wxWindow* parent, wxWindowID id,
                                 const wxPoint& pos,
                                 const wxSize& size,
                                 const wxArrayString& choices,
                                 long style,
                                 const wxValidator& validator,
                                 const wxString& name)
    : wxOwnerDrawnComboBox(parent, id, wxEmptyString, pos, size, choices, style, validator, name),
      tMin(0),
      tMax(10),
      tValue(0),
      tIndex(0),
      tChanged(false)
{
    originalBackground = GetBackgroundColour();

    SetBackgroundColour(originalBackground);
    SetEditable(false);
    SetCursor(wxCursor(wxCURSOR_DEFAULT));

    CreateItems();

    Bind(wxEVT_COMBOBOX, &TTimingComboBox::OnComboBox, this);
    Bind(wxEVT_COMBOBOX_DROPDOWN, &TTimingComboBox::OnDropDown, this);
    Bind(wxEVT_COMBOBOX_CLOSEUP, &TTimingComboBox::OnCloseUp, this);
    Bind(wxEVT_PAINT, &TTimingComboBox::OnPaint, this);
}

void TTimingComboBox::CreateItems()
{
    for (int i = tMin; i <= tMax; i++)
    {
        Append(wxString::Format("%d", i));
    }
}

/*
void TTimingComboBox::OnDrawItem(wxDC& dc, const wxRect& rect, int item, int flags) const
{
    dc.SetBrush(wxBrush(GetBackgroundColour()));
    dc.SetPen(wxPen(GetBackgroundColour()));

    // Customize the drawing of items if needed
    wxOwnerDrawnComboBox::OnDrawItem(dc, rect, item, flags);
}
*/

void TTimingComboBox::OnDropDown(wxCommandEvent& event)
{
    SetBackgroundColour(originalBackground);
    Refresh();
    event.Skip();
}

void TTimingComboBox::OnCloseUp(wxCommandEvent& event)
{
    if (tChanged)
    {
        SetBackgroundColour(*wxYELLOW);
    }
    Refresh();
    event.Skip();
}

void TTimingComboBox::OnComboBox(wxCommandEvent& event)
{
    tChanged = (tIndex != GetSelection());
    SetBackgroundColour(tChanged ? *wxYELLOW : originalBackground);
    Refresh();
    event.Skip();
}

void TTimingComboBox::SetValue(int value)
{
    if (value >= tMin && value <= tMax)
    {
        SetSelection(value - tMin);
        tValue = value;
        tIndex = GetSelection();
        tChanged = false;
        SetBackgroundColour(originalBackground);
        Refresh();
    }
}

void TTimingComboBox::SetItemValue(int value)
{
    if (value >= tMin && value <= tMax)
    {
        int index = FindString(wxString::Format("%d", value));

        if (index == wxNOT_FOUND)
        {
            index = 0;
            for (int i = 0; i < GetCount(); i++)
            {
                if (value > wxAtoi(GetString(i)))
                {
                    index++;
                }
            }

            Insert(wxString::Format("%d", value), index);
        }

        SetSelection(index);
        tIndex = index;
        tValue = value;
        tChanged = false;
        SetBackgroundColour(originalBackground);
        Refresh();
    }
}

void TTimingComboBox::SetChanged()
{
    tChanged = true;
    SetBackgroundColour(*wxYELLOW);
    Refresh();
}

void TTimingComboBox::OnPaint(wxPaintEvent& event)
{
    event.Skip();
    SetSelection(0, 0);
    HideCaret(NULL);
    SetCursor(wxCursor(wxCURSOR_DEFAULT));
}
