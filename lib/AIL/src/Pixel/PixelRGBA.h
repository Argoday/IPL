
#ifndef PIXEL__Pixel_RGBA_H
#define PIXEL__Pixel_RGBA_H

#include <AIL.h>
#include <Meta/TypeVector.h>
#include <Pixel/PixelTypeID.h>
#include <Pixel/PixelDataType3A.h>
#include <Pixel/PixelRange.h>
#include <Data/DataTypes.h>

namespace Pixel {

template <
	typename NumberType,
	typename ComputationDataType,
	typename PixelRangeType,
	int Rposition,
	int Gposition,
	int Bposition,
	int Aposition
> class AIL_DLL_EXPORT PixelRGBAbaseType
	: public PixelDataType3A<NumberType,Rposition,Gposition,Bposition,Aposition>
{
	public:

		typedef typename NumberType                                             NumberType;
		typedef typename PixelRangeType                                         RangeType;
		typedef PixelDataType3A<NumberType,PixelDataType3<NumberType>>          DataType;
		typedef PixelDataType3A<NumberType,PixelDataType3<ComputationDataType>> ComputationType;
		typedef PixelDataType3A<NumberType,PixelDataType3<NumberType>>          ParentType;
		typedef PixelRGBAbaseType<NumberType,ComputationDataType,PixelRangeType,Rposition,Gposition,Bposition> ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

		FINLINE explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b){setR(_r);setG(_g);setB(_b);setA(RangeType::max}
		
		FINLINE void setR(const NumberType & _r) {this->set<Rposition>(_r);}
		FINLINE void setG(const NumberType & _g) {this->set<Gposition>(_g);}
		FINLINE void setB(const NumberType & _b) {this->set<Bposition>(_b);}
		FINLINE void setA(const NumberType & _a) {this->set<Aposition>(_a);}

		FINLINE void clip(){RangeType::clip(*static_cast<ParentType*>(this));}

		FINLINE const NumberType & getR() const {return this->get<Rposition>();}
		FINLINE const NumberType & getG() const {return this->get<Gposition>();}
		FINLINE const NumberType & getB() const {return this->get<Bposition>();}
		FINLINE const NumberType & getA() const {return this->get<Aposition>();}

};

typedef PixelRGBAbaseType<I1u,I4,PixelRange_3i1u   ,0,1,2> PixelRGBi1utd;
typedef PixelRGBAbaseType<I4 ,I4,PixelRange_3i4_i1u,0,1,2> PixelRGBi4_i1utd;
typedef PixelRGBAbaseType<I4 ,I4,PixelRange_3i4_i2u,0,1,2> PixelRGBi4_i2utd;
typedef PixelRGBAbaseType<F8 ,F8,PixelRange_3Af8   ,0,1,2,3> PixelRGBAf8td;

class AIL_DLL_EXPORT PixelRGBAf8 : public PixelRGBAf8td {
	public:
		typedef F8                             NumberType;
		typedef PixelRGBAf8td::DataType        DataType;
		typedef PixelRGBAf8td::ComputationType ComputationType;
		typedef PixelRange_4f8                 ComputationRange;
		typedef PixelRGBAf8td                  ParentType;
		typedef PixelRGBAf8                    ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

		FINLINE explicit ThisType(const NumberType & _r,const NumberType & _g,const NumberType & _b){setR(_r);setG(_g);setB(_b);}
};

}

#endif
