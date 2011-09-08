
#ifndef STRING__AString_H
#define STRING__AString_H

#include <sstream>

//TODO: Write a light-weight string class

std::string getString(const int &number){ //TODO: rewrite to not use sstream
	std::stringstream stream;
	stream<<number;
	return stream.str();
}
std::string getString(const long long &number){ //TODO: rewrite to not use sstream
	std::stringstream stream;
	stream<<number;
	return stream.str();
}

#endif
