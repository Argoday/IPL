
//TODO: Figure out if the 'A' in this file's fileName can be dropped and yet not conflict with <string>
#ifndef STRING__AString_H
#define STRING__AString_H

#include "ACore.h"
#include "Data/DataTypes.h"
#include <string>

namespace String {

//TODO: Write a light-weight string class

ACORE_DLL_EXPORT std::string getString(const I4  & number);
ACORE_DLL_EXPORT std::string getString(const I8  & number);
ACORE_DLL_EXPORT std::string getString(const I8u & number);

ACORE_DLL_EXPORT std::string getString(const F4  & number);
ACORE_DLL_EXPORT std::string getString(const F8  & number);

ACORE_DLL_EXPORT bool hasEnding(const std::string & fullString, const std::string & ending);

}

#endif
