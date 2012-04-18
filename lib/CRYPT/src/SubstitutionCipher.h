
#ifndef CRYPT__SubstitutionCipher_H
#define CRYPT__SubstitutionCipher_H

#include "Crypt.h"
#include "SimpleCipher.h"
#include "MixedAlphabet.h"

namespace Crypt {

class CRYPT_DLL_EXPORT SubstitutionCipherMethod {

	public:

		typedef SubstitutionCipherMethod ThisType;
		
		typedef CryptString EncryptParameterType;
		typedef MixedAlphabet EncryptTempType;

		typedef CryptString DecryptParameterType;
		typedef MixedAlphabet DecryptTempType;

		static void encryptPrep(const EncryptParameterType & parameter,EncryptTempType & temp){
			temp.generate(parameter);		
		}
		static void decryptPrep(const DecryptParameterType & parameter,DecryptTempType & temp){
			temp.generate(parameter);
		}

		static CryptChar encrypt(const CryptChar &  plainChar,const EncryptParameterType & parameter,EncryptTempType & temp){
			if(plainChar.isChar()==true){
				return temp.charAt(plainChar.getValue());
			}
			return plainChar;
		}
		static CryptChar decrypt(const CryptChar & cipherChar,const DecryptParameterType & parameter,DecryptTempType & temp){
			if(cipherChar.isChar()==true){
				return CryptChar(static_cast<CryptChar::NumberType>(temp.positionOf(cipherChar)));
			}
			return cipherChar;
		}

	private:

};

typedef SimpleCipher<SubstitutionCipherMethod> SubstitutionCipher;

}

#endif
