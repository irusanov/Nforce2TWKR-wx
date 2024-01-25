#ifndef CPU_H
#define CPU_H

#include "Types.h"

class Cpu
{
    public:
        Cpu();
        virtual ~Cpu();

    protected:
        cpu_info_t cpuInfo;

    private:
        bool __fastcall InitSystemInfo();
};

#endif // CPU_H
