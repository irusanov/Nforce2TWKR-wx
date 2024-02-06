#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Types.h"

// linux/include/asm-generic/bitsperlong.h
#if defined(_WIN64)
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif

// linux/include/linux/bits.h
#define ULL(nr)                       (long long) nr
#define UL(nr)                        (long) nr
#define LBIT(x)                       (UL(1) << x)
#define BIT_ULL(nr)                   (ULL(1) << (nr))
#define BIT_MASK(nr)                  (UL(1) << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)                  ((nr) / BITS_PER_LONG)
#define BIT_ULL_MASK(nr)              (ULL(1) << ((nr) % BITS_PER_LONG_LONG))
#define BIT_ULL_WORD(nr)              ((nr) / BITS_PER_LONG_LONG)
#define BITS_PER_BYTE                 8

#define GENMASK(h, l) \
    (((~UL(0)) - (UL(1) << (l)) + 1) & \
    (~UL(0) >> (BITS_PER_LONG - 1 - (h))))

#define GENMASK_ULL(h, l) \
    (((~ULL(0)) - (ULL(1) << (l)) + 1) & \
    (~ULL(0) >> (BITS_PER_LONG_LONG - 1 - (h))))

/* K7 MSRs */
#define MSR_K7_EVNTSEL0               0xc0010000
#define MSR_K7_PERFCTR0               0xc0010004
#define MSR_K7_EVNTSEL1               0xc0010001
#define MSR_K7_PERFCTR1               0xc0010005
#define MSR_K7_EVNTSEL2               0xc0010002
#define MSR_K7_PERFCTR2               0xc0010006
#define MSR_K7_EVNTSEL3               0xc0010003
#define MSR_K7_PERFCTR3               0xc0010007
#define MSR_K7_CLK_CTL                0xc001001b
#define MSR_K7_MANID                  0xc001001e
#define MSR_K7_HWCR                   0xc0010015
#define MSR_K7_HWCR_SMMLOCK_BIT       0
#define MSR_K7_HWCR_SMMLOCK           BIT_ULL(MSR_K7_HWCR_SMMLOCK_BIT)
#define MSR_K7_HWCR_IRPERF_EN_BIT     30
#define MSR_K7_HWCR_IRPERF_EN         BIT_ULL(MSR_K7_HWCR_IRPERF_EN_BIT)
#define MSR_K7_FID_VID_CTL            0xc0010041
#define MSR_K7_FID_VID_STATUS         0xc0010042
#define FEATURE_K7_ECC_BIT            19

/* CPUID function 0x80000001, ebx */
#define CPUID_PKGTYPE_MASK            GENMASK(31, 28)

#define PCI_ADDR_PORT                 0xCF8
#define PCI_DATA_PORT                 0xCFC
#define COUNT_OF(array) (sizeof(array) / sizeof(array[0]))

/* NForce2 */
// Set bits 21, 20 and [12:9] to 0
#define NF2_DRAM_CFG1_ACCESS_MASK     0xffcfe1ff
// Set bits 20 and [12:3] to 0, additionally bit 21 needs to be set to 1
#define NF2_DRAM_CFG2_ACCESS_MASK     0xffefe007

// https://github.com/torvalds/linux/blob/master/drivers/cpufreq/powernow-k7.c#L78
// 0x0 - 0x1f. 0 - 31
const int fid_codes[32] = {
    110, 115, 120, 125, 50, 55, 60, 65,
    70, 75, 80, 85, 90, 95, 100, 105,
    30, 190, 40, 200, 130, 135, 140, 210,
    150, 225, 160, 165, 170, 180, 230, 240,
};

const timing_def_t timingDefs[] = {
    // name,                    b,  d,  f, reg, offset, bits
    { "CAS",                    0,  0,  1, 0xB0,  4,  3 },

    { "TRC",                    0,  0,  1, 0x90,  0,  5 },
    { "TRFC",                   0,  0,  1, 0x90,  8,  5 },
    { "TRAS",                   0,  0,  1, 0x90, 15,  4 },
    { "TRCDR",                  0,  0,  1, 0x90, 20,  4 },
    { "TRCDW",                  0,  0,  1, 0x90, 24,  4 },
    { "TRP",                    0,  0,  1, 0x90, 28,  4 },

    { "TDOE",                   0,  0,  1, 0x94, 28,  3 },
    { "TRRD",                   0,  0,  1, 0x94, 24,  3 },
    { "TWTP",                   0,  0,  1, 0x94, 20,  3 },
    { "TWTR",                   0,  0,  1, 0x94, 16,  3 },
    { "TREXT",                  0,  0,  1, 0x94, 12,  2 },
    { "TRTP",                   0,  0,  1, 0x94,  8,  3 },
    { "TRTW",                   0,  0,  1, 0x94,  4,  3 },

    { "CR",                     0,  0,  1, 0x84, 29,  1 },
    { "TREF",                   0,  0,  1, 0x60,  0, 16 },

    { "AutoPrecharge",          0,  0,  1, 0x84, 17,  1 },
    { "BurstMode",              0,  0,  1, 0xA0,  3,  1 },
    //{ "DLLEnable",            0,  0,  1, 0xA4,  0,  1 },
    { "DriveStrengthMode",      0,  0,  1, 0xA4,  1,  1 },
    { "SuperBypass",            0,  0,  1, 0xFC,  0,  1 },
    { "DataScavengedRate",      0,  0,  1, 0xF8,  2,  1 },

    { "FsbDramRatio",           0,  0,  3, 0x7C,  0,  8 },
};

