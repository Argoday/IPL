
#include "CryptString.h"
#include "ModularTranspositionCipher.h"

namespace Crypt {

CryptString ModularTranspositionCipher::encrypt(const CryptString &  plainText,const EncryptParameterType & parameter){
	CryptString cipherText;
	cipherText.resize(plainText.size());
	for(size_t i=0;i<plainText.size();++i){
		if(plainText[i].isChar()==true){
			int temp = (i*parameter.first+parameter.first-1)%parameter.second;
			if(temp<0){temp+=parameter.second;}
			cipherText[i] = plainText[temp];
		}else{
			cipherText[i] = plainText[i];
		}
	}
	return cipherText;
}
CryptString ModularTranspositionCipher::decrypt(const CryptString & cipherText,const DecryptParameterType & parameter){
	CryptString plainText;
	plainText.resize(cipherText.size());
	for(size_t i=0;i<cipherText.size();++i){
		if(cipherText[i].isChar()==true){
			int temp = (i*parameter.first+parameter.first-1)%parameter.second;
			if(temp<0){temp+=parameter.second;}
			plainText[i] = cipherText[temp];
		}else{
			plainText[i] = cipherText[i];
		}
	}
	return plainText;
}

}
