// TTimingComboBox.cpp

#include "TTimingComboBox.h"

TTimingComboBox::TTimingComboBox(wxWindow* parent,
                                 const wxString& name,
                                 const wxString& value,
                                 const wxPoint& pos,
                                 const wxSize& size,
                                 const int min,
                                 const int max)
    : wxOwnerDrawnComboBox(parent, wxID_ANY, value, pos, size, wxArrayString(), 0, wxDefaultValidator, name),
      tMin(min),
      tMax(max),
      tValue(0),
      tIndex(0),
      isChanged(false)
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
    if (isChanged)
    {
        SetBackgroundColour(*wxYELLOW);
    }
    Refresh();
    event.Skip();
}

void TTimingComboBox::OnComboBox(wxCommandEvent& event)
{
    isChanged = (tIndex != GetSelection());
    SetBackgroundColour(isChanged ? *wxYELLOW : originalBackground);
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
        isChanged = false;
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
            for (unsigned int i = 0; i < GetCount(); i++)
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
        isChanged = false;
        SetBackgroundColour(originalBackground);
        Refresh();
    }
}

void TTimingComboBox::SetChanged()
{
    isChanged = true;
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
