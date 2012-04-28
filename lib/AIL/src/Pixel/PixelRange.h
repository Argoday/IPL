
#ifndef IMAGE__PixelRange_i8x3_H
#define IMAGE__PixelRange_i8x3_H

#include "PixelDataType1.h"
#include "PixelDataType3.h"
#include "PixelDataTypeY2.h"

namespace Pixel {

template <
	typename PixeDataType,
	int depthID
> class AIL_DLL_EXPORT PixelRange_Base {
	public:

		static const typename PixeDataType::NumberType minValue; //TODO: Make these constexpr
		static const typename PixeDataType::NumberType maxValue;

		static const PixeDataType minPixel; //TODO: Make these constexpr
		static const PixeDataType maxPixel;

		static FINLINE const PixeDataType & getMinPixel() {return minPixel;}
		static FINLINE const PixeDataType & getMaxPixel() {return maxPixel;}

		static FINLINE void clip(PixeDataType & pixel);

};

///////////////////////////////////////////////////////////////////

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType1b1 ,1>::clip(PixelDataType1b1  & pixel){};
template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType1i1u,1>::clip(PixelDataType1i1u & pixel){};
template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType1i4 ,1>::clip(PixelDataType1i4  & pixel){};

///////////////////////////////////////////////////////////////////

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType3i1u,1>::clip(PixelDataType3i1u & pixel){};
template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType3i4 ,1>::clip(PixelDataType3i4  & pixel){};
template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType3i2 ,1>::clip(PixelDataType3i2  & pixel){};
template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType3i2u,1>::clip(PixelDataType3i2u & pixel){};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType3i2 ,2>::clip(PixelDataType3i2  & pixel){
	if(pixel.get<0>()<0){pixel.set<0>(0);}else if(pixel.get<0>()>255){pixel.set<0>(255);}
	if(pixel.get<1>()<0){pixel.set<1>(0);}else if(pixel.get<1>()>255){pixel.set<1>(255);}
	if(pixel.get<2>()<0){pixel.set<2>(0);}else if(pixel.get<2>()>255){pixel.set<2>(255);}
};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType3i2u,2>::clip(PixelDataType3i2u & pixel){
	if(pixel.get<0>()<0){pixel.set<0>(0);}else if(pixel.get<0>()>255){pixel.set<0>(255);}
	if(pixel.get<1>()<0){pixel.set<1>(0);}else if(pixel.get<1>()>255){pixel.set<1>(255);}
	if(pixel.get<2>()<0){pixel.set<2>(0);}else if(pixel.get<2>()>255){pixel.set<2>(255);}
};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType3i4,2>::clip(PixelDataType3i4 & pixel){
	if(pixel.get<0>()<0){pixel.set<0>(0);}else if(pixel.get<0>()>255){pixel.set<0>(255);}
	if(pixel.get<1>()<0){pixel.set<1>(0);}else if(pixel.get<1>()>255){pixel.set<1>(255);}
	if(pixel.get<2>()<0){pixel.set<2>(0);}else if(pixel.get<2>()>255){pixel.set<2>(255);}
};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType3i4,3>::clip(PixelDataType3i4 & pixel){
	if(pixel.get<0>()<0){pixel.set<0>(0);}else if(pixel.get<0>()>65535){pixel.set<0>(65535);}
	if(pixel.get<1>()<0){pixel.set<1>(0);}else if(pixel.get<1>()>65535){pixel.set<1>(65535);}
	if(pixel.get<2>()<0){pixel.set<2>(0);}else if(pixel.get<2>()>65535){pixel.set<2>(65535);}
};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType3f4,1>::clip(PixelDataType3f4 & pixel){
	if(pixel.get<0>()<0.0f){pixel.set<0>(0.0f);}else if(pixel.get<0>()>1.0f){pixel.set<0>(1.0f);}
	if(pixel.get<1>()<0.0f){pixel.set<1>(0.0f);}else if(pixel.get<1>()>1.0f){pixel.set<1>(1.0f);}
	if(pixel.get<2>()<0.0f){pixel.set<2>(0.0f);}else if(pixel.get<2>()>1.0f){pixel.set<2>(1.0f);}
};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataType3f8,1>::clip(PixelDataType3f8 & pixel){
	if(pixel.get<0>()<0.0){pixel.set<0>(0.0);}else if(pixel.get<0>()>1.0){pixel.set<0>(1.0);}
	if(pixel.get<1>()<0.0){pixel.set<1>(0.0);}else if(pixel.get<1>()>1.0){pixel.set<1>(1.0);}
	if(pixel.get<2>()<0.0){pixel.set<2>(0.0);}else if(pixel.get<2>()>1.0){pixel.set<2>(1.0);}
};

///////////////////////////////////////////////////////////////////

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataTypeY2_0i1u,1>::clip(PixelDataTypeY2_0i1u & pixel){};
template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataTypeY2_0i4 ,1>::clip(PixelDataTypeY2_0i4  & pixel){};
template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataTypeY2_0i2 ,1>::clip(PixelDataTypeY2_0i2  & pixel){};
template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataTypeY2_0i2u,1>::clip(PixelDataTypeY2_0i2u & pixel){};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataTypeY2_0i2 ,2>::clip(PixelDataTypeY2_0i2  & pixel){
	if(pixel.get<0>()<0){pixel.set<0>(0);}else if(pixel.get<0>()>255){pixel.set<0>(255);}
	if(pixel.get<1>()<0){pixel.set<1>(0);}else if(pixel.get<1>()>255){pixel.set<1>(255);}
	if(pixel.get<2>()<0){pixel.set<2>(0);}else if(pixel.get<2>()>255){pixel.set<2>(255);}
};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataTypeY2_0i2u,2>::clip(PixelDataTypeY2_0i2u & pixel){
	if(pixel.get<0>()<0){pixel.set<0>(0);}else if(pixel.get<0>()>255){pixel.set<0>(255);}
	if(pixel.get<1>()<0){pixel.set<1>(0);}else if(pixel.get<1>()>255){pixel.set<1>(255);}
	if(pixel.get<2>()<0){pixel.set<2>(0);}else if(pixel.get<2>()>255){pixel.set<2>(255);}
};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataTypeY2_0i4,2>::clip(PixelDataTypeY2_0i4 & pixel){
	if(pixel.get<0>()<0){pixel.set<0>(0);}else if(pixel.get<0>()>255){pixel.set<0>(255);}
	if(pixel.get<1>()<0){pixel.set<1>(0);}else if(pixel.get<1>()>255){pixel.set<1>(255);}
	if(pixel.get<2>()<0){pixel.set<2>(0);}else if(pixel.get<2>()>255){pixel.set<2>(255);}
};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataTypeY2_0i4,3>::clip(PixelDataTypeY2_0i4 & pixel){
	if(pixel.get<0>()<0){pixel.set<0>(0);}else if(pixel.get<0>()>65535){pixel.set<0>(65535);}
	if(pixel.get<1>()<0){pixel.set<1>(0);}else if(pixel.get<1>()>65535){pixel.set<1>(65535);}
	if(pixel.get<2>()<0){pixel.set<2>(0);}else if(pixel.get<2>()>65535){pixel.set<2>(65535);}
};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataTypeY2_0f4,1>::clip(PixelDataTypeY2_0f4 & pixel){
	if(pixel.get<0>()<0.0f){pixel.set<0>(0.0f);}else if(pixel.get<0>()>1.0f){pixel.set<0>(1.0f);}
	if(pixel.get<1>()<0.0f){pixel.set<1>(0.0f);}else if(pixel.get<1>()>1.0f){pixel.set<1>(1.0f);}
	if(pixel.get<2>()<0.0f){pixel.set<2>(0.0f);}else if(pixel.get<2>()>1.0f){pixel.set<2>(1.0f);}
};

template <> AIL_DLL_EXPORT static FINLINE void PixelRange_Base<PixelDataTypeY2_0f8,1>::clip(PixelDataTypeY2_0f8 & pixel){
	if(pixel.get<0>()<0.0){pixel.set<0>(0.0);}else if(pixel.get<0>()>1.0){pixel.set<0>(1.0);}
	if(pixel.get<1>()<0.0){pixel.set<1>(0.0);}else if(pixel.get<1>()>1.0){pixel.set<1>(1.0);}
	if(pixel.get<2>()<0.0){pixel.set<2>(0.0);}else if(pixel.get<2>()>1.0){pixel.set<2>(1.0);}
};

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

typedef PixelRange_Base<PixelDataType1b1 ,1> PixelRange_1b1;
typedef PixelRange_Base<PixelDataType1i1u,1> PixelRange_1i1u;
typedef PixelRange_Base<PixelDataType1i4 ,1> PixelRange_1i4;

///////////////////////////////////////////////////////////////////

typedef PixelRange_Base<PixelDataType3i1u,1> PixelRange_3i1u;

typedef PixelRange_Base<PixelDataType3i2 ,1> PixelRange_3i2;
typedef PixelRange_Base<PixelDataType3i2 ,2> PixelRange_3i2_i1u;
typedef PixelRange_Base<PixelDataType3i2u,1> PixelRange_3i2u;
typedef PixelRange_Base<PixelDataType3i2u,2> PixelRange_3i2u_i1u;

typedef PixelRange_Base<PixelDataType3i4 ,1> PixelRange_3i4;
typedef PixelRange_Base<PixelDataType3i4 ,2> PixelRange_3i4_i1u;
typedef PixelRange_Base<PixelDataType3i4 ,3> PixelRange_3i4_i2u;

typedef PixelRange_Base<PixelDataType3f4 ,1> PixelRange_3f4;
typedef PixelRange_Base<PixelDataType3f8 ,1> PixelRange_3f8;

///////////////////////////////////////////////////////////////////

typedef PixelRange_Base<PixelDataTypeY2_0i1u,1> PixelRange_Y2_0i1u;

typedef PixelRange_Base<PixelDataTypeY2_0i2 ,1> PixelRange_Y2_0i2;
typedef PixelRange_Base<PixelDataTypeY2_0i2 ,2> PixelRange_Y2_0i2_i1u;
typedef PixelRange_Base<PixelDataTypeY2_0i2u,1> PixelRange_Y2_0i2u;
typedef PixelRange_Base<PixelDataTypeY2_0i2u,2> PixelRange_Y2_0i2u_i1u;

typedef PixelRange_Base<PixelDataTypeY2_0i4 ,1> PixelRange_Y2_0i4;
typedef PixelRange_Base<PixelDataTypeY2_0i4 ,2> PixelRange_Y2_0i4_i1u;
typedef PixelRange_Base<PixelDataTypeY2_0i4 ,3> PixelRange_Y2_0i4_i2u;

typedef PixelRange_Base<PixelDataTypeY2_0f4 ,1> PixelRange_Y2_0f4;
typedef PixelRange_Base<PixelDataTypeY2_0f8 ,1> PixelRange_Y2_0f8;

///////////////////////////////////////////////////////////////////

}

#endif
