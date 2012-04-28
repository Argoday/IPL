
#ifndef PIXEL__PixelY_H
#define PIXEL__PixelY_H

#include <AIL.h>
#include <Meta/TypeVector.h>
#include <Meta/Boolean.h>
#include "PixelDataType1.h"
#include "PixelRange.h"

namespace Pixel {

template <
	typename NumberType,
	typename ComputationDataType,
	typename PixelRangeType
> class PixelYbaseType
	: public PixelDataType1<NumberType>
{
	public:

		typedef typename NumberType                 NumberType;
		typedef typename PixelRangeType             RangeType;
		typedef PixelDataType1<NumberType>          DataType;
		typedef PixelDataType1<ComputationDataType> ComputationType;
		typedef PixelDataType1<NumberType>          ParentType;
		typedef PixelYbaseType<NumberType,ComputationDataType,PixelRangeType> ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

		FINLINE void setY(const NumberType & _y) {this->set<0>(_y);}

		FINLINE const NumberType & getY() const {return this->get<0>();}

};

typedef PixelYbaseType<B1 ,I4,PixelRange_1b1 > PixelYb1td;
typedef PixelYbaseType<I1u,I4,PixelRange_1i1u> PixelYi1utd;

class AIL_DLL_EXPORT PixelYb1 : public PixelYb1td {
	public:
		typedef B1                          NumberType;
		typedef PixelYb1td::DataType        DataType;
		typedef PixelYb1td::ComputationType ComputationType;
		typedef PixelRange_1i4              ComputationRange;
		typedef PixelRange_1b1              RangeType;
		typedef PixelYb1td                  ParentType;
		typedef PixelYb1                    ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

};

//TODO: Move this to a seperate 'TestType' file ?
class BooleanTestType {
	public:
		static FINLINE B1 isIncluded(const Pixel::PixelYb1 & boolToTest){
			return boolToTest.getY();
		}
};

class AIL_DLL_EXPORT PixelYi1u : public PixelYi1utd {
	public:
		typedef I1u                          NumberType;
		typedef PixelYi1utd::DataType        DataType;
		typedef PixelYi1utd::ComputationType ComputationType;
		typedef PixelRange_1i4               ComputationRange;
		typedef PixelRange_1i1u              RangeType;
		typedef PixelYi1utd                  ParentType;
		typedef PixelYi1u                    ThisType;

		FINLINE explicit ThisType(){}
		FINLINE explicit ThisType(const NumberType      & _scalar):ParentType(_scalar){}
		FINLINE          ThisType(const DataType        & _pixel ):ParentType(_pixel ){}
		FINLINE          ThisType(const ThisType        & _pixel ):ParentType(_pixel ){}

};

}


#endif
