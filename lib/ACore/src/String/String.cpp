
#include "AString.h"
#include <sstream>
#include <iomanip>

namespace String {

//TODO: Rewrite these functions to not use sstream - it is slow
ACORE_DLL_EXPORT std::string getString(const I4  & number){
	std::stringstream stream;
	stream<<number;
	return stream.str();
}
ACORE_DLL_EXPORT std::string getString(const I8  & number){
	std::stringstream stream;
	stream<<number;
	return stream.str();
}
ACORE_DLL_EXPORT std::string getString(const I8u & number){
	std::stringstream stream;
	stream<<number;
	return stream.str();
}
ACORE_DLL_EXPORT std::string getString(const I4  & number,const I4 & zeros){
	std::stringstream stream;
	stream<<std::setw(zeros)<<std::setfill('0')<<number;
	return stream.str();
}
ACORE_DLL_EXPORT std::string getString(const I8  & number,const I4 & zeros){
	std::stringstream stream;
	stream<<std::setw(zeros)<<std::setfill('0')<<number;
	return stream.str();
}
ACORE_DLL_EXPORT std::string getString(const I8u & number,const I4 & zeros){
	std::stringstream stream;
	stream<<std::setw(zeros)<<std::setfill('0')<<number;
	return stream.str();
}

ACORE_DLL_EXPORT std::string getString(const F4 & number){
	std::stringstream stream;
	stream<< std::setprecision( 8)<<number;//TODO: Check that this is enough precision
	return stream.str();
}
ACORE_DLL_EXPORT std::string getString(const F8 & number){
	std::stringstream stream;
	stream<< std::setprecision(15)<<number;//TODO: Check that this is enough precision
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

