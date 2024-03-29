#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion {

//Date Version Types
static const char DATE[] = "15";
static const char MONTH[] = "02";
static const char YEAR[] = "2024";
static const char UBUNTU_VERSION_STYLE[] =  "24.02";

//Software Status
static const char STATUS[] =  "Alpha";
static const char STATUS_SHORT[] =  "a";

//Standard Version Type
static const long MAJOR  = 1;
static const long MINOR  = 2;
static const long BUILD  = 0;
static const long REVISION  = 73;

//Miscellaneous Version Types
static const long BUILDS_COUNT  = 1361;
#define RC_FILEVERSION 1,2,2,73
#define RC_FILEVERSION_STRING "1, 2, 0, 73\0"
static const char FULLVERSION_STRING [] = "1.2.0.73";

//These values are to keep track of your versioning state, don't modify them.
static const long BUILD_HISTORY  = 11;

}
#endif //VERSION_H
