
#ifndef META__Boolean_H
#define META__Boolean_H

#include "ACore.h"

namespace Meta {

class ACORE_DLL_EXPORT Boolean {

	public:

		typedef Boolean ThisType;
		typedef bool NumberType;

		NumberType value;

		__forceinline ThisType():value(false){}
		__forceinline ThisType(const ThisType &other);
		__forceinline ThisType(const NumberType &_value);

		__forceinline ThisType &operator =(const ThisType &other);
		__forceinline ThisType &operator =(const NumberType &_value);

		__forceinline operator bool() const {return value;}

		__forceinline bool operator ==(const ThisType &other) const ;
		__forceinline bool operator ==(const NumberType &_value) const ;

		__forceinline void setAs(const ThisType &other);
		__forceinline void setAs(const NumberType &_value);

	//Operators
		//With NumberType:
		__forceinline ThisType &operator -=(const NumberType &number);
		__forceinline ThisType &operator +=(const NumberType &number);
		__forceinline ThisType &operator *=(const NumberType &number);
		__forceinline ThisType &operator /=(const NumberType &number);

		__forceinline ThisType operator-(const NumberType &number) const ;
		__forceinline ThisType operator+(const NumberType &number) const ;
		__forceinline ThisType operator*(const NumberType &number) const ;
		__forceinline ThisType operator/(const NumberType &number) const ;

		//With ThisType:
		__forceinline ThisType &operator -=(const ThisType &other);
		__forceinline ThisType &operator +=(const ThisType &other);
		__forceinline ThisType &operator *=(const ThisType &other);
		__forceinline ThisType &operator /=(const ThisType &other);

		__forceinline ThisType operator-(const ThisType &other) const ;
		__forceinline ThisType operator+(const ThisType &other) const ;
		__forceinline ThisType operator*(const ThisType &other) const ;
		__forceinline ThisType operator/(const ThisType &other) const ;

		friend __forceinline ThisType operator-(const NumberType &number, const ThisType &other);
		friend __forceinline ThisType operator+(const NumberType &number, const ThisType &other);
		friend __forceinline ThisType operator*(const NumberType &number, const ThisType &other);
		friend __forceinline ThisType operator/(const NumberType &number, const ThisType &other);

};

}

#include "Boolean_cpp.h"

#endif
