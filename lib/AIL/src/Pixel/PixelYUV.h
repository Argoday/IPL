
#ifndef PIXEL__PixelYUV_H
#define PIXEL__PixelYUV_H

#include <AIL.h>
#include <Meta/TypeVector.h>
#include <Pixel/PixelTypeID.h>
#include <Pixel/PixelDataTypeY2.h>
#include <Pixel/PixelRange.h>
#include <Data/DataTypes.h>

namespace Pixel {

template <
	typename NumberType,
	typename PixelRangeType,
	int Yposition,
	int Uposition,
	int Vposition
> class AIL_DLL_EXPORT PixelYUVbaseType
	: public PixelDataTypeY2<NumberType,Yposition>
{
	public:

		typedef typename NumberType NumberType;
		typedef typename PixelRangeType RangeType;
		typedef PixelDataTypeY2<NumberType,Yposition> DataType;
		typedef PixelDataTypeY2<NumberType,Yposition> ParentType;
		typedef PixelYUVbaseType<NumberType,PixelRangeType,Yposition,Uposition,Vposition> ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		__forceinline ThisType(const DataType & _pixel):ParentType(_pixel){}
		__forceinline ThisType(const ThisType & _pixel):ParentType(_pixel){}

		__forceinline explicit ThisType(const NumberType & _y,const NumberType & _u,const NumberType & _v){setY(_y);setU(_u);setV(_v);} //TODO: Use template specialization to keep memory accesses in-order
		
		__forceinline void setY(const NumberType & _y) {this->set<Yposition>(_y);}
		__forceinline void setU(const NumberType & _u) {this->set<Uposition>(_u);}
		__forceinline void setV(const NumberType & _v) {this->set<Vposition>(_v);}

		__forceinline void clip(){RangeType::clip(*static_cast<ParentType*>(this));} //TODO: What is the 'right' way to do this? , or is this the right way?
		
		__forceinline NumberType & getY() {return this->get<Yposition>();}
		__forceinline NumberType & getU() {return this->get<Uposition>();}
		__forceinline NumberType & getV() {return this->get<Vposition>();}

		__forceinline const NumberType & getY() const {return this->get<Yposition>();}
		__forceinline const NumberType & getU() const {return this->get<Uposition>();}
		__forceinline const NumberType & getV() const {return this->get<Vposition>();}

};

//typedef PixelYUVbaseType<I1u,PixelRange_3i1u ,0,1,2> PixelYUVi1u;
//typedef PixelYUVbaseType<I4 ,PixelRange_3i4_1,0,1,2> PixelYUVi4_1;
//typedef PixelYUVbaseType<I4 ,PixelRange_3i4_2,0,1,2> PixelYUVi4_2;
//typedef PixelYUVbaseType<F8 ,PixelRange_3f8  ,0,1,2> PixelYUVf8;
typedef PixelYUVbaseType<F8,PixelRange_Y2_0f8  ,0,1,2> PixelYUVf8td;

class AIL_DLL_EXPORT PixelYUVf8 : public PixelYUVf8td {
	public:
		typedef F8 NumberType;
		typedef PixelYUVf8td::DataType DataType;
		typedef PixelRange_Y2_0f8 RangeType;
		typedef PixelYUVf8td ParentType;
		typedef PixelYUVf8 ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		__forceinline ThisType(const DataType & _pixel):ParentType(_pixel){}
		__forceinline ThisType(const ThisType & _pixel):ParentType(_pixel){}

		__forceinline explicit ThisType(const NumberType & _y,const NumberType & _u,const NumberType & _v){setY(_y);setU(_u);setV(_v);}
};

}

#endif
