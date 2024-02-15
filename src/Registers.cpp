#include "Registers.h"
#include "Constants.h"
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

        if (combo != nullptr && combo != 0 && sizeof(def) > 0) {

            pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg);
            regValue = Utils::ReadPciReg(pciAddress);
            value = Utils::GetBits(regValue, def.offset, def.bits);

            if (name == "CAS") {
                ((TTimingComboBox *)combo)->SetValue(GetIndexByCAS(value));
            } else {
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

        if (box != nullptr && box != 0 && sizeof(def) > 0) {
            pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg);
            regValue = Utils::ReadPciReg(pciAddress);
            value = Utils::GetBits(regValue, def.offset, def.bits);

            box->SetValue(Utils::ByteToHexString(value));
            // box->InitialValue = box->Text;
        }
    }
}

void Registers::WriteTimings(const struct timing_def_t* table, int size, bool doubled) {
    timing_def_t def;
    unsigned int pciAddress, regValue, value, bits;
    TTimingComboBox* combo;
    string name;

    for (int i = 0; i < size; i++) {
        name = table[i].name;
        combo = static_cast<TTimingComboBox *>(wxFrame::FindWindowByName(name));

        if (combo != nullptr && combo != 0 && ((TTimingComboBox *)combo)->IsChanged()) {
            // Skip if timing requires a custom write
            if (combo->IsCustomValue()) {
                continue;
            }

            def = Utils::GetDefByName(table, size, name);
            bits = def.bits;
            value = combo->GetSelection();

            if (doubled) {
                value = (value << 4) | value;
                bits *= 2;
            }

            pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg);
            regValue = Utils::ReadPciReg(pciAddress);
            regValue = Utils::SetBits(regValue, def.offset, bits, value);
            Utils::WritePciReg(pciAddress, regValue);
        }
    }
}

void Registers::WriteBurstMode(const struct timing_def_t* table, int size) {
    string name = "BurstMode";
    timing_def_t def;
    unsigned int pciAddress, regValue, value;
    TTimingComboBox* combo = static_cast<TTimingComboBox *>(wxFrame::FindWindowByName(name));

    if (combo != nullptr && combo != 0 && combo->IsChanged()) {
        def = Utils::GetDefByName(table, size, name);
        value = combo->GetSelection();

        // Write values for DIMM_0, DIMM_B1 and DIMM_A0
        for (int i = 0; i < 3; i++) {
            pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg + i * 8);
            regValue = Utils::ReadPciReg(pciAddress) & NF2_DRAM_CFG1_ACCESS_MASK;
            regValue = Utils::SetBits(regValue, def.offset, def.bits, value);
            Utils::WritePciReg(pciAddress, regValue);
        }
    }
}

void Registers::WriteDriveStrengthMode(const struct timing_def_t* table, int size) {
    string name = "DriveStrengthMode";
    timing_def_t def;
    unsigned int pciAddress, regValue, value;
    TTimingComboBox* combo = static_cast<TTimingComboBox *>(wxFrame::FindWindowByName(name));

    if (combo != nullptr && combo != 0 && combo->IsChanged()) {
        def = Utils::GetDefByName(table, size, name);
        value = combo->GetSelection();

        // Write values for DIMM_0, DIMM_B1 and DIMM_A0
        for (int i = 0; i < 3; i++) {
            pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg + i * 8);
            regValue = (Utils::ReadPciReg(pciAddress) & NF2_DRAM_CFG2_ACCESS_MASK) | LBIT(21);
            regValue = Utils::SetBits(regValue, def.offset, def.bits, value);
            Utils::WritePciReg(pciAddress, regValue);
        }
    }
}

void Registers::WriteBusDisconnect() {
    bool busDisconnect;
    timing_def_t def;
    unsigned int pciAddress = Utils::MakePciAddress(0, 0, 0, 0x6C);
    unsigned int regValue, value;
    TTimingComboBox* combo;

    combo = static_cast<TTimingComboBox *>(wxFrame::FindWindowByName("STPGNTDisconnect"));

    if (combo != nullptr && combo != 0 && combo->IsChanged()) {
        regValue = Utils::ReadPciReg(pciAddress);
        value = combo->GetSelection();

        regValue = Utils::SetBits(regValue, 28, 1, ~value & 0x1);
        regValue = Utils::SetBits(regValue, 31, 1, value);
        Utils::WritePciReg(pciAddress, regValue);
    }

    combo = static_cast<TTimingComboBox *>(wxFrame::FindWindowByName("HALTDisconnect"));

    if (combo != nullptr && combo != 0 && combo->IsChanged()) {
        regValue = Utils::ReadPciReg(pciAddress);
        value = combo->GetSelection();

        regValue = Utils::SetBits(regValue, 14, 2, (value << 1) | value);
        Utils::WritePciReg(pciAddress, regValue);
    }
}

void Registers::WriteRomsipValues(const struct timing_def_t* table, int size) {
    timing_def_t def;
    unsigned int pciAddress, regValue, value;
    TAdvancedEdit* box;
    string name;

    for (int i = 0; i < size; i++) {
        name = table[i].name;
        box = static_cast<TAdvancedEdit *>(wxFrame::FindWindowByName(name));

        if (box != nullptr && box != 0 && box->isChanged) {
            def = Utils::GetDefByName(table, size, name);
            pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg);
            regValue = Utils::ReadPciReg(pciAddress);

            unsigned long ulongValue;
            box->GetValue().ToULong(&ulongValue, 16);
            value = static_cast<unsigned int>(ulongValue);

            regValue = Utils::SetBits(regValue, def.offset, def.bits, value);
            Utils::WritePciReg(pciAddress, regValue);
        }
    }
}
