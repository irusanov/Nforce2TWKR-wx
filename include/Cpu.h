#ifndef CPU_H
#define CPU_H

#include "Types.h"
#include "../utils/Nforce2Pll.h"
#include "../utils/QueryPerformance.h"

class Cpu
{
    public:
        Cpu();
        virtual ~Cpu();


    protected:
        cpu_info_t cpuInfo;
        Nforce2Pll pll;
        QueryPerformance qpc;
        double targetFsb;
        void __fastcall RefreshCpuSpeed();

    private:
        bool __fastcall InitSystemInfo();
};

#endif // CPU_H
