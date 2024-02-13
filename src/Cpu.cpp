#include <math.h>
#include "Cpu.h"
#include "ols/OlsApiInitExt.h"
#include "Constants.h"
#include "../utils/CPUDetection.h"
#include "../utils/Utils.h"

Cpu::Cpu() {
    if (!pll.init()) {
        throw "Not a nForce2 chipset!";
    }
    InitSystemInfo();
}

Cpu::~Cpu() {
    delete &pll;
    delete &qpc;
}

string Cpu::GetCpuName() {
    string model = "";
    DWORD eax = 0, ebx = 0, ecx = 0, edx = 0;

    if(Cpuid(0x80000002, &eax, &ebx, &ecx, &edx))
        model = model + Utils::IntToStr(eax) + Utils::IntToStr(ebx) + Utils::IntToStr(ecx) + Utils::IntToStr(edx);

    if(Cpuid(0x80000003, &eax, &ebx, &ecx, &edx))
        model = model + Utils::IntToStr(eax) + Utils::IntToStr(ebx) + Utils::IntToStr(ecx) + Utils::IntToStr(edx);

    if(Cpuid(0x80000004, &eax, &ebx, &ecx, &edx))
        model = model + Utils::IntToStr(eax) + Utils::IntToStr(ebx) + Utils::IntToStr(ecx) + Utils::IntToStr(edx);

    Utils::trim(model);

    return model;
}

unsigned int Cpu::GetFID() {
    timing_def_t def;
    unsigned int pciAddress;
    unsigned int regValue;
    unsigned int value;

    // Get actual FID from chipset
    def = Utils::GetDefByName(s2kTimings, COUNT_OF(s2kTimings), "FID");
    pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg);
    regValue = Utils::ReadPciReg(pciAddress);
    // if value is 0011 (0x3), ratio is >= 12.5x (FID 0x3)
    value = Utils::GetBits(regValue, def.offset, def.bits);

    return value;
}

void Cpu::RefreshPciFrequency() {
    timing_def_t def;
    unsigned int pciAddress, regValue, value;

    // Get current PCI bus frequency
    def = Utils::GetDefByName(chipsetTimingDefs, COUNT_OF(chipsetTimingDefs), "PCIFrequency");
    pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg);
    regValue = Utils::ReadPciReg(pciAddress);
    value = Utils::GetBits(regValue, def.offset, def.bits);

    cpuInfo.pciDiv = value & 0xff;
    cpuInfo.pciMul = value >> 8 & 0xff;

    // First write?
    if (cpuInfo.pciDiv != 0xf) {
        unsigned int newMul = (cpuInfo.pciMul * 0xf) / cpuInfo.pciDiv;
        cpuInfo.pciDiv = 0xf;
        cpuInfo.pciMul = newMul;

        WritePciFrequency(cpuInfo.pciMul << 8 | cpuInfo.pciDiv);
    }
}

void Cpu::WritePciFrequency(unsigned int value) {
    timing_def_t def;
    unsigned int pciAddress, regValue;

    def = Utils::GetDefByName(chipsetTimingDefs, COUNT_OF(chipsetTimingDefs), "PCIFrequency");
    pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg);
    regValue = Utils::ReadPciReg(pciAddress);

    regValue = Utils::SetBits(regValue, def.offset, def.bits, value);
    Utils::WritePciReg(pciAddress, regValue);
}

// Refresh frequency related parameters
void Cpu::RefreshCpuSpeed() {
    unsigned long eax = 0, edx = 0;
    timing_def_t def;
    unsigned int pciAddress, regValue, value;

    // Read current FSB
    cpuInfo.fsbFromPll = pll.nforce2_fsb_read(0);
    // Measure current CPU frequency
    cpuInfo.frequency = qpc.MeasureCPUFrequency();

    // Update current FID and VID
    if (Rdmsr(MSR_K7_FID_VID_STATUS, &eax, &edx)) {
        cpuInfo.currVid = Utils::GetBits(edx, 0, 6);
        cpuInfo.currFid = Utils::GetBits(eax, 0, 6);
    }

    cpuInfo.fid = GetFID();

    // FID from chipset is 4 bits and covers up to 12.5x
    // CurrFID from MSR_K7_FID_VID_STATUS is also unreliable
    // Calculate multiplier from CPU frequency and FSB (from PLL)
    if (cpuInfo.fsbFromPll > 0) {
        cpuInfo.multi = floor(((cpuInfo.frequency / cpuInfo.fsbFromPll) * 2) + 0.5) / 2;
    } else {
        cpuInfo.multi = fid_codes[cpuInfo.fid] / 10.0;
    }

    cpuInfo.fsb = cpuInfo.frequency / cpuInfo.multi;
    targetFsb = cpuInfo.fsb;

    // Get FSB:DRAM ratio
    def = Utils::GetDefByName(timingDefs, COUNT_OF(timingDefs), "FsbDramRatio");
    pciAddress = Utils::MakePciAddress(def.bus, def.device, def.fn, def.reg);
    regValue = Utils::ReadPciReg(pciAddress);
    value = Utils::GetBits(regValue, def.offset, def.bits);

    cpuInfo.fsbDiv = value & 0xf;
    cpuInfo.dramDiv = value >> 4 & 0xf;

    if (cpuInfo.fsbDiv > 0 && cpuInfo.dramDiv > 0) {
        cpuInfo.dram = cpuInfo.fsb * cpuInfo.dramDiv / cpuInfo.fsbDiv;
    }

    RefreshPciFrequency();
}

bool Cpu::InitSystemInfo() {
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
        cpuInfo.manID.minorRev = Utils::GetBits(eax, 0, 4);
        cpuInfo.manID.majorRev = Utils::GetBits(eax, 4, 4);
        cpuInfo.manID.reticleSite = Utils::GetBits(eax, 8, 2);
    }

    // Read CPU FID and VID values
    if(Rdmsr(MSR_K7_FID_VID_STATUS, &eax, &edx)) {
        cpuInfo.currVid = Utils::GetBits(edx, 0, 6);
        cpuInfo.startVid = Utils::GetBits(edx, 8, 6);
        cpuInfo.maxVid = Utils::GetBits(edx, 16, 6);

        cpuInfo.currFid = Utils::GetBits(eax, 0, 6);
        cpuInfo.startFid = Utils::GetBits(eax, 8, 6);
        cpuInfo.maxFid = Utils::GetBits(eax, 16, 6);
    }

    cpuInfo.cpuName = GetCpuName();
    decode_amd_model_string(cpuInfo.cpuName);
    // decode_amd_model_string("Athlon XP-M");

    RefreshCpuSpeed();

    switch(cpuInfo.cpuid) {
    default:
        ;
    }

    return true;
}

const cpu_info_t& Cpu::GetCpuInfo() const {
    return cpuInfo;
}

const Nforce2Pll& Cpu::GetPll() const {
    return pll;
}
