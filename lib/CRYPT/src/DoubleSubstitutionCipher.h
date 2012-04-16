
#ifndef CRYPT__DoubleSubstitutionCipher_H
#define CRYPT__DoubleSubstitutionCipher_H

#include "Crypt.h"
#include "SimpleCipher.h"
#include "MixedAlphabet.h"
#include <vector>

namespace Crypt {

class DoubleSubstitutionCipher_TempType {
	public:
		size_t index;
		MixedAlphabet linekey;
		std::vector<MixedAlphabet> key;
};

class CRYPT_DLL_EXPORT DoubleSubstitutionCipherMethod {

	public:

		typedef DoubleSubstitutionCipherMethod ThisType;
		
		typedef std::pair<CryptString,CryptString> EncryptParameterType;
		typedef DoubleSubstitutionCipher_TempType EncryptTempType;

		typedef std::pair<CryptString,CryptString> DecryptParameterType;
		typedef DoubleSubstitutionCipher_TempType DecryptTempType;

		static void encryptPrep(const EncryptParameterType & parameter,EncryptTempType & temp){
			temp.index = 0;
			temp.linekey.generate(parameter.first);
			temp.key.resize(parameter.second.size());
			for(size_t index=0;index<=temp.key.size()-1;++index){
				temp.key[index].generate(parameter.first);
				temp.key[index].rotate(temp.key[index].positionOf(parameter.second[index]));
			}
		}
		static void decryptPrep(const DecryptParameterType & parameter,DecryptTempType & temp){
			temp.index = 0;
			temp.linekey.generate(parameter.first);
			temp.key.resize(parameter.second.size());
			for(size_t index=0;index<=temp.key.size()-1;++index){
				temp.key[index].generate(parameter.first);
				temp.key[index].rotate(temp.key[index].positionOf(parameter.second[index]));
			}
		}

		static CryptChar encrypt(const CryptChar &  plainChar,const EncryptParameterType & parameter,EncryptTempType & temp){
			if(plainChar.isChar()==true){
				CryptChar cipherChar = temp.key[temp.index].charAt(temp.linekey.positionOf(plainChar));
				++(temp.index);if(temp.index>=temp.key.size()){temp.index=0;}
				return cipherChar;
			}
			return plainChar;
		}
		static CryptChar decrypt(const CryptChar & cipherChar,const DecryptParameterType & parameter,DecryptTempType & temp){
			if(cipherChar.isChar()==true){
				CryptChar plainChar = temp.linekey.charAt(temp.key[temp.index].positionOf(cipherChar));
				++(temp.index);if(temp.index>=temp.key.size()){temp.index=0;}
				return plainChar;
			}
			return cipherChar;
		}

	private:

};

typedef SimpleCipher<DoubleSubstitutionCipherMethod> DoubleSubstitutionCipher;

}

#endif
