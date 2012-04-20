
#ifndef PIXEL__Pixel_RGBA_H
#define PIXEL__Pixel_RGBA_H

#include <AIL.h>
#include <Meta/TypeVector.h>
#include <Pixel/PixelTypeID.h>
#include <Pixel/PixelDataType3.h>
#include <Pixel/PixelDataType3A.h>
#include <Pixel/PixelRange.h>
#include <Data/DataTypes.h>

namespace Pixel {

template <
	typename NumberType,
	typename PixelRangeType,
	int Rposition,
	int Gposition,
	int Bposition
> class AIL_DLL_EXPORT PixelRGBAbaseType
	: public PixelDataType3A<NumberType,PixelDataType3<NumberType>>
{
	public:

		typedef typename NumberType NumberType;
		typedef typename PixelRangeType RangeType;
		typedef PixelDataType3A<NumberType,PixelDataType3<NumberType>> DataType;
		typedef PixelDataType3A<NumberType,PixelDataType3<NumberType>> ParentType;
		typedef PixelRGBAbaseType<NumberType,PixelRangeType,Rposition,Gposition,Bposition> ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		__forceinline ThisType(const DataType & _pixel):ParentType(_pixel){}
		__forceinline ThisType(const ThisType & _pixel):ParentType(_pixel){}

		__forceinline explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b){setR(_r);setG(_g);setB(_b);} //TODO: Use template specialization to keep memory accesses in-order?
		
		__forceinline void setR(const NumberType & _r) {this->set<Rposition>(_r);}
		__forceinline void setG(const NumberType & _g) {this->set<Gposition>(_g);}
		__forceinline void setB(const NumberType & _b) {this->set<Bposition>(_b);}
		__forceinline void setA(const NumberType & _a) {this->set<3>(_a);}

		__forceinline void clip(){RangeType::clip(*static_cast<ParentType*>(this));}

		__forceinline const NumberType & getR() const {return this->get<Rposition>();}
		__forceinline const NumberType & getG() const {return this->get<Gposition>();}
		__forceinline const NumberType & getB() const {return this->get<Bposition>();}

};

/*typedef PixelRGBbaseType<I1u,PixelRange_3i1u ,0,1,2> PixelRGBi1u;
typedef PixelRGBbaseType<I4 ,PixelRange_3i4_1,0,1,2> PixelRGBi4_1;
typedef PixelRGBbaseType<I4 ,PixelRange_3i4_2,0,1,2> PixelRGBi4_2;//*/
typedef PixelRGBbaseType<F8 ,PixelRange_3f8  ,0,1,2> PixelRGBf8td;

class AIL_DLL_EXPORT PixelRGBf8 : public PixelRGBf8td {
	public:
		typedef F8 NumberType;
		typedef PixelRGBf8td::DataType DataType;
		typedef PixelRGBf8td ParentType;
		typedef PixelRGBf8 ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		__forceinline ThisType(const DataType & _pixel):ParentType(_pixel){}
		__forceinline ThisType(const ThisType & _pixel):ParentType(_pixel){}

		__forceinline explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b){setR(_r);setG(_g);setB(_b);} //TODO: Use template specialization to keep memory accesses in-order?
};

/*typedef PixelRGBbaseType<I1u,PixelRange_3i1u ,2,1,0> PixelBGRi1u;
typedef PixelRGBbaseType<I4 ,PixelRange_3i4_1,2,1,0> PixelBGRi4_1;
typedef PixelRGBbaseType<I4 ,PixelRange_3i4_2,2,1,0> PixelBGRi4_2;
typedef PixelRGBbaseType<F8 ,PixelRange_3f8  ,2,1,0> PixelBGRf8;//*/

}

#endif
