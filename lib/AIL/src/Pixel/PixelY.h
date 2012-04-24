
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
	typename PixelRangeType
> class PixelYbaseType
	: public PixelDataType1<NumberType>
{
	public:

		typedef typename NumberType NumberType;
		typedef typename PixelRangeType RangeType;
		typedef PixelDataType1<NumberType> DataType;
		typedef PixelDataType1<NumberType> ParentType;
		typedef PixelYbaseType<NumberType,PixelRangeType> ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		__forceinline ThisType(const DataType & _pixel):ParentType(_pixel){}
		__forceinline ThisType(const ThisType & _pixel):ParentType(_pixel){}
		
		__forceinline void setY(const NumberType & _y) {this->set<0>(_y);}

		__forceinline const NumberType & getY() const {return this->get<0>();}

};

typedef PixelYbaseType<Meta::Boolean,PixelRange_1b1 > PixelYb1td;
typedef PixelYbaseType<I1u          ,PixelRange_1i1u> PixelYi1utd;

class AIL_DLL_EXPORT PixelYb1 : public PixelYb1td {
	public:
		typedef Meta::Boolean NumberType;
		typedef PixelYb1td::DataType DataType;
		typedef PixelRange_1b1 RangeType;
		typedef PixelYb1td ParentType;
		typedef PixelYb1 ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		__forceinline ThisType(const DataType & _pixel):ParentType(_pixel){}
		__forceinline ThisType(const ThisType & _pixel):ParentType(_pixel){}
};

//TODO: Move this to a seperate 'TestType' file ?
class BooleanTestType {
	public:
		static __forceinline Meta::Boolean isIncluded(const Pixel::PixelYb1 &boolToTest){
			return boolToTest.getY();
		}
};

class AIL_DLL_EXPORT PixelYi1u : public PixelYi1utd {
	public:
		typedef I1u NumberType;
		typedef PixelYi1utd::DataType DataType;
		typedef PixelRange_1i1u RangeType;
		typedef PixelYi1utd ParentType;
		typedef PixelYi1u ThisType;

		__forceinline explicit ThisType(){}
		__forceinline explicit ThisType(const NumberType & _scalar):ParentType(_scalar){}
		__forceinline ThisType(const DataType & _pixel):ParentType(_pixel){}
		__forceinline ThisType(const ThisType & _pixel):ParentType(_pixel){}
};

}


#endif
