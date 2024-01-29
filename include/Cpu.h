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
        const cpu_info_t& GetCpuInfo() const;
        void RefreshCpuSpeed();

    protected:
        cpu_info_t cpuInfo;
        Nforce2Pll pll;
        QueryPerformance qpc;
        double targetFsb;

    private:
        bool InitSystemInfo();
};

#endif // CPU_H
