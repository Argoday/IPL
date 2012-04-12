
#ifndef CRYPT__CryptString_H
#define CRYPT__CryptString_H

#include "Crypt.h"
#include "CryptChar.h"

#include <string>

namespace Crypt {

class CryptString_d;

class CRYPT_DLL_EXPORT CryptString {

	public:

		typedef CryptString ThisType;
		typedef CryptChar CharType;

		CryptString();
		CryptString(const ThisType & other);
		CryptString(const char * const & _value);
		CryptString(const std::string & _value);
		~CryptString();

		operator std::string() const ;

		const size_t size() const ;
		void resize(const size_t &sz);

		CryptChar & at(const size_t & i);
		const CryptChar & at(const size_t & i) const ;

		CryptChar & operator [](const size_t & i);
		const CryptChar & operator [](const size_t & i) const ;

	private:

		CryptString_d * _this;

};

}

#endif
