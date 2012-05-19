
#ifndef META__Boolean_H
#define META__Boolean_H

#include "ACore.h"

namespace Meta {

class ACORE_DLL_EXPORT Boolean {

	public:

		typedef Boolean ThisType;
		typedef bool NumberType;

		NumberType value;

		FINLINE Boolean():value(false){}
		FINLINE Boolean(const ThisType   &  other);
		FINLINE Boolean(const NumberType & _value);

		FINLINE ThisType & operator =(const ThisType   &  other);
		FINLINE ThisType & operator =(const NumberType & _value);

		FINLINE operator bool() const {return value;}

		FINLINE bool operator ==(const ThisType   &  other) const ;
		FINLINE bool operator ==(const NumberType & _value) const ;

		FINLINE void setAs(const ThisType   &  other);
		FINLINE void setAs(const NumberType & _value);

	//Operators
		//With NumberType:
		FINLINE ThisType & operator -=(const NumberType & number);
		FINLINE ThisType & operator +=(const NumberType & number);
		FINLINE ThisType & operator *=(const NumberType & number);
		FINLINE ThisType & operator /=(const NumberType & number);

		FINLINE ThisType operator-(const NumberType & number) const ;
		FINLINE ThisType operator+(const NumberType & number) const ;
		FINLINE ThisType operator*(const NumberType & number) const ;
		FINLINE ThisType operator/(const NumberType & number) const ;

		//With ThisType:
		FINLINE ThisType & operator -=(const ThisType & other);
		FINLINE ThisType & operator +=(const ThisType & other);
		FINLINE ThisType & operator *=(const ThisType & other);
		FINLINE ThisType & operator /=(const ThisType & other);

		FINLINE ThisType operator-(const ThisType & other) const ;
		FINLINE ThisType operator+(const ThisType & other) const ;
		FINLINE ThisType operator*(const ThisType & other) const ;
		FINLINE ThisType operator/(const ThisType & other) const ;

		friend FINLINE ThisType operator-(const NumberType & number, const ThisType & other);
		friend FINLINE ThisType operator+(const NumberType & number, const ThisType & other);
		friend FINLINE ThisType operator*(const NumberType & number, const ThisType & other);
		friend FINLINE ThisType operator/(const NumberType & number, const ThisType & other);

};

}

#include "Boolean_cpp.h"

#endif
