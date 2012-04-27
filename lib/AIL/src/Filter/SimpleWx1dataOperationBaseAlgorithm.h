
#ifndef FILTER__SimpleWx1dataOperationBaseAlgorithm_H
#define FILTER__SimpleWx1dataOperationBaseAlgorithm_H

#include "AIL.h"

namespace Filter {

template <
	typename DerivedAlgorithmType,
	typename PixelDataType,
	typename ParametersType,
	typename TempType
> class SimpleWx1dataOperationBaseAlgorithm {
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
			for (I4 xf=x-parameters.xOffset; xf<x-parameters.xOffset+parameters.filterWidth; ++xf){
				DerivedAlgorithmType::inner(tempData,parameters,srcImage.getPixel(xf,y),(*filterDataPtr));
				++filterDataPtr;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.tempPixel;
		}
		static FINLINE void process(
			PixelDataType * const & dstImageDataPtr,
			const PixelDataType * const & srcImageDataPtrIn,
			const ParametersType & parameters)
		{
			TempType tempData;
			DerivedAlgorithmType::initial(tempData,parameters);
			auto srcImageDataPtr = srcImageDataPtrIn;
			auto filterDataPtr   = parameters.filterDataPtr;
			for (;filterDataPtr!=parameters.filterDataPtrEnd;){
				DerivedAlgorithmType::inner(tempData,parameters,(*srcImageDataPtr),(*filterDataPtr));
				++filterDataPtr;
				++srcImageDataPtr;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.tempPixel;
		}
};

}

#endif
