
#ifndef IMAGE__BasicWx1baseAlgorithm_H
#define IMAGE__BasicWx1baseAlgorithm_H

#include "AIL.h"

namespace Algorithm {

template <
	typename DerivedAlgorithmType,
	typename PixelDataType,
	typename PixelComputationType,
	typename ParametersType,
	typename TempType
> class BasicWx1baseAlgorithm {
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
			for (I4 xf=x-parameters.xOffset; xf<=x+parameters.borderXRight; ++xf){
				DerivedAlgorithmType::inner(tempData,parameters,srcImage.getPixel(xf,y).getAsComp<PixelComputationType::NumberType>());
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
			auto srcImageDataPtr    = srcImageDataPtrIn;
			auto srcImageDataPtrEnd = srcImageDataPtrIn + parameters.filterWidth;
			for (;srcImageDataPtr!=srcImageDataPtrEnd;){//TODO: loop unroll
				DerivedAlgorithmType::inner(tempData,parameters,(*srcImageDataPtr).getAsComp<PixelComputationType::NumberType>());
				++srcImageDataPtr;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.resultPixel;
		}
};

}

#endif
