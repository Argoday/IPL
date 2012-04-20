
#ifndef PIXEL__PixelDataType1_H
#define PIXEL__PixelDataType1_H

#include <AIL.h>
#include <Meta/Boolean.h>
#include <Data/DataTypes.h>

namespace Pixel {

template <
	typename NumberType
> class AIL_DLL_EXPORT PixelDataType1 {
	public:
		typedef PixelDataType1<NumberType> ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):x(_scalar){}
		__forceinline          ThisType(const ThisType   & _pixel) :x(_pixel.x){}
	
		__forceinline ThisType &operator =(const ThisType & _pixel )  {x=_pixel.x;return (*this);}
		__forceinline ThisType &operator =(const NumberType & _scalar){x=_scalar;return (*this);}

		__forceinline bool operator ==(const ThisType   & _pixel ) const {return (x==_pixel.x);}
		__forceinline bool operator ==(const NumberType & _scalar) const {return (x==_scalar);}

		__forceinline void setAs(const ThisType & _pixel)  {x=_pixel.x;}
		__forceinline void setAsMin(const ThisType & pixel){if(x>pixel.x){x=pixel.x;}}
		__forceinline void setAsMax(const ThisType & pixel){if(x<pixel.x){x=pixel.x;}}

		__forceinline void setAs(const NumberType & _scalar)  {x=_scalar;}
		__forceinline void setAsMin(const NumberType & scalar){if(x>scalar){x=scalar;}}
		__forceinline void setAsMax(const NumberType & scalar){if(x<scalar){x=scalar;}}

	//Operators
		//With Scalar:
		__forceinline ThisType &operator -=(const NumberType & scalar){x-=scalar;return (*this);}
		__forceinline ThisType &operator +=(const NumberType & scalar){x+=scalar;return (*this);}
		__forceinline ThisType &operator *=(const NumberType & scalar){x*=scalar;return (*this);}
		__forceinline ThisType &operator /=(const NumberType & scalar){x/=scalar;return (*this);}
		
		__forceinline ThisType operator-(const NumberType & scalar) const {return ThisType(*this)-=scalar;}
		__forceinline ThisType operator+(const NumberType & scalar) const {return ThisType(*this)+=scalar;}
		__forceinline ThisType operator*(const NumberType & scalar) const {return ThisType(*this)*=scalar;}
		__forceinline ThisType operator/(const NumberType & scalar) const {return ThisType(*this)/=scalar;}

		//With Pixel:
		__forceinline ThisType &operator -=(const ThisType & pixel){x-=pixel.x;return (*this);}
		__forceinline ThisType &operator +=(const ThisType & pixel){x+=pixel.x;return (*this);}
		__forceinline ThisType &operator *=(const ThisType & pixel){x*=pixel.x;return (*this);}
		__forceinline ThisType &operator /=(const ThisType & pixel){x/=pixel.x;return (*this);}

		__forceinline ThisType operator-(const ThisType & pixel) const {return ThisType(*this)-=pixel;}
		__forceinline ThisType operator+(const ThisType & pixel) const {return ThisType(*this)+=pixel;}
		__forceinline ThisType operator*(const ThisType & pixel) const {return ThisType(*this)*=pixel;}
		__forceinline ThisType operator/(const ThisType & pixel) const {return ThisType(*this)/=pixel;}

		friend __forceinline ThisType operator-(const NumberType & scalar, const ThisType & pixel){return PixelDataType1<NumberType>(scalar)-pixel;}
		friend __forceinline ThisType operator+(const NumberType & scalar, const ThisType & pixel){return PixelDataType1<NumberType>(scalar)+pixel;}
		friend __forceinline ThisType operator*(const NumberType & scalar, const ThisType & pixel){return PixelDataType1<NumberType>(scalar)*pixel;}
		friend __forceinline ThisType operator/(const NumberType & scalar, const ThisType & pixel){return PixelDataType1<NumberType>(scalar)/pixel;}

		template <int TypeNumber> __forceinline const NumberType & get()    const ;
		template <              > __forceinline const NumberType & get<0>() const {return x;}

		template <int TypeNumber> __forceinline       NumberType & get()          ;
		template <              > __forceinline       NumberType & get<0>()       {return x;}

		template <int TypeNumber> __forceinline void set(const NumberType & _otherElement){this->get<TypeNumber>()=_otherElement;}

	protected:
		NumberType x;
};

typedef PixelDataType1<Meta::Boolean> PixelDataType1b1;
typedef PixelDataType1<I1u>           PixelDataType1i1u;
typedef PixelDataType1<I4>            PixelDataType1i4;
typedef PixelDataType1<F4>            PixelDataType1f4;
typedef PixelDataType1<F8>            PixelDataType1f8;

}


#endif
