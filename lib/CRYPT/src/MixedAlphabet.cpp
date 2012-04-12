
#include "MixedAlphabet.h"
#include <vector>

namespace Crypt {

class MixedAlphabet::MixedAlphabet_d {
	public:
		std::vector<CryptChar> value;
};

MixedAlphabet::MixedAlphabet(){
	_this = new MixedAlphabet_d;
}
MixedAlphabet::MixedAlphabet(const CryptString & key){
	_this = new MixedAlphabet_d;
	generate(key);
}
MixedAlphabet::~MixedAlphabet(){
	delete _this;
}

void MixedAlphabet::generate(const CryptString & key){
	_this->value.clear();
	_this->value.resize(CryptChar::alphabetSize);
	
	size_t index=0;
	for(;index<=key.size()-1;++index){
		_this->value[index] = key[index];
	}

	for(;index<=_this->value.size()-1;++index){
		int num = 0;
		for(;;){
			bool found = false;
			for(size_t j=0;j<=index;++j){
				if(_this->value[j].getValue() == num){
					found = true;++num;
				}
			}
			if(found==false){break;}
		}
		_this->value[index] = num;
	}
}

void MixedAlphabet::rotate(const int & shift){
	MixedAlphabet_d * temp_this = new MixedAlphabet_d;
	temp_this->value = _this->value;
	for(size_t index=0;index<=_this->value.size()-1;++index){
		int shiftedIndex=(index+shift)%CryptChar::alphabetSize;
		if(shiftedIndex<0){shiftedIndex+=CryptChar::alphabetSize;}
		temp_this->value[index] = _this->value[shiftedIndex];
	}
	delete _this;_this = temp_this;
}

size_t MixedAlphabet::positionOf(const CryptChar & letter) const {
	for(size_t index=0;index<=_this->value.size()-1;++index){
		if(_this->value[index]==letter){
			return index;
		}
	}
	return 0;
}
const CryptChar & MixedAlphabet::charAt(const size_t & index) const {
	return _this->value[index];
}

}