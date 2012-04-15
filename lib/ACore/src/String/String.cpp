
#include "AString.h"
#include <sstream>

namespace String {

ACORE_DLL_EXPORT std::string getString(const I4  & number){ //TODO: rewrite to not use sstream
	std::stringstream stream;
	stream<<number;
	return stream.str();
}
ACORE_DLL_EXPORT std::string getString(const I8  & number){ //TODO: rewrite to not use sstream
	std::stringstream stream;
	stream<<number;
	return stream.str();
}
ACORE_DLL_EXPORT std::string getString(const I8u & number){ //TODO: rewrite to not use sstream
	std::stringstream stream;
	stream<<number;
	return stream.str();
}

ACORE_DLL_EXPORT bool hasEnding(const std::string & fullString, const std::string & ending){
    if(fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

}

