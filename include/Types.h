#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>

using namespace std;

enum CodeName {
    Spitfire,
    Morgan,
    Applebred,
    Thunderbird,
    Palomino,
    Thoroughbred,
    Barton,
};

struct timing_def_t {
    string name;
    unsigned int bus;
    unsigned int device;
    unsigned int fn;
    unsigned int reg;
    unsigned int offset;
    unsigned int bits;
};

// MANID Register, MSR C001_001Eh
struct man_id_t {
    unsigned char reticleSite; // [9-8]
    unsigned char majorRev; // [7-4]
    unsigned char minorRev; // [3-0]
};

struct cpu_info_t {
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
};

struct control_def_t {
    string name;
    string label;
    bool editable;
    unsigned int min;
    unsigned int max;
    vector<string> customChoices;
    bool customItems;
};

#endif // TYPES_H
