
#ifndef IMAGE__PixelRange_i8x3_H
#define IMAGE__PixelRange_i8x3_H

#include "PixelDataType1.h"
#include "PixelDataType3.h"
#include "PixelDataTypeY2.h"

namespace Pixel {

template <
	typename PixeDataType,
	int depthID
> class PixelRange_Base {
	public:
		static const PixeDataType minPixel;
		static const PixeDataType maxPixel;

		static __forceinline const PixeDataType &getMinPixel() {return minPixel;}
		static __forceinline const PixeDataType &getMaxPixel() {return maxPixel;}

		static __forceinline void clip(PixeDataType &pixel);

};

template <> static __forceinline void PixelRange_Base<PixelDataType1b,1>::clip(PixelDataType1b &pixel){
};

template <> static __forceinline void PixelRange_Base<PixelDataType3i1u,1>::clip(PixelDataType3i1u &pixel){
};

template <> static __forceinline void PixelRange_Base<PixelDataType3i4,1>::clip(PixelDataType3i4 &pixel){
	if(pixel.get<0>()<0){pixel.set<0>(0);}else if(pixel.get<0>()>255){pixel.set<0>(255);}
	if(pixel.get<1>()<0){pixel.set<1>(0);}else if(pixel.get<1>()>255){pixel.set<1>(255);}
	if(pixel.get<2>()<0){pixel.set<2>(0);}else if(pixel.get<2>()>255){pixel.set<2>(255);}
};

template <> static __forceinline void PixelRange_Base<PixelDataType3i4,2>::clip(PixelDataType3i4 &pixel){
	if(pixel.get<0>()<0){pixel.set<0>(0);}else if(pixel.get<0>()>65535){pixel.set<0>(65535);}
	if(pixel.get<1>()<0){pixel.set<1>(0);}else if(pixel.get<1>()>65535){pixel.set<1>(65535);}
	if(pixel.get<2>()<0){pixel.set<2>(0);}else if(pixel.get<2>()>65535){pixel.set<2>(65535);}
};

template <> static __forceinline void PixelRange_Base<PixelDataType3f4,1>::clip(PixelDataType3f4 &pixel){
	if(pixel.get<0>()<0.0f){pixel.set<0>(0.0f);}else if(pixel.get<0>()>1.0f){pixel.set<0>(1.0f);}
	if(pixel.get<1>()<0.0f){pixel.set<1>(0.0f);}else if(pixel.get<1>()>1.0f){pixel.set<1>(1.0f);}
	if(pixel.get<2>()<0.0f){pixel.set<2>(0.0f);}else if(pixel.get<2>()>1.0f){pixel.set<2>(1.0f);}
};

template <> static __forceinline void PixelRange_Base<PixelDataType3f8,1>::clip(PixelDataType3f8 &pixel){
	if(pixel.get<0>()<0.0){pixel.set<0>(0.0);}else if(pixel.get<0>()>1.0){pixel.set<0>(1.0);}
	if(pixel.get<1>()<0.0){pixel.set<1>(0.0);}else if(pixel.get<1>()>1.0){pixel.set<1>(1.0);}
	if(pixel.get<2>()<0.0){pixel.set<2>(0.0);}else if(pixel.get<2>()>1.0){pixel.set<2>(1.0);}
};

template <> static __forceinline void PixelRange_Base<PixelDataTypeY2_0f8,1>::clip(PixelDataTypeY2_0f8 &pixel){
	if(pixel.get<0>()<0.0){pixel.set<0>(0.0);pixel.set<1>(0.0);pixel.set<2>(0.0);return;}else if(pixel.get<0>()>1.0){pixel.set<0>(1.0);return;}
	if(pixel.get<1>()<0.0){pixel.set<1>(0.0);}else if(pixel.get<1>()>1.0){pixel.set<1>(1.0);}
	if(pixel.get<2>()<0.0){pixel.set<2>(0.0);}else if(pixel.get<2>()>1.0){pixel.set<2>(1.0);}
};

typedef PixelRange_Base<PixelDataType1b  ,1> PixelRange_1b;
typedef PixelRange_Base<PixelDataType3i1u,1> PixelRange_3i1u;
typedef PixelRange_Base<PixelDataType3i4 ,1> PixelRange_3i4_1;
typedef PixelRange_Base<PixelDataType3i4 ,2> PixelRange_3i4_2;
typedef PixelRange_Base<PixelDataType3f4 ,1> PixelRange_3f4;
typedef PixelRange_Base<PixelDataType3f8 ,1> PixelRange_3f8;
typedef PixelRange_Base<PixelDataTypeY2_0f8 ,1> PixelRange_Y2_0f8;

}

#endif
