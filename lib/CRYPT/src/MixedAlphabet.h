
#ifndef CRYPT__MixedAlphabet_H
#define CRYPT__MixedAlphabet_H

#include "Crypt.h"
#include "CryptChar.h"
#include "CryptString.h"

namespace Crypt {

class CRYPT_DLL_EXPORT MixedAlphabet {

	public:

		MixedAlphabet();
		MixedAlphabet(const CryptString & key);
		~MixedAlphabet();

		void generate(const CryptString & key);

		void rotate(const int & shift);

		size_t positionOf(const CryptChar & letter) const ;
		const CryptChar & charAt(const size_t & index) const ;

	private:

		class MixedAlphabet_d;
		MixedAlphabet_d * _this;

};

}

#endif
