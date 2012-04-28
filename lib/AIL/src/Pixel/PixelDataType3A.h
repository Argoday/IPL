
#ifndef PIXEL__PixelDataType3A_H
#define PIXEL__PixelDataType3A_H

#include <AIL.h>
#include <Data/DataTypes.h>

namespace Pixel {

//TODO: Actually make the Alpha channel do stuff
//Note: Only Aposition matters
template <
	typename NumberType,
	int Xposition,
	int Yposition,
	int Zposition,
	int Aposition
> class AIL_DLL_EXPORT PixelDataType3A {
	public:
		typedef NumberType NumberType;
		typedef PixelDataType3A<NumberType,Xposition,Yposition,Zposition,Aposition> ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType & _scalar):x(_scalar) ,y(_scalar) ,z(_scalar ),w(_scalar ){}
		FINLINE explicit ThisType(const NumberType & _scalar1,const NumberType & _scalar2,const NumberType & _scalar3,const NumberType & _scalar4):x(_scalar1) ,y(_scalar2) ,z(_scalar3),w(_scalar4){}
		FINLINE          ThisType(const ThisType   & _pixel) :x(_pixel.x),y(_pixel.y),z(_pixel.z),w(_pixel.w){}
	
		FINLINE ThisType & operator =(const ThisType   & _pixel ){x=_pixel.x;y=_pixel.y;z=_pixel.z;w=_pixel.w;return (*this);}
		FINLINE ThisType & operator =(const NumberType & _scalar){x=_scalar ;y=_scalar ;z=_scalar ;w=_scalar ;return (*this);}

		FINLINE bool operator ==(const ThisType   & _pixel ) const {if(x==_pixel.x){if(y==_pixel.y){if(z==_pixel.z){if(w==_pixel.w){return true;}}}}return false;}
		FINLINE bool operator ==(const NumberType & _scalar) const {if(x==scalar  ){if(y==scalar  ){if(z==scalar  ){if(w==scalar  ){return true;}}}}return false;}

		template <typename DiffNumberType> FINLINE const void setComp(const PixelDataType3A<DiffNumberType,Xposition,Yposition,Zposition,Aposition> & _pixel){x=_pixel.get<0>();y=_pixel.get<1>();z=_pixel.get<2>();w=_pixel.get<3>();};

		template <typename DiffNumberType> FINLINE PixelDataType3A<DiffNumberType> getAsComp() const {return PixelDataType3A<DiffNumberType>(x,y,z,w);};

		FINLINE void setAs   (const ThisType & _pixel){x=_pixel.x;y=_pixel.y;z=_pixel.z;w=_pixel.w;}
		FINLINE void setAsMin(const ThisType &  pixel){if(x>pixel.x){x=pixel.x;}if(y>pixel.y){y=pixel.y;}if(z>pixel.z){z=pixel.z;}}
		FINLINE void setAsMax(const ThisType &  pixel){if(x<pixel.x){x=pixel.x;}if(y<pixel.y){y=pixel.y;}if(z<pixel.z){z=pixel.z;}}

		FINLINE void setAs   (const NumberType & _scalar){x=_scalar;y=_scalar;z=_scalar;}
		FINLINE void setAsMin(const NumberType &  scalar){if(x>scalar){x=scalar;}if(y>scalar){y=scalar;}if(z>scalar){z=scalar;}}
		FINLINE void setAsMax(const NumberType &  scalar){if(x<scalar){x=scalar;}if(y<scalar){y=scalar;}if(z<scalar){z=scalar;}}

	//Operators
		//With Scalar:
		FINLINE ThisType & operator -=(const NumberType & scalar){x-=scalar;y-=scalar;z-=scalar;return (*this);}
		FINLINE ThisType & operator +=(const NumberType & scalar){x+=scalar;y+=scalar;z+=scalar;return (*this);}
		FINLINE ThisType & operator *=(const NumberType & scalar){x*=scalar;y*=scalar;z*=scalar;return (*this);}
		FINLINE ThisType & operator /=(const NumberType & scalar){x/=scalar;y/=scalar;z/=scalar;return (*this);}
		
		FINLINE ThisType operator-(const NumberType & scalar) const {return ThisType(*this)-=scalar;}
		FINLINE ThisType operator+(const NumberType & scalar) const {return ThisType(*this)+=scalar;}
		FINLINE ThisType operator*(const NumberType & scalar) const {return ThisType(*this)*=scalar;}
		FINLINE ThisType operator/(const NumberType & scalar) const {return ThisType(*this)/=scalar;}

		//With Pixel:
		FINLINE ThisType & operator -=(const ThisType & pixel){x-=pixel.x;y-=pixel.y;z-=pixel.z;return (*this);}
		FINLINE ThisType & operator +=(const ThisType & pixel){x+=pixel.x;y+=pixel.y;z+=pixel.z;return (*this);}
		FINLINE ThisType & operator *=(const ThisType & pixel){x*=pixel.x;y*=pixel.y;z*=pixel.z;return (*this);}
		FINLINE ThisType & operator /=(const ThisType & pixel){x/=pixel.x;y/=pixel.y;z/=pixel.z;return (*this);}

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
		template <              > FINLINE const NumberType & get<3>() const {return w;}

		template <int TypeNumber> FINLINE       NumberType & get()          ;
		template <              > FINLINE       NumberType & get<0>()       {return x;}
		template <              > FINLINE       NumberType & get<1>()       {return y;}
		template <              > FINLINE       NumberType & get<2>()       {return z;}
		template <              > FINLINE       NumberType & get<3>()       {return w;}

		template <int TypeNumber> FINLINE void set(const NumberType & _otherElement){this->get<TypeNumber>()=_otherElement;}

	protected:
		NumberType x;
		NumberType y;
		NumberType z;
		NumberType w;
};

typedef PixelDataType3A<I1u,0,1,2,3> PixelDataTypeA3i1u;
typedef PixelDataType3A<I2 ,0,1,2,3> PixelDataTypeA3i2;
typedef PixelDataType3A<I2u,0,1,2,3> PixelDataTypeA3i2u;
typedef PixelDataType3A<I4 ,0,1,2,3> PixelDataTypeA3i4;
typedef PixelDataType3A<F4 ,0,1,2,3> PixelDataTypeA3f4;
typedef PixelDataType3A<F8 ,0,1,2,3> PixelDataTypeA3f8;

typedef PixelDataType3A<I1u,3,0,1,2> PixelDataType3Ai1u;
typedef PixelDataType3A<I2 ,3,0,1,2> PixelDataType3Ai2;
typedef PixelDataType3A<I2u,3,0,1,2> PixelDataType3Ai2u;
typedef PixelDataType3A<I4 ,3,0,1,2> PixelDataType3Ai4;
typedef PixelDataType3A<F4 ,3,0,1,2> PixelDataType3Af4;
typedef PixelDataType3A<F8 ,3,0,1,2> PixelDataType3Af8;

}

#endif
