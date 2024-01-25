#ifndef TYPES_H
#define TYPES_H

#include <string>

// MANID Register, MSR C001_001Eh
typedef struct {
    unsigned char reticleSite; // [9-8]
    unsigned char majorRev; // [7-4]
    unsigned char minorRev; // [3-0]
} man_id_t;

typedef struct {
    unsigned int cpuid;
    string codeName;
    string cpuName;
    unsigned char family;
    unsigned char model;
    unsigned char extFamily;
    unsigned char extModel;
    unsigned char stepping;
    unsigned char patchLevel;
    double frequency;
    double fsbFromPll;
    double fsb;
    double multi;
    double dram;
    unsigned int pciMul;
    unsigned int pciDiv;
    unsigned char fsbDiv;
    unsigned char dramDiv;
    unsigned int maxVid;
    unsigned int startVid;
    unsigned int currVid;
    unsigned int maxFid;
    unsigned int startFid;
    unsigned int currFid;
    unsigned int fid;
    bool MP;
    int l1DataCache;
    int l1InstCache;
    int l1Cache;
    int l2Cache;
    man_id_t manID;
} cpu_info_t;

#endif // TYPES_H
