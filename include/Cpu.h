#ifndef CPU_H
#define CPU_H

#include "Types.h"
#include "../utils/Nforce2Pll.h"
#include "../utils/QueryPerformance.h"

class Cpu {
public:
    Cpu();
    virtual ~Cpu();
    const cpu_info_t& GetCpuInfo() const;
    const Nforce2Pll& GetPll() const;
    void RefreshPciFrequency();
    void RefreshCpuSpeed();
    static void WritePciFrequency(unsigned int value);

protected:
    cpu_info_t cpuInfo;
    Nforce2Pll pll;
    QueryPerformance qpc;
    double targetFsb;

private:
    bool InitSystemInfo();
    string GetCpuName();
    static unsigned int GetFID();
};

#endif // CPU_H
