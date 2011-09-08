
#ifndef PIXEL__PixelDataType3_H
#define PIXEL__PixelDataType3_H

#include <AIL.h>
#include <Meta/DataTypes.h>

namespace Pixel {

template <
	typename NumberType
> class AIL_DLL_EXPORT PixelDataType3 {
	public:
		typedef PixelDataType3<NumberType> ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType &_scalar):x(_scalar),y(_scalar),z(_scalar){}
		__forceinline ThisType(const ThisType &_pixel):x(_pixel.x),y(_pixel.y),z(_pixel.z){}
	
		__forceinline ThisType &operator =(const ThisType &_pixel )  {x=_pixel.x;y=_pixel.y;z=_pixel.z;return (*this);}
		__forceinline ThisType &operator =(const NumberType &_scalar){x=_scalar ;y=_scalar ;z=_scalar ;return (*this);}

		__forceinline bool operator ==(const ThisType   &_pixel ) const {if(x==_pixel.x){if(y==_pixel.y){if(z==_pixel.z){return true;}}}return false;}
		__forceinline bool operator ==(const NumberType &_scalar) const {if(x==scalar  ){if(y==scalar  ){if(z==scalar  ){return true;}}}return false;}

		__forceinline void setAs(const ThisType &_pixel)  {x=_pixel.x;y=_pixel.y;z=_pixel.z;}
		__forceinline void setAsMin(const ThisType &pixel){if(x>pixel.x){x=pixel.x;}if(y>pixel.y){y=pixel.y;}if(z>pixel.z){z=pixel.z;}}
		__forceinline void setAsMax(const ThisType &pixel){if(x<pixel.x){x=pixel.x;}if(y<pixel.y){y=pixel.y;}if(z<pixel.z){z=pixel.z;}}

		__forceinline void setAs(const NumberType &_scalar)  {x=_scalar;y=_scalar;z=_scalar;}
		__forceinline void setAsMin(const NumberType &scalar){if(x>scalar){x=scalar;}if(y>scalar){y=scalar;}if(z>scalar){z=scalar;}}
		__forceinline void setAsMax(const NumberType &scalar){if(x<scalar){x=scalar;}if(y<scalar){y=scalar;}if(z<scalar){z=scalar;}}

	//Operators
		//With Scalar:
		__forceinline ThisType &operator -=(const NumberType &scalar){x-=scalar;y-=scalar;z-=scalar;return (*this);}
		__forceinline ThisType &operator +=(const NumberType &scalar){x+=scalar;y+=scalar;z+=scalar;return (*this);}
		__forceinline ThisType &operator *=(const NumberType &scalar){x*=scalar;y*=scalar;z*=scalar;return (*this);}
		__forceinline ThisType &operator /=(const NumberType &scalar){x/=scalar;y/=scalar;z/=scalar;return (*this);}
		
		__forceinline ThisType operator-(const NumberType &scalar) const {return ThisType(*this)-=scalar;}
		__forceinline ThisType operator+(const NumberType &scalar) const {return ThisType(*this)+=scalar;}
		__forceinline ThisType operator*(const NumberType &scalar) const {return ThisType(*this)*=scalar;}
		__forceinline ThisType operator/(const NumberType &scalar) const {return ThisType(*this)/=scalar;}

		//With Pixel:
		__forceinline ThisType &operator -=(const ThisType &pixel){x-=pixel.x;y-=pixel.y;z-=pixel.z;return (*this);}
		__forceinline ThisType &operator +=(const ThisType &pixel){x+=pixel.x;y+=pixel.y;z+=pixel.z;return (*this);}
		__forceinline ThisType &operator *=(const ThisType &pixel){x*=pixel.x;y*=pixel.y;z*=pixel.z;return (*this);}
		__forceinline ThisType &operator /=(const ThisType &pixel){x/=pixel.x;y/=pixel.y;z/=pixel.z;return (*this);}

		__forceinline ThisType operator-(const ThisType &pixel) const {return ThisType(*this)-=pixel;}
		__forceinline ThisType operator+(const ThisType &pixel) const {return ThisType(*this)+=pixel;}
		__forceinline ThisType operator*(const ThisType &pixel) const {return ThisType(*this)*=pixel;}
		__forceinline ThisType operator/(const ThisType &pixel) const {return ThisType(*this)/=pixel;}

		friend __forceinline ThisType operator-(const NumberType &scalar, const ThisType &pixel){return PixelDataType3<NumberType>(scalar)-pixel;}
		friend __forceinline ThisType operator+(const NumberType &scalar, const ThisType &pixel){return PixelDataType3<NumberType>(scalar)+pixel;}
		friend __forceinline ThisType operator*(const NumberType &scalar, const ThisType &pixel){return PixelDataType3<NumberType>(scalar)*pixel;}
		friend __forceinline ThisType operator/(const NumberType &scalar, const ThisType &pixel){return PixelDataType3<NumberType>(scalar)/pixel;}

		template <int TypeNumber> __forceinline const NumberType & get()    const ;
		template <              > __forceinline const NumberType & get<0>() const {return x;}
		template <              > __forceinline const NumberType & get<1>() const {return y;}
		template <              > __forceinline const NumberType & get<2>() const {return z;}

		template <int TypeNumber> __forceinline       NumberType & get()          ;
		template <              > __forceinline       NumberType & get<0>()       {return x;}
		template <              > __forceinline       NumberType & get<1>()       {return y;}
		template <              > __forceinline       NumberType & get<2>()       {return z;}

		template <int TypeNumber> __forceinline void set(const NumberType & _otherElement){this->get<TypeNumber>()=_otherElement;}

	private:
		NumberType x;
		NumberType y;
		NumberType z;
};

typedef PixelDataType3<I1u> PixelDataType3i1u;
typedef PixelDataType3<I4>  PixelDataType3i4;
typedef PixelDataType3<F4>  PixelDataType3f4;
typedef PixelDataType3<F8>  PixelDataType3f8;

}

#endif
