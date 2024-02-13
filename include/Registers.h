#ifndef REGISTERS_H
#define REGISTERS_H

#include "wx/wx.h"
#include "../utils/Utils.h"

class Registers
{
public:
    static int GetIndexByCAS(unsigned int value);
    static void ReadTimings(const struct timing_def_t* table, int size);
    static void ReadRomsipValues(const struct timing_def_t* table, int size);
    static void WriteTimings(const struct timing_def_t* table, int size, bool doubled);
    static void WriteBurstMode(const struct timing_def_t* table, int size);
    static void WriteDriveStrengthMode(const struct timing_def_t* table, int size);
    static void WriteBusDisconnect();
    static void WriteRomsipValues(const struct timing_def_t* table, int size);
protected:

private:
};

#endif // REGISTERS_H
