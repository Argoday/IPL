
#ifndef FILTER__Simple1xHdataOperationBaseAlgorithm_H
#define FILTER__Simple1xHdataOperationBaseAlgorithm_H

#include "AIL.h"

namespace Filter {

template <
	typename DerivedAlgorithmType,
	typename PixelDataType,
	typename ParametersType,
	typename TempType
> class Simple1xHdataOperationBaseAlgorithm {
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
			for (I4 yf=y-parameters.yOffset; yf<y-parameters.yOffset+parameters.filterHeight; ++yf){
				DerivedAlgorithmType::inner(tempData,parameters,srcImage.getPixel(x,yf),(*filterDataPtr));
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
				srcImageDataPtr+=parameters.srcImageWidth;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.tempPixel;
		}
};

}

#endif
