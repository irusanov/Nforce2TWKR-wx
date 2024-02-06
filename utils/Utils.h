#ifndef UTILS_H
#define UTILS_H

using namespace std;

#include <windows.h>
#include "wx/string.h"
#include "wx/arrstr.h"
#include "Types.h"
#include "../version.h"

class Utils {
public:
    static unsigned int SetBits(unsigned int val, int offset, int n, unsigned int newValue);
    static unsigned int GetBits(unsigned int val, int offset, int n);
    static unsigned int MakePciAddress(int bus, int device, int fn, int offset);
    static string GetStringPart(BYTE val);
    static string IntToStr(DWORD val);
    static string trim(string& str);
    static bool Contains(const string* arr, int arraySize, string value) ;
    static wxString GetAppVersion();
    static wxString GetBuildDate();
    static struct timing_def_t GetDefByName(const struct timing_def_t* table, int size, string name);
    static bool WritePciReg(unsigned int pciDev, unsigned int value);
    static unsigned int ReadPciReg(unsigned int pciDev);
    static wxArrayString ConvertToWxArrayString(const std::vector<std::string>& values);
protected:

private:
};

#endif // UTILS_H
