#ifndef CHIPSET_H
#define CHIPSET_H

#include "Constants.h"
#include "Cpu.h"
#include "components/TTimingComboBox.h"
#include "components/TReadonlyTextBox.h"
#include "wx/wx.h"

#define CHIPSET_PANEL_ROW_SPACING 2

class ChipsetPanel: public wxPanel {
public:
    ChipsetPanel(wxWindow* parent, Cpu* cpu);
    void Update();
    double GetTargetFsb();
    int GetTargetPci();

private:
    Cpu* cpuReference;
    double targetFsb;

    void AddControls();
    void UpdatePllSlider(double fsb);
    void UpdatePciSlider(unsigned int mul);

    void OnPciSliderChange(wxScrollEvent& event);
    void OnButtonPciPrevClick(wxCommandEvent& event);
    void OnButtonPciNextClick(wxCommandEvent& event);

    void OnPllSliderChange(wxScrollEvent& event);
    void OnButtonPllPrevClick(wxCommandEvent& event);
    void OnButtonPllNextClick(wxCommandEvent& event);

    // controls
    TReadonlyTextBox* pciSliderValue;
    TReadonlyTextBox* pllSliderValue;
    wxSlider* pllSlider;
    wxSlider* pciSlider;
    wxButton* buttonPllPrev;
    wxButton* buttonPllNext;
    wxButton* buttonPciPrev;
    wxButton* buttonPciNext;
};

#endif // CHIPSET_H

