
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

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		FINLINE ThisType(const DataType & _pixel):ParentType(_pixel){}
		FINLINE ThisType(const ThisType & _pixel):ParentType(_pixel){}

		FINLINE explicit ThisType(const NumberType & _y,const NumberType & _u,const NumberType & _v){setY(_y);setU(_u);setV(_v);}
		
		FINLINE void setY(const NumberType & _y) {this->set<Yposition>(_y);}
		FINLINE void setU(const NumberType & _u) {this->set<Uposition>(_u);}
		FINLINE void setV(const NumberType & _v) {this->set<Vposition>(_v);}

		FINLINE void clip(){RangeType::clip(*static_cast<ParentType*>(this));} //TODO: What is the 'right' way to do this? , or is this the right way?
		
		FINLINE NumberType & getY() {return this->get<Yposition>();}
		FINLINE NumberType & getU() {return this->get<Uposition>();}
		FINLINE NumberType & getV() {return this->get<Vposition>();}

		FINLINE const NumberType & getY() const {return this->get<Yposition>();}
		FINLINE const NumberType & getU() const {return this->get<Uposition>();}
		FINLINE const NumberType & getV() const {return this->get<Vposition>();}

};

//typedef PixelYUVbaseType<I1u,PixelRange_Y2_0i1u   ,0,1,2> PixelYUVi1utd;
//typedef PixelYUVbaseType<I4 ,PixelRange_Y2_0i4    ,0,1,2> PixelYUVi4td;
//typedef PixelYUVbaseType<I4 ,PixelRange_Y2_0i4_i1u,0,1,2> PixelYUVi4_i1utd;
typedef PixelYUVbaseType<F4 ,PixelRange_Y2_0f4  ,0,1,2> PixelYUVf4td;
typedef PixelYUVbaseType<F8 ,PixelRange_Y2_0f8  ,0,1,2> PixelYUVf8td;

class AIL_DLL_EXPORT PixelYUVf8 : public PixelYUVf8td {
	public:
		typedef F8 NumberType;
		typedef PixelYUVf8td::DataType DataType;
		typedef PixelRange_Y2_0f8 RangeType;
		typedef PixelYUVf8td ParentType;
		typedef PixelYUVf8 ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		FINLINE ThisType(const DataType & _pixel):ParentType(_pixel){}
		FINLINE ThisType(const ThisType & _pixel):ParentType(_pixel){}

		FINLINE explicit ThisType(const NumberType & _y,const NumberType & _u,const NumberType & _v){setY(_y);setU(_u);setV(_v);}
};

}

#endif
