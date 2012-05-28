
#ifndef DATA__DataRange_H
#define DATA__DataRange_H

#include <ACore.h>
#include <Meta/Boolean.h>
#include <Data/DataTypes.h>

namespace Data {

//TODO: This is designed to be used as constexpr (but compiler support hasn't caught up yet)
//      - when the compiler supports constexpr -> replace const with constexpr
template <
	typename NumberType
> class ACORE_DLL_EXPORT DataRange_Base {
	public:
		static const NumberType min;
		static const NumberType max;

		static FINLINE const NumberType & getMin() {return min;}
		static FINLINE const NumberType & getMax() {return max;}
};

template <
	typename NumberType,
	int depthID
> class ACORE_DLL_EXPORT DataRange_BaseDepth {
	public:
		static const NumberType min;
		static const NumberType max;

		static FINLINE const NumberType & getMin() {return min;}
		static FINLINE const NumberType & getMax() {return max;}
};

typedef DataRange_Base<B1 > DataRange_B1 ;
typedef DataRange_Base<I1 > DataRange_I1 ;
typedef DataRange_Base<I1u> DataRange_I1u;
typedef DataRange_Base<I2 > DataRange_I2 ;
typedef DataRange_Base<I2u> DataRange_I2u;
typedef DataRange_Base<I4 > DataRange_I4 ;
typedef DataRange_Base<I4u> DataRange_I4u;

typedef DataRange_BaseDepth<I2 ,1> DataRange_I2_I1  ;
typedef DataRange_BaseDepth<I2 ,2> DataRange_I2_I1u ;

typedef DataRange_BaseDepth<I2u,1> DataRange_I2u_I1u;

typedef DataRange_BaseDepth<I4 ,1> DataRange_I4_I1  ;
typedef DataRange_BaseDepth<I4 ,2> DataRange_I4_I1u ;
typedef DataRange_BaseDepth<I4 ,3> DataRange_I4_I2  ;
typedef DataRange_BaseDepth<I4 ,4> DataRange_I4_I2u ;

typedef DataRange_BaseDepth<I4u,1> DataRange_I4u_I1u;
typedef DataRange_BaseDepth<I4u,2> DataRange_I4u_I2u;

typedef DataRange_BaseDepth<F4 ,1> DataRange_F4_1;
typedef DataRange_BaseDepth<F8 ,1> DataRange_F8_1;

}

#endif
