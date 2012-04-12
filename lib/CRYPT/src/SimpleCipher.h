
#ifndef CRYPT__SimpleCipher_H
#define CRYPT__SimpleCipher_H

#include "CryptString.h"

namespace Crypt {

template <
	typename Method
> class CRYPT_DLL_EXPORT SimpleCipher {

	public:

		typedef Method Method;

		static CryptString encrypt(const CryptString &  plainText,const typename Method::EncryptParameterType & parameter){
			CryptString cipherText;
			cipherText.resize(plainText.size());
			typename Method::EncryptTempType temp;
			Method::encryptPrep(parameter,temp);
			for(size_t i=0;i<plainText.size();++i){
				if(plainText[i].isChar()==true){
					cipherText[i] = Method::encrypt(plainText[i],parameter,temp);
				}else{
					cipherText[i] = plainText[i];
				}
			}
			return cipherText;
		}

		static CryptString decrypt(const CryptString & cipherText,const typename Method::DecryptParameterType & parameter){
			CryptString plainText;
			plainText.resize(cipherText.size());
			typename Method::DecryptTempType temp;
			Method::decryptPrep(parameter,temp);
			for(size_t i=0;i<cipherText.size();++i){
				if(cipherText[i].isChar()==true){
					plainText[i] = Method::decrypt(cipherText[i],parameter,temp);
				}else{
					plainText[i] = cipherText[i];
				}
			}
			return plainText;
		}

	private:

		SimpleCipher(){};

};

}


#endif
