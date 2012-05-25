
#ifndef FILTER__Simple1xHbooleanOperationBaseAlgorithm_H
#define FILTER__Simple1xHbooleanOperationBaseAlgorithm_H

#include "AIL.h"

namespace Filter {

template <
	typename DerivedAlgorithmType,
	typename PixelDataType,
	typename PixelComputationType,
	typename ParametersType,
	typename TempType
> class Simple1xHbooleanOperationBaseAlgorithm {
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
			I4 yf=y-parameters.yOffset;
			for(;yf<y+(parameters.filterHeight-parameters.yOffset); ++yf){
				if(Pixel::BooleanTestType::isIncluded((*filterDataPtr))==true){
					DerivedAlgorithmType::first(tempData,parameters,srcImage.getPixel(x,yf).getAsComp<PixelComputationType::NumberType>());
					++filterDataPtr;
					break;
				}
				++filterDataPtr;
			}
			for(;yf<y+(parameters.filterHeight-parameters.yOffset); ++yf){
				if(Pixel::BooleanTestType::isIncluded((*filterDataPtr))==true){
					DerivedAlgorithmType::inner(tempData,parameters,srcImage.getPixel(x,yf).getAsComp<PixelComputationType::NumberType>());
				}
				++filterDataPtr;
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
			auto srcImageDataPtr   = srcImageDataPtrIn;
			auto filterSkipDataPtr = parameters.filterSkipDataPtr;

			srcImageDataPtr+=(*filterSkipDataPtr);
			++filterSkipDataPtr;
			DerivedAlgorithmType::first(tempData,parameters,(*srcImageDataPtr).getAsComp<PixelComputationType::NumberType>());
			srcImageDataPtr+=(*filterSkipDataPtr);
			++filterSkipDataPtr;
			for(;filterSkipDataPtr!=parameters.filterSkipDataPtrEnd;){
				DerivedAlgorithmType::inner(tempData,parameters,(*srcImageDataPtr).getAsComp<PixelComputationType::NumberType>());
				srcImageDataPtr+=(*filterSkipDataPtr);
				++filterSkipDataPtr;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.resultPixel;
		}
};

}

#endif
