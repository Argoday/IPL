
#ifndef CRYPT__ModularTranspositionCipher_H
#define CRYPT__ModularTranspositionCipher_H

#include "CryptString.h"

namespace Crypt {

class CRYPT_DLL_EXPORT ModularTranspositionCipher {

	public:
		
		typedef std::pair<int,int> EncryptParameterType;
		typedef std::pair<int,int> DecryptParameterType;

		static CryptString encrypt(const CryptString &  plainText,const EncryptParameterType & parameter);
		static CryptString decrypt(const CryptString & cipherText,const DecryptParameterType & parameter);

	private:

		ModularTranspositionCipher(){};

};

}

#endif