const timing_def_t doubledTimingDefs[] = {
    { "DIMM0DrvStrA",           0,  0,  4, 0x64,  8,  4 },
    { "DIMM1DrvStrA",           0,  0,  4, 0x64, 24,  4 },
    { "DIMM2DrvStrA",           0,  0,  4, 0x7C,  8,  4 },
    { "DIMM0DrvStrB",           0,  0,  4, 0x70,  8,  4 },
    { "DIMM1DrvStrB",           0,  0,  4, 0x70, 24,  4 },
    { "DIMM2DrvStrB",           0,  0,  4, 0x80,  8,  4 },

    { "DIMM0SlewRate",          0,  0,  4, 0x64,  0,  4 },
    { "DIMM1SlewRate",          0,  0,  4, 0x64, 16,  4 },
    { "DIMM2SlewRate",          0,  0,  4, 0x7C,  0,  4 },
};

const timing_def_t chipsetTimingDefs[] = {
    // name,                    b,  d,  f, reg, offset, bits
    { "CPUDisconnect",          0,  0,  0, 0x6C, 28,  1 },
    { "HALTDisconnect",         0,  0,  0, 0x6C, 14,  1 },
    { "STPGNTDisconnect",       0,  0,  0, 0x6C, 31,  1 },
    { "AGPFastWrite",           0,  0,  0, 0x44,  4,  1 },
    { "AGPSBA",                 0,  0,  0, 0x48,  9,  1 },
    { "AGPControllerLatency",   0, 30,  0, 0x0C,  8,  8 },
    { "AGPBusLatency",          0, 30,  0, 0x18, 24,  8 },
    { "PCILatencyTimer",        0,  8,  0, 0x18, 24,  8 },
    { "PCIFrequency",           0,  0,  3, 0x78,  0, 16 },
    //{ "DIMM_B0_CFG",          0,  0,  2, 0x40,  0,  1 },
    //{ "DIMM_B1_CFG",          0,  0,  2, 0x44,  0,  1 },
    //{ "DIMM_A0_CFG",          0,  0,  2, 0x48,  0,  1 },

    // Thermal Throttling Ratio
    { "TTHRatio",               0,  1,  0, 0x95,  1,  3 },
    // Normal Throttling Ratio
    { "NTHRatio",               0,  1,  0, 0x95,  1,  3 },
};

const timing_def_t s2kTimings[] = {
    // S2K Control 1 Register
    { "SYSDCIN_Delay",          0,  0,  0, 0xE4,  0,  4 },
    { "SYSDCOUT_Delay",         0,  0,  0, 0xE4,  4,  2 },
    { "RDTOWR_Delay",           0,  0,  0, 0xE4,  7,  2 },
    { "WRTORD_Delay",           0,  0,  0, 0xE4, 10,  1 },
    { "WRDATA_Delay",           0,  0,  0, 0xE4, 12,  3 },
    { "XCAARB_PRCOUNT",         0,  0,  0, 0xE4, 16,  3 },
    { "XCAARB_RDCOUNT",         0,  0,  0, 0xE4, 19,  3 },
    { "XCAARB_WRCOUNT",         0,  0,  0, 0xE4, 22,  3 },
    { "FID",                    0,  0,  0, 0xF0, 28,  4 },
};

const timing_def_t romsipDefs[] = {
    // name,                    b,  d,  f, reg, offset, bits
    { "Romsip48",               0,  0,  3, 0x48,  0,  8 },
    { "Romsip4C",               0,  0,  3, 0x4C,  0,  8 },
    { "Romsip4D",               0,  0,  3, 0x4C,  8,  8 },
    { "Romsip50",               0,  0,  3, 0x50,  0,  8 },
    { "Romsip65",               0,  0,  3, 0x64,  8,  8 },
    { "Romsip66",               0,  0,  3, 0x64, 16,  8 },
    { "Romsip67",               0,  0,  3, 0x64, 24,  8 },
    { "Romsip68",               0,  0,  3, 0x68,  0,  8 },
    { "Romsip69",               0,  0,  3, 0x68,  8,  8 },
    { "Romsip6A",               0,  0,  3, 0x68, 16,  8 },
    { "Romsip6B",               0,  0,  3, 0x68, 24,  8 },
    { "Romsip6C",               0,  0,  3, 0x6C,  0,  8 },
    { "Romsip6D",               0,  0,  3, 0x6C,  8,  8 },
    //{ "Romsip6E",             0,  0,  3, 0x6C, 16,  8 },
    { "Romsip6F",               0,  0,  3, 0x6C, 24,  8 },
    { "Romsip74",               0,  0,  3, 0x74,  0,  8 },
};

const vector<string> trefChoices = {
    "16",
    "32",
    "64",
    "128",
    "388",
    "516",
    "648",
    "776",
    "780",
    "908",
    "1032",
    "1168",
    "1296",
    "1536",
    "1552",
    "1560",
    "1816",
    "2048",
    "2064",
    "2336",
    "2560",
    "2592",
    "3072",
    "3120",
    "3632",
    "3684",
    "4128",
    "4196",
    "4672",
    "4708",
};

const vector<string> tcasChoices = {
    "2.0",
    "2.5",
    "3.0",
};
const vector<string> tcrChoices = {
    "1T",
    "2T",
};

#endif // CONSTANTS_H
