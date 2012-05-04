
#ifndef FILTER__SimpleWxHdataOperationBaseAlgorithm_H
#define FILTER__SimpleWxHdataOperationBaseAlgorithm_H

#include "AIL.h"

namespace Filter {

template <
	typename DerivedAlgorithmType,
	typename PixelDataType,
	typename PixelComputationType,
	typename ParametersType,
	typename TempType
> class SimpleWxHdataOperationBaseAlgorithm {
	public:
		static FINLINE void process(
			PixelDataType * const & dstImageDataPtr,
			const Image::ImageView<PixelDataType> & srcImage,
			const ParametersType & parameters,
			const I4 & x,
			const I4 & y)
		{
			TempType tempData;
			DerivedAlgorithmType::initial(tempData,parameters);
			auto filterDataPtr = parameters.filterDataPtr;
			for (I4 yf=y-parameters.yOffset; yf<y+(parameters.filterHeight-parameters.yOffset); ++yf){
				for (I4 xf=x-parameters.xOffset; xf<x+(parameters.filterWidth-parameters.xOffset); ++xf){
					DerivedAlgorithmType::inner(tempData,parameters,srcImage.getPixel(xf,yf).getAsComp<PixelComputationType::NumberType>(),(*filterDataPtr).getAsComp<PixelComputationType::NumberType>());
					++filterDataPtr;
				}
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.resultPixel;
		}
		static FINLINE void process(
			PixelDataType * const & dstImageDataPtr,
			const PixelDataType * const & srcImageDataPtrIn,
			const ParametersType & parameters)
		{
			TempType tempData;
			DerivedAlgorithmType::initial(tempData,parameters);
			auto srcImageDataPtr     = srcImageDataPtrIn;
			auto filterDataPtr       = parameters.filterDataPtr;
			auto filterDataPtrRowEnd = parameters.filterDataPtr+parameters.filterWidth; //TODO: store this information in the parameters and just use a lookup?
			for (;filterDataPtr!=parameters.filterDataPtrEnd;){
				for (;filterDataPtr!=filterDataPtrRowEnd;){
					DerivedAlgorithmType::inner(tempData,parameters,(*srcImageDataPtr).getAsComp<PixelComputationType::NumberType>(),(*filterDataPtr).getAsComp<PixelComputationType::NumberType>());
					++filterDataPtr;
					++srcImageDataPtr;
				}
				filterDataPtrRowEnd+=parameters.filterWidth;
				srcImageDataPtr+=parameters.srcImageWidth_filterWidth;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.resultPixel;
		}

};

}

#endif
