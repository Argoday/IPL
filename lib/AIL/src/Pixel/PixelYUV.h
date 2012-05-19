
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
	typename ComputationDataType,
	typename PixelRangeType,
	int Yposition,
	int Uposition,
	int Vposition
> class AIL_DLL_EXPORT PixelYUVbaseType
	: public PixelDataTypeY2<NumberType,Yposition>
{
	public:

		typedef typename NumberType                            NumberType;
		typedef typename PixelRangeType                        RangeType;
		typedef PixelDataTypeY2<NumberType,Yposition>          DataType;
		typedef PixelDataTypeY2<ComputationDataType,Yposition> ComputationType;
		typedef PixelDataTypeY2<NumberType,Yposition>          ParentType;
		typedef PixelYUVbaseType<NumberType,ComputationDataType,PixelRangeType,Yposition,Uposition,Vposition> ThisType;

		FINLINE explicit PixelYUVbaseType(){}
		FINLINE explicit PixelYUVbaseType(const NumberType & _scalar):ParentType(_scalar){}
		FINLINE          PixelYUVbaseType(const DataType   & _pixel ):ParentType(_pixel ){}
		FINLINE          PixelYUVbaseType(const ThisType   & _pixel ):ParentType(_pixel ){}

		FINLINE explicit PixelYUVbaseType(const NumberType & _y,const NumberType & _u,const NumberType & _v){setY(_y);setU(_u);setV(_v);}

		FINLINE void setY(const NumberType & _y) {this->set<Yposition>(_y);}
		FINLINE void setU(const NumberType & _u) {this->set<Uposition>(_u);}
		FINLINE void setV(const NumberType & _v) {this->set<Vposition>(_v);}

		FINLINE void clip(){RangeType::clip(*static_cast<ParentType*>(this));}
		
		FINLINE NumberType & getY() {return this->get<Yposition>();}
		FINLINE NumberType & getU() {return this->get<Uposition>();}
		FINLINE NumberType & getV() {return this->get<Vposition>();}

		FINLINE const NumberType & getY() const {return this->get<Yposition>();}
		FINLINE const NumberType & getU() const {return this->get<Uposition>();}
		FINLINE const NumberType & getV() const {return this->get<Vposition>();}

};

typedef PixelYUVbaseType<I1u,I4,PixelRange_Y2_0i1u   ,0,1,2> PixelYUVi1utd;
typedef PixelYUVbaseType<I4 ,I4,PixelRange_Y2_0i4    ,0,1,2> PixelYUVi4td;
typedef PixelYUVbaseType<I4 ,I4,PixelRange_Y2_0i4_i1u,0,1,2> PixelYUVi4_i1utd;
typedef PixelYUVbaseType<F4 ,F8,PixelRange_Y2_0f4    ,0,1,2> PixelYUVf4td;
typedef PixelYUVbaseType<F8 ,F8,PixelRange_Y2_0f8    ,0,1,2> PixelYUVf8td;

class AIL_DLL_EXPORT PixelYUVf8 : public PixelYUVf8td {
	public:
		typedef F8                            NumberType;
		typedef PixelYUVf8td::DataType        DataType;
		typedef PixelYUVf8td::ComputationType ComputationType;
		typedef PixelYUVf8                    ComputationPixel;
		typedef PixelRange_Y2_0f8             ComputationRange;
		typedef PixelRange_Y2_0f8             RangeType;
		typedef PixelYUVf8td                  ParentType;
		typedef PixelYUVf8                    ThisType;

		FINLINE explicit PixelYUVf8(){}
		FINLINE explicit PixelYUVf8(const NumberType & _scalar):ParentType(_scalar){}
		FINLINE          PixelYUVf8(const DataType   & _pixel ):ParentType(_pixel ){}
		FINLINE          PixelYUVf8(const ThisType   & _pixel ):ParentType(_pixel ){}

		FINLINE explicit PixelYUVf8(const NumberType & _y,const NumberType & _u,const NumberType & _v){setY(_y);setU(_u);setV(_v);}
};

}

#endif
