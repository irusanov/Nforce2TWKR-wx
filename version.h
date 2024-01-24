#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{

	//Date Version Types
	static const char DATE[] = "25";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2024";
	static const char UBUNTU_VERSION_STYLE[] =  "24.01";

	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";

	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 2;
	static const long BUILD  = 6;
	static const long REVISION  = 37;

	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 30;
	#define RC_FILEVERSION 1,2,6,37
	#define RC_FILEVERSION_STRING "1, 2, 6, 37\0"
	static const char FULLVERSION_STRING [] = "1.2.6.37";

	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 4;

}
#endif //VERSION_H
