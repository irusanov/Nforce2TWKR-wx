#ifndef HEADER_6A8BE12ABAB94C4F
#define HEADER_6A8BE12ABAB94C4F

#pragma once
#include <string>
#include <windows.h>

using namespace std;

unsigned int SetBits(unsigned int val, int offset, int n, unsigned int newValue);

unsigned int GetBits(unsigned int val, int offset, int n);

unsigned int MakePciAddress(int bus, int device, int fn, int offset);

string GetStringPart(BYTE val);

string IntToStr(DWORD val);

string trim(string& str);

bool __fastcall Contains(const string* arr, int arraySize, string value);

unsigned int ReadPciReg(unsigned int pciDev);

bool WritePciReg(unsigned int pciDev, unsigned int value);

string GetCpuName();

#endif // header guard

