#include "Utils.h"
#include "Constants.h"
#include "ols/OlsApiInitExt.h"

unsigned int Utils::SetBits(unsigned int val, int offset, int n, unsigned int newValue) {
    return (val & ~(((1U << n) - 1) << offset)) | (newValue << offset);
}

unsigned int Utils::GetBits(unsigned int val, int offset, int n) {
    return (val >> offset) & ~(~0U << n);
}

unsigned int Utils::MakePciAddress(int bus, int device, int fn, int offset) {
    return 0x80000000 | bus << 16 | device << 11 | fn << 8 | offset;
}

string Utils::GetStringPart(BYTE val) {
    if(val != 0) {
        string s(1, val);
        return s;
    }
    return "";
}

string Utils::IntToStr(DWORD val) {
    BYTE part1 = val & 0xff;
    BYTE part2 = val >> 8 & 0xff;
    BYTE part3 = val >> 16 & 0xff;
    BYTE part4 = val >> 24 & 0xff;

    return GetStringPart(part1) + GetStringPart(part2) + GetStringPart(part3) + GetStringPart(part4);
}

string Utils::trim(string& str) {
    size_t first = str.find_first_not_of(' ');
    if(string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool Utils::Contains(const string* arr, int arraySize, string value) {
    for(int i = 0; i < arraySize; i++) {
        if(arr[i] == value) {
            return true;
        }
    }
    return false;
}

wxString Utils::GetAppVersion() {
    return wxString::Format("%s %s", AutoVersion::FULLVERSION_STRING, AutoVersion::STATUS);
}

wxString Utils::GetBuildDate() {
    return wxString::Format("%s.%s.%s", AutoVersion::DATE, AutoVersion::MONTH, AutoVersion::YEAR);
}

wxString Utils::GetBuildCount() {
    return wxString::Format("%d", AutoVersion::BUILDS_COUNT);
}

struct timing_def_t Utils::GetDefByName(const struct timing_def_t* table, int size, string name) {
    for (int i = 0; i < size; i++) {
        if (table[i].name == name) {
            return table[i];
        }
    }

    return {
    };
}

bool Utils::WritePciReg(unsigned int pciDev, unsigned int value) {
    WriteIoPortDwordEx(PCI_ADDR_PORT, pciDev);
    return WriteIoPortDwordEx(PCI_DATA_PORT, value) == 1;
}

unsigned int Utils::ReadPciReg(unsigned int pciDev) {
    WriteIoPortDwordEx(PCI_ADDR_PORT, pciDev);
    return ReadIoPortDword(PCI_DATA_PORT);
}

wxArrayString Utils::ConvertToWxArrayString(const std::vector<std::string>& values) {
    wxArrayString wxArray;
    for (const auto& value : values) {
        wxArray.Add(wxString(value));
    }
    return wxArray;
}

wxString Utils::ByteToHexString(unsigned char byte) {
    wxString hexString;
    hexString.Printf("%02X", static_cast<unsigned int>(byte));
    return hexString;
}

wxString Utils::ByteToHexString(unsigned int byte) {
    return ByteToHexString(static_cast<unsigned char>(byte));
}

