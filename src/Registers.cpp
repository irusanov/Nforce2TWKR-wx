#include "Registers.h"
#include "components/TTimingComboBox.h"
#include "components/TAdvancedEdit.h"

int Registers::GetIndexByCAS(unsigned int value) {
    // CAS is bits [5:4], bit 6 is Half Latency toggle
    // CAS 2.0 = 010 2
    // CAS 2.5 = 110 5
    // CAS 3.0 = 011 3
    // 001, 101 and 111 are reserved

    if (value == 2)
        return 0; // CAS 2.0
    if (value == 6)
        return 1; // CAS 2.5
    if (value == 3)
        return 2; // CAS 3.0

    return -1;
}

void Registers::ReadTimings(const struct timing_def_t* table, int size) {
    timing_def_t def;
    unsigned int pciAddress, regValue, value;
    TTimingComboBox* combo;
    string name;

    for (int i = 0; i < size; i++) {
        name = table[i].name;
        def = Utils::GetDefByName(table, size, name);
        combo = static_cast<TTimingComboBox *>(wxFrame::FindWindowByName(name));

        if (combo != NULL && combo != 0 && sizeof(def) > 0) {

            pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg);
            regValue = Utils::ReadPciReg(pciAddress);
            value = Utils::GetBits(regValue, def.offset, def.bits);

            if (name == "CAS") {
                ((TTimingComboBox *)combo)->SetValue(GetIndexByCAS(value));
            }
            else if (combo->isCustomValue) {
                ((TTimingComboBox *)combo)->SetItemValue(value);
            }
            else {
                ((TTimingComboBox *)combo)->SetValue(value);
            }
        }
    }
}

void Registers::ReadRomsipValues(const struct timing_def_t* table, int size) {
    timing_def_t def;
    unsigned int pciAddress, regValue, value;
    TAdvancedEdit* box;
    string name;

    for (int i = 0; i < size; i++) {
        name = table[i].name;
        def = Utils::GetDefByName(table, size, name);
        box = static_cast<TAdvancedEdit *>(wxFrame::FindWindowByName(name));

        if (box != NULL && box != 0 && sizeof(def) > 0) {
            pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg);
            regValue = Utils::ReadPciReg(pciAddress);
            value = Utils::GetBits(regValue, def.offset, def.bits);

            box->SetValue(Utils::ByteToHexString(value));
            // box->InitialValue = box->Text;
        }
    }
}
