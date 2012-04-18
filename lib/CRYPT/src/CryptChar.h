
#ifndef CRYPT__CryptChar_H
#define CRYPT__CryptChar_H

#include "Crypt.h"
#include "Data/DataTypes.h"

namespace Crypt {

class CRYPT_DLL_EXPORT CryptChar {

	public:

		typedef CryptChar ThisType;
		typedef I4 NumberType;
		typedef I1 CharType;

		CryptChar():value(-1){}
		CryptChar(const ThisType & other):value(other.value){}
		CryptChar(const NumberType & _value):value(_value){clip();}
		CryptChar(const CharType & _char){setValue(_char);}

		void setValue(const NumberType & _value){value=_value;clip();}
		void setValue(const CharType & _value);

		const NumberType & getValue() const {return value;}

		ThisType &operator =(const NumberType &_value){setValue(_value);return(*this);}
		ThisType &operator =(const CharType &_value){setValue(_value);return(*this);}
		ThisType &operator =(const ThisType &other){value=other.value;return(*this);}

		bool operator ==(const NumberType &_value) const {return (value==_value);}
		bool operator ==(const ThisType &other) const {return (value==other.value);}

		ThisType &operator -=(const NumberType &number){if(isChar()==true){value-=number;clip();}return(*this);}
		ThisType &operator +=(const NumberType &number){if(isChar()==true){value+=number;clip();}return(*this);}
		ThisType &operator *=(const NumberType &number){if(isChar()==true){value*=number;clip();}return(*this);}

		ThisType operator-(const NumberType &number) const {return ThisType(*this)-=value;}
		ThisType operator+(const NumberType &number) const {return ThisType(*this)+=value;}
		ThisType operator*(const NumberType &number) const {return ThisType(*this)*=value;}

		ThisType &operator -=(const ThisType &other){if(isChar()==true){value-=other.value;clip();}return(*this);}
		ThisType &operator +=(const ThisType &other){if(isChar()==true){value+=other.value;clip();}return(*this);}
		ThisType &operator *=(const ThisType &other){if(isChar()==true){value*=other.value;clip();}return(*this);}

		ThisType operator-(const ThisType &other) const {return ThisType(*this)-=other;}
		ThisType operator+(const ThisType &other) const {return ThisType(*this)+=other;}
		ThisType operator*(const ThisType &other) const {return ThisType(*this)*=other;}

		friend ThisType operator-(const NumberType &number, const ThisType &other){return ThisType(number)-other;}
		friend ThisType operator+(const NumberType &number, const ThisType &other){return ThisType(number)-other;}
		friend ThisType operator*(const NumberType &number, const ThisType &other){return ThisType(number)-other;}

		operator NumberType() const ;
		operator CharType() const ;

		const bool isChar() const {return (value>=0);}

		const static NumberType alphabetSize = 26;

	private:

		void clip(){
			value=value%alphabetSize;
			if(value<0){value+=alphabetSize;}
		}

		NumberType value;

};

}

#endif
