
#ifndef CRYPT__CaesarCipher_H
#define CRYPT__CaesarCipher_H

#include "Crypt.h"
#include "CryptChar.h"
#include "SimpleCipher.h"

namespace Crypt {

class CRYPT_DLL_EXPORT CaesarCipherMethod {

	public:

		typedef CaesarCipherMethod ThisType;

		typedef int EncryptParameterType;
		typedef int EncryptTempType;

		typedef int DecryptParameterType;
		typedef int DecryptTempType;

		static void encryptPrep(const EncryptParameterType & parameter,EncryptTempType & temp){}
		static void decryptPrep(const DecryptParameterType & parameter,DecryptTempType & temp){}
		
		static CryptChar encrypt(const CryptChar &  plainChar,const EncryptParameterType & parameter){
			return (plainChar+parameter);
		}
		static CryptChar decrypt(const CryptChar & cipherChar,const DecryptParameterType & parameter){
			return (cipherChar-parameter);
		}

	private:

};

typedef SimpleCipher<CaesarCipherMethod> CaesarCipher;

}

#endif
