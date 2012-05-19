
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

		FINLINE explicit PixelYbaseType(){}
		FINLINE explicit PixelYbaseType(const NumberType & _scalar):ParentType(_scalar){}
		FINLINE          PixelYbaseType(const DataType   & _pixel ):ParentType(_pixel ){}
		FINLINE          PixelYbaseType(const ThisType   & _pixel ):ParentType(_pixel ){}

		FINLINE void setY(const NumberType & _y) {this->set<0>(_y);}

		FINLINE const NumberType & getY() const {return this->get<0>();}

};

typedef PixelYbaseType<B1 ,I4,PixelRange_1b1 > PixelYb1td;
typedef PixelYbaseType<I1u,I4,PixelRange_1i1u> PixelYi1utd;
typedef PixelYbaseType<I4 ,I4,PixelRange_1i4 > PixelYi4td;

class AIL_DLL_EXPORT PixelYi4 : public PixelYi4td {
	public:
		typedef I4                          NumberType;
		typedef PixelYi4td::DataType        DataType;
		typedef PixelYi4td::ComputationType ComputationType;
		typedef PixelYi4td                  ComputationPixel;
		typedef PixelRange_1i4_i1u          ComputationRange;
		typedef PixelRange_1i4_i1u          RangeType;
		typedef PixelYi4td                  ParentType;
		typedef PixelYi4                    ThisType;

		FINLINE explicit PixelYi4(){}
		FINLINE explicit PixelYi4(const NumberType & _scalar):ParentType(_scalar){}
		FINLINE          PixelYi4(const DataType   & _pixel ):ParentType(_pixel ){}
		FINLINE          PixelYi4(const ThisType   & _pixel ):ParentType(_pixel ){}

};

class AIL_DLL_EXPORT PixelYb1 : public PixelYb1td {
	public:
		typedef B1                          NumberType;
		typedef PixelYb1td::DataType        DataType;
		typedef PixelYb1td::ComputationType ComputationType;
		typedef PixelYi4                    ComputationPixel;
		typedef PixelRange_1i4_i1u          ComputationRange;
		typedef PixelRange_1b1              RangeType;
		typedef PixelYb1td                  ParentType;
		typedef PixelYb1                    ThisType;

		FINLINE explicit PixelYb1(){}
		FINLINE explicit PixelYb1(const NumberType & _scalar):ParentType(_scalar){}
		FINLINE          PixelYb1(const DataType   & _pixel ):ParentType(_pixel ){}
		FINLINE          PixelYb1(const ThisType   & _pixel ):ParentType(_pixel ){}

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
		typedef PixelYi4                     ComputationPixel;
		typedef PixelRange_1i4_i1u           ComputationRange;
		typedef PixelRange_1i1u              RangeType;
		typedef PixelYi1utd                  ParentType;
		typedef PixelYi1u                    ThisType;

		FINLINE explicit PixelYi1u(){}
		FINLINE explicit PixelYi1u(const NumberType & _scalar):ParentType(_scalar){}
		FINLINE          PixelYi1u(const DataType   & _pixel ):ParentType(_pixel ){}
		FINLINE          PixelYi1u(const ThisType   & _pixel ):ParentType(_pixel ){}

};

}


#endif
