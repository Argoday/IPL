
#include "CryptString.h"
#include <vector>

namespace Crypt {

class CryptString_d {
	public:
		std::vector<CryptChar> value;
};


CryptString::CryptString(){
	_this = new CryptString_d;
	_this->value.resize(0);
}
CryptString::CryptString(const ThisType & other){
	_this = new CryptString_d;
	_this->value = other._this->value;
}

CryptString::CryptString(const char * const & _value){
	_this = new CryptString_d;
	std::string tempString = _value;
	_this->value.resize(tempString.length());
	for(size_t i=0;i<tempString.length();++i){
		_this->value[i] = tempString[i];
	}
}

CryptString::CryptString(const std::string & _value){
	_this = new CryptString_d;
	_this->value.resize(_value.length());
	for(size_t i=0;i<_value.length();++i){
		_this->value[i] = _value[i];
	}
}

CryptString::~CryptString(){
	delete _this;
}

CryptString::operator std::string() const {
	std::string temp;
	temp.resize(_this->value.size());
	for(unsigned int i=0;i<_this->value.size();++i){
		temp[i] = _this->value[i];
	}
	return temp;
}

const size_t CryptString::size() const {return _this->value.size();}
void CryptString::resize(const size_t &sz){_this->value.resize(sz);}

CryptChar & CryptString::at(const size_t & i) {return _this->value[i];}
const CryptChar & CryptString::at(const size_t & i) const {return _this->value[i];}

CryptChar & CryptString::operator [](const size_t & i){return _this->value[i];}
const CryptChar & CryptString::operator [](const size_t & i) const {return _this->value[i];}


}