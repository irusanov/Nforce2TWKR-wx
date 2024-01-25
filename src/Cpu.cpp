#include "Cpu.h"
#include "ols/OlsApiInitExt.h"
#include "Constants.h"
#include "../utils/CPUDetection.h"
#include "../utils/Utils.h"

Cpu::Cpu()
{
    InitSystemInfo();
}

Cpu::~Cpu()
{
    //dtor
}

bool __fastcall Cpu::InitSystemInfo() {
    unsigned long eax = 0, ebx = 0, ecx = 0, edx = 0;

    // CPUID information
    if(Cpuid(0x00000001, &eax, &ebx, &ecx, &edx)) {
        cpuInfo.cpuid = eax;
        cpuInfo.stepping = eax & 0xf;
        cpuInfo.family = eax >> 8 & 0xf;
        cpuInfo.model = eax >> 4 & 0xf;
    } else {
        return false;
    }

    // Extended CPUID information
    if(Cpuid(0x80000001, &eax, &ebx, &ecx, &edx)) {
        cpuInfo.extFamily = eax >> 8 & 0xf;
        cpuInfo.extModel = eax >> 4 & 0xf;
        cpuInfo.MP = edx >> FEATURE_K7_ECC_BIT & 1;
    } else {
        return false;
    }

    // L1 Data cache
    if(Cpuid(0x80000005, &eax, &ebx, &ecx, &edx)) {
        cpuInfo.l1DataCache = (ecx >> 24 & 0xff);
        cpuInfo.l1InstCache = (edx >> 24 & 0xff);
        cpuInfo.l1Cache = cpuInfo.l1DataCache + cpuInfo.l1InstCache;
    }

    // L2 cache
    if(Cpuid(0x80000006, &eax, &ebx, &ecx, &edx)) {
        cpuInfo.l2Cache = (ecx >> 16 & 0xffff);
    }

    if(Rdmsr(MSR_K7_MANID, &eax, &edx)) {
        cpuInfo.manID.minorRev = GetBits(eax, 0, 4);
        cpuInfo.manID.majorRev = GetBits(eax, 4, 4);
        cpuInfo.manID.reticleSite = GetBits(eax, 8, 2);
    }

    // Read CPU FID and VID values
    if(Rdmsr(MSR_K7_FID_VID_STATUS, &eax, &edx)) {
        cpuInfo.currVid = GetBits(edx, 0, 6);
        cpuInfo.startVid = GetBits(edx, 8, 6);
        cpuInfo.maxVid = GetBits(edx, 16, 6);

        cpuInfo.currFid = GetBits(eax, 0, 6);
        cpuInfo.startFid = GetBits(eax, 8, 6);
        cpuInfo.maxFid = GetBits(eax, 16, 6);
    }

    cpuInfo.cpuName = GetCpuName();
    decode_amd_model_string(cpuInfo.cpuName);
    // decode_amd_model_string("Athlon XP-M");

    // @TODO: Implement RefreshCpuSpeed
    //RefreshCpuSpeed();

    switch(cpuInfo.cpuid) {
    default:
        ;
    }

    return true;
}
