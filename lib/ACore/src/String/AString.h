
//TODO: Figure out if the 'A' in this file's fileName can be dropped and yet not conflict with <string>
#ifndef STRING__AString_H
#define STRING__AString_H

#include "Data/DataTypes.h"
#include <sstream>

namespace String {

//TODO: Write a light-weight string class


std::string getString(const I4  & number){ //TODO: rewrite to not use sstream
	std::stringstream stream;
	stream<<number;
	return stream.str();
}
std::string getString(const I8  & number){ //TODO: rewrite to not use sstream
	std::stringstream stream;
	stream<<number;
	return stream.str();
}
std::string getString(const I8u & number){ //TODO: rewrite to not use sstream
	std::stringstream stream;
	stream<<number;
	return stream.str();
}

bool hasEnding(const std::string & fullString, const std::string & ending){
    if(fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

}

#endif
