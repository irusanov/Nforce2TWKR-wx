#ifndef CPU_DETECTION_H
#define CPU_DETECTION_H

// AMD K7 (family 6) core detection
//
// Core names and process are based on the libcpuid K7 match table,
// stepping -> revision mapping is based on x86info and the AMD revision guides.

#include <algorithm>
#include <string>
#include <cctype>
#include <wx/string.h>
#include "Constants.h"

using namespace std;

// Model string bits, decoded from the CPUID brand string
enum _cpu_bits_t {
    _M_          = BIT_ULL(0),
    _MP_         = BIT_ULL(1),
    _XP_         = BIT_ULL(2),
    _LV_         = BIT_ULL(3),
    _NX_         = BIT_ULL(4),
    _SFF_        = BIT_ULL(5),
    _4_          = BIT_ULL(6),
    MOBILE_      = BIT_ULL(7),
    ATHLON_      = BIT_ULL(8),
    DURON_       = BIT_ULL(9),
    SEMPRON_     = BIT_ULL(10),
    GEODE_       = BIT_ULL(11),
};

struct k7_core_t {
    string codeName;
    string revision;
    string technology;
};

static std::string to_lower(std::string s) {
    for(std::size_t i = 0; i < s.length(); ++i) {
        s[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(s[i])));
    }

    return s;
}

static unsigned int decode_amd_model_string(const string& name) {
    unsigned int i = 0;
    unsigned int bits = 0x0;
    string lowerName = to_lower(name);

    const struct {
        unsigned int bit;
        const char* search;
    } bit_matchtable[] = {
        { _M_,       " XP-M"   },
        { _MP_,      " MP"     },
        { _XP_,      " XP"     },
        { _LV_,      " (LV)"   },
        { _NX_,      " NX"     },
        { _SFF_,     " SFF"    },
        { _4_,       " 4"      },
        { MOBILE_,   "Mobile"  },
        { ATHLON_,   "Athlon"  },
        { DURON_,    "Duron"   },
        { SEMPRON_,  "Sempron" },
        { GEODE_,    "Geode"   },
    };

    for(i = 0; i < COUNT_OF(bit_matchtable); i++) {
        if(lowerName.find(to_lower(bit_matchtable[i].search)) != std::string::npos)
            bits |= bit_matchtable[i].bit;
    }

    return bits;
}

static bool is_mobile_k7(unsigned int bits) {
    return (bits & (MOBILE_ | _M_)) != 0;
}

// Identify K7 core and revision.
// l2Cache is in KB (already corrected for the T13 erratum).
static k7_core_t identify_k7_core(bool isAmd, unsigned int family, unsigned int model, unsigned int stepping,
                                  int l2Cache, unsigned int bits) {
    k7_core_t core;
    core.codeName = "Unknown";
    core.revision = "";
    core.technology = "";

    if(!isAmd || family != 6) {
        core.codeName = "Not a K7";
        return core;
    }

    switch(model) {
    case 1:
        // Athlon Slot A, 0.25um
        core.codeName = "Argon";
        core.technology = "250 nm";
        if(stepping == 1) core.revision = "C1";
        else if(stepping == 2) core.revision = "C2";
        break;

    case 2:
        // Athlon Slot A, 0.18um
        core.codeName = "Pluto/Orion";
        core.technology = "180 nm";
        if(stepping == 1) core.revision = "A1";
        else if(stepping == 2) core.revision = "A2";
        break;

    case 3:
        // Duron
        core.codeName = "Spitfire";
        core.technology = "180 nm";
        if(stepping == 0) core.revision = "A0";
        else if(stepping == 1) core.revision = "A2";
        break;

    case 4:
        // Athlon Socket A
        core.codeName = "Thunderbird";
        core.technology = "180 nm";
        if(stepping == 0) core.revision = "A1";
        else if(stepping == 1) core.revision = "A2";
        else if(stepping == 2) core.revision = "A4-A8";
        else if(stepping == 3) core.revision = "A9";
        break;

    case 6:
        // Athlon XP / MP / Mobile Athlon 4
        core.codeName = "Palomino";
        core.technology = "180 nm";
        if(stepping == 0) core.revision = "A0-A1";
        else if(stepping == 1) core.revision = "A2";
        else if(stepping == 2) core.revision = "A5";
        break;

    case 7:
        // Duron / Mobile Duron
        core.codeName = is_mobile_k7(bits) ? "Camaro" : "Morgan";
        core.technology = "180 nm";
        if(stepping == 0) core.revision = "A0";
        else if(stepping == 1) core.revision = "A1";
        break;

    case 8:
        // Athlon XP / MP / XP-M, Duron, Sempron, Geode NX
        core.technology = "130 nm";

        if((bits & DURON_) || (l2Cache > 0 && l2Cache <= 64)) {
            core.codeName = "Applebred";
        } else {
            core.codeName = stepping == 0 ? "Thoroughbred-A" : "Thoroughbred-B";
        }

        if(stepping == 0) core.revision = "A0";
        else if(stepping == 1) core.revision = "B0";
        break;

    case 10:
        // Athlon XP / MP / XP-M, Sempron
        core.technology = "130 nm";

        if(l2Cache > 0 && l2Cache < 512) {
            core.codeName = "Thorton";
        } else {
            core.codeName = "Barton";
        }

        if(stepping == 0) core.revision = "A2";
        break;

    default:
        core.codeName = "Unknown K7";
        break;
    }

    return core;
}

// AMD errata T13: early Duron and Thunderbird report a wrong L2 size
static int fix_k7_l2_cache(bool isAmd, unsigned int family, unsigned int model, unsigned int stepping, int l2Cache) {
    if(isAmd && family == 6) {
        // Duron rev A0
        if(model == 3 && stepping == 0)
            return 64;

        // Thunderbird rev A1/A2
        if(model == 4 && (stepping == 0 || stepping == 1))
            return 256;
    }

    return l2Cache;
}

#endif // header guard
