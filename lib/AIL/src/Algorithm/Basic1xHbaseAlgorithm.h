
#ifndef IMAGE__Basic1xHbaseAlgorithm_H
#define IMAGE__Basic1xHbaseAlgorithm_H

#include "AIL.h"

namespace Algorithm {

template <
	typename DerivedAlgorithmType,
	typename PixelDataType,
	typename ParametersType,
	typename TempType
> class Basic1xHbaseAlgorithm {
	public:
		static __forceinline void process(
			PixelDataType * const & dstImageDataPtr,
			const Image::ImageView<PixelDataType> & srcImage,
			const ParametersType & parameters,
			const I4 & x,
			const I4 & y)
		{
			TempType tempData;
			DerivedAlgorithmType::initial(tempData,parameters);
			for (I4 yf=y-parameters.yOffset; yf<=y+parameters.borderYTop; ++yf){
				DerivedAlgorithmType::inner(tempData,parameters,srcImage.getPixel(x,yf));
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.tempPixel;
		}
		static __forceinline void process(
			PixelDataType * const & dstImageDataPtr,
			const PixelDataType * const & srcImageDataPtrIn,
			const ParametersType & parameters)
		{
			TempType tempData;
			DerivedAlgorithmType::initial(tempData,parameters);
			const PixelDataType *srcImageDataPtr=srcImageDataPtrIn;
			const PixelDataType * const srcImageDataPtrEnd=srcImageDataPtrIn+parameters.srcImageWidth_x_filterHeight;
			for (;srcImageDataPtr!=srcImageDataPtrEnd;){//TODO: loop unroll
				DerivedAlgorithmType::inner(tempData,parameters,(*srcImageDataPtr));
				srcImageDataPtr+=parameters.srcImageWidth;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.tempPixel;
		}
};

}

#endif
