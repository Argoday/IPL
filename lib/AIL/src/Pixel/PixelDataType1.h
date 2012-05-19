
#ifndef PIXEL__PixelDataType1_H
#define PIXEL__PixelDataType1_H

#include <AIL.h>
#include <Data/DataTypes.h>

namespace Pixel {

template <
	typename NumberType
> class AIL_DLL_EXPORT PixelDataType1 {
	public:
		typedef NumberType                 NumberType;
		typedef PixelDataType1<NumberType> ThisType;

		FINLINE explicit PixelDataType1(){}
		FINLINE explicit PixelDataType1(const NumberType & _scalar):x(_scalar){}
		FINLINE          PixelDataType1(const ThisType   & _pixel) :x(_pixel.x){}
	
		FINLINE ThisType & operator =(const ThisType   & _pixel ){x=_pixel.x;return (*this);}
		FINLINE ThisType & operator =(const NumberType & _scalar){x=_scalar ;return (*this);}

		FINLINE bool operator ==(const ThisType   & _pixel ) const {return (x==_pixel.x);}
		FINLINE bool operator ==(const NumberType & _scalar) const {return (x==_scalar );}

		template <typename DiffNumberType> FINLINE const void setComp(const PixelDataType1<DiffNumberType> & _pixel){x=_pixel.get<0>();};

		template <typename DiffNumberType> FINLINE PixelDataType1<DiffNumberType> getAsComp() const {return PixelDataType1<DiffNumberType>(x);};

		FINLINE void setAs   (const ThisType & _pixel){x=_pixel.x;}
		FINLINE void setAsMin(const ThisType &  pixel){if(x>pixel.x){x=pixel.x;}}
		FINLINE void setAsMax(const ThisType &  pixel){if(x<pixel.x){x=pixel.x;}}

		FINLINE void setAs   (const NumberType & _scalar){x=_scalar;}
		FINLINE void setAsMin(const NumberType &  scalar){if(x>scalar){x=scalar;}}
		FINLINE void setAsMax(const NumberType &  scalar){if(x<scalar){x=scalar;}}

	//Operators
		//With Scalar:
		FINLINE ThisType & operator -=(const NumberType & scalar){x-=scalar;return (*this);}
		FINLINE ThisType & operator +=(const NumberType & scalar){x+=scalar;return (*this);}
		FINLINE ThisType & operator *=(const NumberType & scalar){x*=scalar;return (*this);}
		FINLINE ThisType & operator /=(const NumberType & scalar){x/=scalar;return (*this);}
		
		FINLINE ThisType operator-(const NumberType & scalar) const {return ThisType(*this)-=scalar;}
		FINLINE ThisType operator+(const NumberType & scalar) const {return ThisType(*this)+=scalar;}
		FINLINE ThisType operator*(const NumberType & scalar) const {return ThisType(*this)*=scalar;}
		FINLINE ThisType operator/(const NumberType & scalar) const {return ThisType(*this)/=scalar;}

		//With Pixel:
		FINLINE ThisType & operator -=(const ThisType & pixel){x-=pixel.x;return (*this);}
		FINLINE ThisType & operator +=(const ThisType & pixel){x+=pixel.x;return (*this);}
		FINLINE ThisType & operator *=(const ThisType & pixel){x*=pixel.x;return (*this);}
		FINLINE ThisType & operator /=(const ThisType & pixel){x/=pixel.x;return (*this);}

		FINLINE ThisType operator-(const ThisType & pixel) const {return ThisType(*this)-=pixel;}
		FINLINE ThisType operator+(const ThisType & pixel) const {return ThisType(*this)+=pixel;}
		FINLINE ThisType operator*(const ThisType & pixel) const {return ThisType(*this)*=pixel;}
		FINLINE ThisType operator/(const ThisType & pixel) const {return ThisType(*this)/=pixel;}

		friend FINLINE ThisType operator-(const NumberType & scalar, const ThisType & pixel){return PixelDataType1<NumberType>(scalar)-pixel;}
		friend FINLINE ThisType operator+(const NumberType & scalar, const ThisType & pixel){return PixelDataType1<NumberType>(scalar)+pixel;}
		friend FINLINE ThisType operator*(const NumberType & scalar, const ThisType & pixel){return PixelDataType1<NumberType>(scalar)*pixel;}
		friend FINLINE ThisType operator/(const NumberType & scalar, const ThisType & pixel){return PixelDataType1<NumberType>(scalar)/pixel;}

		template <int TypeNumber> FINLINE const NumberType & get()    const ;
		template <              > FINLINE const NumberType & get<0>() const {return x;}

		template <int TypeNumber> FINLINE       NumberType & get()          ;
		template <              > FINLINE       NumberType & get<0>()       {return x;}

		template <int TypeNumber> FINLINE void set(const NumberType & _otherElement){this->get<TypeNumber>()=_otherElement;}

	protected:
		NumberType x;
};

typedef PixelDataType1<B1 > PixelDataType1b1;
typedef PixelDataType1<I1u> PixelDataType1i1u;
typedef PixelDataType1<I4 > PixelDataType1i4;
typedef PixelDataType1<F4 > PixelDataType1f4;
typedef PixelDataType1<F8 > PixelDataType1f8;

}


#endif
