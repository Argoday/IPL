
#ifndef FILTER__SimpleWx1booleanOperationBaseAlgorithm_H
#define FILTER__SimpleWx1booleanOperationBaseAlgorithm_H

#include "AIL.h"

namespace Filter {

template <
	typename DerivedAlgorithmType,
	typename PixelDataType,
	typename ParametersType,
	typename TempType
> class SimpleWx1booleanOperationBaseAlgorithm {
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
			const Pixel::PixelYb::DataType * filterDataPtr = parameters.filterDataPtr;
			for (I4 xf=x-parameters.xOffset; xf<x-parameters.xOffset+parameters.filterWidth; ++xf){
				if(Pixel::BooleanTestType::isIncluded((*filterDataPtr))==true){
					DerivedAlgorithmType::inner(tempData,parameters,srcImage.getPixel(xf,y));
				}
				++filterDataPtr;
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
			auto srcImageDataPtr   = srcImageDataPtrIn;
			auto filterSkipDataPtr = parameters.filterSkipDataPtr;

			srcImageDataPtr+=(*filterSkipDataPtr);
			++filterSkipDataPtr;
			for (;filterSkipDataPtr!=parameters.filterSkipDataPtrEnd;){
				DerivedAlgorithmType::inner(tempData,parameters,(*srcImageDataPtr));
				srcImageDataPtr+=(*filterSkipDataPtr);
				++filterSkipDataPtr;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.tempPixel;
		}
};

}

#endif
