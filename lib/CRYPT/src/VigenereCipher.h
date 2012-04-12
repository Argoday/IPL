
#ifndef CRYPT__VigenereCipher_H
#define CRYPT__VigenereCipher_H

#include "Crypt.h"
#include "SimpleCipher.h"

namespace Crypt {

class CRYPT_DLL_EXPORT VigenereCipherMethod {

	public:

		typedef VigenereCipherMethod ThisType;
		
		typedef CryptString EncryptParameterType;
		typedef size_t EncryptTempType;

		typedef CryptString DecryptParameterType;
		typedef size_t DecryptTempType;

		static void encryptPrep(const EncryptParameterType & parameter,EncryptTempType & temp){temp=0;}
		static void decryptPrep(const DecryptParameterType & parameter,DecryptTempType & temp){temp=0;}

		static CryptChar encrypt(const CryptChar &  plainChar,const EncryptParameterType & parameter,EncryptTempType & temp){
			CryptChar returnVal = (plainChar+parameter[temp]);
			++temp;if(temp>=parameter.size()){temp=0;}
			return returnVal;
		}
		static CryptChar decrypt(const CryptChar & cipherChar,const DecryptParameterType & parameter,DecryptTempType & temp){
			CryptChar returnVal = (cipherChar-parameter[temp]);
			++temp;if(temp>=parameter.size()){temp=0;}
			return returnVal;
		}

	private:

};

typedef SimpleCipher<VigenereCipherMethod> VigenereCipher;

}

#endif
