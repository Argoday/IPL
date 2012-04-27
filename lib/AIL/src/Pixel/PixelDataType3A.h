
#ifndef PIXEL__PixelDataType3A_H
#define PIXEL__PixelDataType3A_H

#include <AIL.h>
#include <Data/DataTypes.h>

namespace Pixel {

//TODO: Actually make the Alpha channel do stuff
template <
	typename NumberType,
	int Xposition,
	int Yposition,
	int Zposition,
	int Aposition
> class AIL_DLL_EXPORT PixelDataType3A {
	public:
		typedef PixelDataType3A<NumberType,Xposition,Yposition,Zposition,Aposition> ThisType;
		typedef NumberType NumberType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType & _scalar):ParentType(scalar),a(scalar){}
		FINLINE          ThisType(const ThisType   & _pixel) :ParentType(_pixel),a(_pixel.a){}
	
		FINLINE ThisType & operator =(const ThisType   & _pixel ){x=_pixel.x;y=_pixel.y;z=_pixel.z;return (*this);}
		FINLINE ThisType & operator =(const NumberType & _scalar){x=_scalar ;y=_scalar ;z=_scalar ;return (*this);}

		FINLINE bool operator ==(const ThisType   & _pixel ) const {if(x==_pixel.x){if(y==_pixel.y){if(z==_pixel.z){if(a==_pixel.a){return true;}}}}return false;}
		FINLINE bool operator ==(const NumberType & _scalar) const {if(x==scalar  ){if(y==scalar  ){if(z==scalar  ){if(a==scalar  ){return true;}}}}return false;}

		FINLINE void setAs(const ThisType & _pixel)  {x=_pixel.x;y=_pixel.y;z=_pixel.z;a=_pixel.a;}
		FINLINE void setAsMin(const ThisType & pixel){if(x>pixel.x){x=pixel.x;}if(y>pixel.y){y=pixel.y;}if(z>pixel.z){z=pixel.z;}}
		FINLINE void setAsMax(const ThisType & pixel){if(x<pixel.x){x=pixel.x;}if(y<pixel.y){y=pixel.y;}if(z<pixel.z){z=pixel.z;}}

		FINLINE void setAs(const NumberType & _scalar)  {x=_scalar;y=_scalar;z=_scalar;}
		FINLINE void setAsMin(const NumberType & scalar){if(x>scalar){x=scalar;}if(y>scalar){y=scalar;}if(z>scalar){z=scalar;}}
		FINLINE void setAsMax(const NumberType & scalar){if(x<scalar){x=scalar;}if(y<scalar){y=scalar;}if(z<scalar){z=scalar;}}

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

		friend FINLINE ThisType operator-(const NumberType & scalar, const ThisType & pixel){return PixelDataType3A<NumberType,BasePixelDataType>(scalar)-pixel;}
		friend FINLINE ThisType operator+(const NumberType & scalar, const ThisType & pixel){return PixelDataType3A<NumberType,BasePixelDataType>(scalar)+pixel;}
		friend FINLINE ThisType operator*(const NumberType & scalar, const ThisType & pixel){return PixelDataType3A<NumberType,BasePixelDataType>(scalar)*pixel;}
		friend FINLINE ThisType operator/(const NumberType & scalar, const ThisType & pixel){return PixelDataType3A<NumberType,BasePixelDataType>(scalar)/pixel;}

		template <int TypeNumber> FINLINE const NumberType & get()    const ;
		template <              > FINLINE const NumberType & get<0>() const {return x;}
		template <              > FINLINE const NumberType & get<1>() const {return y;}
		template <              > FINLINE const NumberType & get<2>() const {return z;}
		template <              > FINLINE const NumberType & get<3>() const {return a;}

		template <int TypeNumber> FINLINE       NumberType & get()          ;
		template <              > FINLINE       NumberType & get<0>()       {return x;}
		template <              > FINLINE       NumberType & get<1>()       {return y;}
		template <              > FINLINE       NumberType & get<2>()       {return z;}
		template <              > FINLINE       NumberType & get<3>()       {return a;}

		template <int TypeNumber> FINLINE void set(const NumberType & _otherElement){this->get<TypeNumber>()=_otherElement;}

	private:
		NumberType a;
};

}

#endif
