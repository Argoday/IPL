
#ifndef PIXEL__PixelDataTypeY2_H
#define PIXEL__PixelDataTypeY2_H

#include <AIL.h>
#include <Data/DataTypes.h>

namespace Pixel {

template <
	typename NumberType,
	int Yposition
> class AIL_DLL_EXPORT PixelDataTypeY2 {
	public:
		typedef PixelDataTypeY2<NumberType,Yposition> ThisType;
		typedef NumberType NumberType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType & _scalar):x(_scalar) ,y(_scalar) ,z(_scalar){} //TODO: Is this correct? - I expect not , perhaps use (scalar,0,0) ?
		FINLINE          ThisType(const ThisType   & _pixel) :x(_pixel.x),y(_pixel.y),z(_pixel.z){}
	
		FINLINE ThisType & operator =(const ThisType   & _pixel ){x=_pixel.x;y=_pixel.y;z=_pixel.z;return (*this);}
		FINLINE ThisType & operator =(const NumberType & _scalar){x=_scalar ;y=_scalar ;z=_scalar ;return (*this);} //TODO: Is this correct? - I expect not

		FINLINE bool operator ==(const ThisType   & _pixel ) const {if(x==_pixel.x){if(y==_pixel.y){if(z==_pixel.z){return true;}}}return false;}
		FINLINE bool operator ==(const NumberType & _scalar) const {if(x==scalar  ){if(y==scalar  ){if(z==scalar  ){return true;}}}return false;}

		FINLINE void setAs(const ThisType & _pixel)  {x=_pixel.x;y=_pixel.y;z=_pixel.z;}
		FINLINE void setAsMin(const ThisType & pixel){if(pixel.get<Yposition>()<get<Yposition>()){(*this)=pixel;}}
		FINLINE void setAsMax(const ThisType & pixel){if(pixel.get<Yposition>()>get<Yposition>()){(*this)=pixel;}}

		FINLINE void setAs(const NumberType & _scalar)  {x=_scalar;y=_scalar;z=_scalar;}
		FINLINE void setAsMin(const NumberType & scalar){if(scalar<get<Yposition>()){(*this)=scalar;}}
		FINLINE void setAsMax(const NumberType & scalar){if(scalar>get<Yposition>()){(*this)=scalar;}}

	//Operators
		//With Scalar:
		FINLINE ThisType &operator -=(const NumberType & scalar){x-=scalar;y-=scalar;z-=scalar;return (*this);}
		FINLINE ThisType &operator +=(const NumberType & scalar){x+=scalar;y+=scalar;z+=scalar;return (*this);}
		FINLINE ThisType &operator *=(const NumberType & scalar){x*=scalar;y*=scalar;z*=scalar;return (*this);}
		FINLINE ThisType &operator /=(const NumberType & scalar){x/=scalar;y/=scalar;z/=scalar;return (*this);}
		
		FINLINE ThisType operator-(const NumberType & scalar) const {return ThisType(*this)-=scalar;}
		FINLINE ThisType operator+(const NumberType & scalar) const {return ThisType(*this)+=scalar;}
		FINLINE ThisType operator*(const NumberType & scalar) const {return ThisType(*this)*=scalar;}
		FINLINE ThisType operator/(const NumberType & scalar) const {return ThisType(*this)/=scalar;}

		//With Pixel:
		FINLINE ThisType &operator -=(const ThisType & pixel){x-=pixel.x;y-=pixel.y;z-=pixel.z;return (*this);}
		FINLINE ThisType &operator +=(const ThisType & pixel){x+=pixel.x;y+=pixel.y;z+=pixel.z;return (*this);}
		FINLINE ThisType &operator *=(const ThisType & pixel){x*=pixel.x;y*=pixel.y;z*=pixel.z;return (*this);}
		FINLINE ThisType &operator /=(const ThisType & pixel){x/=pixel.x;y/=pixel.y;z/=pixel.z;return (*this);}

		FINLINE ThisType operator-(const ThisType & pixel) const {return ThisType(*this)-=pixel;}
		FINLINE ThisType operator+(const ThisType & pixel) const {return ThisType(*this)+=pixel;}
		FINLINE ThisType operator*(const ThisType & pixel) const {return ThisType(*this)*=pixel;}
		FINLINE ThisType operator/(const ThisType & pixel) const {return ThisType(*this)/=pixel;}

		friend FINLINE ThisType operator-(const NumberType & scalar, const ThisType & pixel){return PixelDataType3<NumberType>(scalar)-pixel;}
		friend FINLINE ThisType operator+(const NumberType & scalar, const ThisType & pixel){return PixelDataType3<NumberType>(scalar)+pixel;}
		friend FINLINE ThisType operator*(const NumberType & scalar, const ThisType & pixel){return PixelDataType3<NumberType>(scalar)*pixel;}
		friend FINLINE ThisType operator/(const NumberType & scalar, const ThisType & pixel){return PixelDataType3<NumberType>(scalar)/pixel;}

		template <int TypeNumber> FINLINE const NumberType & get()    const ;
		template <              > FINLINE const NumberType & get<0>() const {return x;}
		template <              > FINLINE const NumberType & get<1>() const {return y;}
		template <              > FINLINE const NumberType & get<2>() const {return z;}

		template <int TypeNumber> FINLINE       NumberType & get()          ;
		template <              > FINLINE       NumberType & get<0>()       {return x;}
		template <              > FINLINE       NumberType & get<1>()       {return y;}
		template <              > FINLINE       NumberType & get<2>()       {return z;}

		template <int TypeNumber> FINLINE void set(const NumberType & _otherElement){this->get<TypeNumber>()=_otherElement;}

	protected:
		NumberType x;
		NumberType y;
		NumberType z;
};

typedef PixelDataTypeY2<I1u,0> PixelDataTypeY2_0i1u;

typedef PixelDataTypeY2<I2u,0> PixelDataTypeY2_0i2u;
typedef PixelDataTypeY2<I2 ,0> PixelDataTypeY2_0i2;

typedef PixelDataTypeY2<I4 ,0> PixelDataTypeY2_0i4;

typedef PixelDataTypeY2<F4 ,0> PixelDataTypeY2_0f4;
typedef PixelDataTypeY2<F8 ,0> PixelDataTypeY2_0f8;

}


#endif
