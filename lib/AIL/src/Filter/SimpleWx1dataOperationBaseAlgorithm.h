
#ifndef FILTER__SimpleWx1dataOperationBaseAlgorithm_H
#define FILTER__SimpleWx1dataOperationBaseAlgorithm_H

#include "AIL.h"

namespace Filter {

template <
	typename DerivedAlgorithmType,
	typename PixelDataType,
	typename PixelComputationType,
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
			I4 xf=x-parameters.xOffset;
			DerivedAlgorithmType::first(tempData,parameters,srcImage.getPixel(xf,y).getAsComp<PixelComputationType::NumberType>(),(*filterDataPtr).getAsComp<PixelComputationType::NumberType>());
			++filterDataPtr;++xf;
			for(;xf<x+(parameters.filterWidth-parameters.xOffset); ++xf){
				DerivedAlgorithmType::inner(tempData,parameters,srcImage.getPixel(xf,y).getAsComp<PixelComputationType::NumberType>(),(*filterDataPtr).getAsComp<PixelComputationType::NumberType>());
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
			auto srcImageDataPtr = srcImageDataPtrIn;
			auto filterDataPtr   = parameters.filterDataPtr;
			DerivedAlgorithmType::first(tempData,parameters,(*srcImageDataPtr).getAsComp<PixelComputationType::NumberType>(),(*filterDataPtr).getAsComp<PixelComputationType::NumberType>());
			++filterDataPtr;
			++srcImageDataPtr;
			for(;filterDataPtr!=parameters.filterDataPtrEnd;){
				DerivedAlgorithmType::inner(tempData,parameters,(*srcImageDataPtr).getAsComp<PixelComputationType::NumberType>(),(*filterDataPtr).getAsComp<PixelComputationType::NumberType>());
				++filterDataPtr;
				++srcImageDataPtr;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.resultPixel;
		}
};

}

#endif
