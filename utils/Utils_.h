#ifndef HEADER_6A8BE12ABAB94C4F
#define HEADER_6A8BE12ABAB94C4F

#pragma once
#include <string>
#include <windows.h>
#include <wx/string.h>
#include "ols/OlsApiInitExt.h"
#include "Constants.h"
#include "Types.h"
#include "../version.h"

using namespace std;

static unsigned int SetBits(unsigned int val, int offset, int n, unsigned int newValue) {
    return (val & ~(((1U << n) - 1) << offset)) | (newValue << offset);
}

static unsigned int GetBits(unsigned int val, int offset, int n) {
    return (val >> offset) & ~(~0U << n);
}

static unsigned int MakePciAddress(int bus, int device, int fn, int offset) {
    return 0x80000000 | bus << 16 | device << 11 | fn << 8 | offset;
}

unsigned int ReadPciReg(unsigned int pciDev) {
    WriteIoPortDwordEx(PCI_ADDR_PORT, pciDev);
    return ReadIoPortDword(PCI_DATA_PORT);
}

static string GetStringPart(BYTE val) {
    if(val != 0) {
        string s(1, val);
        return s;
    }
    return "";
}

static string IntToStr(DWORD val) {
    BYTE part1 = val & 0xff;
    BYTE part2 = val >> 8 & 0xff;
    BYTE part3 = val >> 16 & 0xff;
    BYTE part4 = val >> 24 & 0xff;

    return GetStringPart(part1) + GetStringPart(part2) + GetStringPart(part3) + GetStringPart(part4);
}

static string trim(string& str) {
    size_t first = str.find_first_not_of(' ');
    if(string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

static bool Contains(const string* arr, int arraySize, string value) {
    for(int i = 0; i < arraySize; i++) {
        if(arr[i] == value) {
            return true;
        }
    }
    return false;
}

bool WritePciReg(unsigned int pciDev, unsigned int value) {
    WriteIoPortDwordEx(PCI_ADDR_PORT, pciDev);
    return WriteIoPortDwordEx(PCI_DATA_PORT, value) == 1;
}

string GetCpuName() {
    string model = "";
    DWORD eax = 0, ebx = 0, ecx = 0, edx = 0;

    if(Cpuid(0x80000002, &eax, &ebx, &ecx, &edx))
        model = model + IntToStr(eax) + IntToStr(ebx) + IntToStr(ecx) + IntToStr(edx);

    if(Cpuid(0x80000003, &eax, &ebx, &ecx, &edx))
        model = model + IntToStr(eax) + IntToStr(ebx) + IntToStr(ecx) + IntToStr(edx);

    if(Cpuid(0x80000004, &eax, &ebx, &ecx, &edx))
        model = model + IntToStr(eax) + IntToStr(ebx) + IntToStr(ecx) + IntToStr(edx);

    trim(model);

    return model;
}

static wxString GetAppVersion() {
    return wxString::Format("%s %s", AutoVersion::FULLVERSION_STRING, AutoVersion::STATUS);
}

static wxString GetBuildDate() {
    return wxString::Format("%s.%s.%s", AutoVersion::DATE, AutoVersion::MONTH, AutoVersion::YEAR);
}

static timing_def_t GetDefByName(const struct timing_def_t* table, int size, string name) {
    for (int i = 0; i < size; i++) {
        if (table[i].name == name) {
            return table[i];
        }
    }

    return {
    };
}

#endif // header guard

