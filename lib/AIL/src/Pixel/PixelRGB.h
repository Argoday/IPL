
#ifndef PIXEL__Pixel_RGB_H
#define PIXEL__Pixel_RGB_H

#include <AIL.h>
#include <Meta/TypeVector.h>
#include <Pixel/PixelTypeID.h>
#include <Pixel/PixelDataType3.h>
#include <Pixel/PixelRange.h>
#include <Data/DataTypes.h>

namespace Pixel {

template <
	typename NumberType,
	typename PixelRangeType,
	int Rposition,
	int Gposition,
	int Bposition
> class AIL_DLL_EXPORT PixelRGBbaseType
	: public PixelDataType3<NumberType>
{
	public:

		typedef typename NumberType NumberType;
		typedef typename PixelRangeType RangeType;
		typedef PixelDataType3<NumberType> DataType;
		typedef PixelDataType3<NumberType> ParentType;
		typedef PixelRGBbaseType<NumberType,PixelRangeType,Rposition,Gposition,Bposition> ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		__forceinline ThisType(const DataType & _pixel):ParentType(_pixel){}
		__forceinline ThisType(const ThisType & _pixel):ParentType(_pixel){}

		__forceinline explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b){setR(_r);setG(_g);setB(_b);} //TODO: Use template specialization to keep memory accesses in-order?
		
		__forceinline void setR(const NumberType & _r) {this->set<Rposition>(_r);}
		__forceinline void setG(const NumberType & _g) {this->set<Gposition>(_g);}
		__forceinline void setB(const NumberType & _b) {this->set<Bposition>(_b);}

		__forceinline void clip(){RangeType::clip(*static_cast<ParentType*>(this));}

		__forceinline const NumberType & getR() const {return this->get<Rposition>();}
		__forceinline const NumberType & getG() const {return this->get<Gposition>();}
		__forceinline const NumberType & getB() const {return this->get<Bposition>();}

};

typedef PixelRGBbaseType<I1u,PixelRange_3i1u   ,0,1,2> PixelRGBi1utd;
typedef PixelRGBbaseType<I4 ,PixelRange_3i4_i1u,0,1,2> PixelRGBi4_i1utd;
typedef PixelRGBbaseType<I4 ,PixelRange_3i4_i2u,0,1,2> PixelRGBi4_i2utd;
typedef PixelRGBbaseType<F4 ,PixelRange_3f4    ,0,1,2> PixelRGBf4td;
typedef PixelRGBbaseType<F8 ,PixelRange_3f8    ,0,1,2> PixelRGBf8td;

class AIL_DLL_EXPORT PixelRGBi1u : public PixelRGBi1utd {
	public:
		typedef I1u NumberType;
		typedef PixelRGBi1utd::DataType DataType;
		typedef PixelRange_3i1u RangeType;
		typedef PixelRGBi1utd ParentType;
		typedef PixelRGBi1u ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		__forceinline ThisType(const DataType & _pixel):ParentType(_pixel){}
		__forceinline ThisType(const ThisType & _pixel):ParentType(_pixel){}

		__forceinline explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b){setR(_r);setG(_g);setB(_b);} //TODO: Use template specialization to keep memory accesses in-order?
};

class AIL_DLL_EXPORT PixelRGBf8 : public PixelRGBf8td {
	public:
		typedef F8 NumberType;
		typedef PixelRGBf8td::DataType DataType;
		typedef PixelRange_3f8 RangeType;
		typedef PixelRGBf8td ParentType;
		typedef PixelRGBf8 ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		__forceinline ThisType(const DataType & _pixel):ParentType(_pixel){}
		__forceinline ThisType(const ThisType & _pixel):ParentType(_pixel){}

		__forceinline explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b){setR(_r);setG(_g);setB(_b);} //TODO: Use template specialization to keep memory accesses in-order?
};

}

#endif
