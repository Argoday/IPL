
#ifndef FILTER__SimpleWxHdataOperationBaseAlgorithm_H
#define FILTER__SimpleWxHdataOperationBaseAlgorithm_H

namespace Filter {

template <
	typename DerivedAlgorithmType,
	typename PixelDataType,
	typename ParametersType,
	typename TempType
> class SimpleWxHdataOperationBaseAlgorithm {
	public:
		static __forceinline void process(
			PixelDataType * const &dstImageDataPtr,
			const Image::ImageView<PixelDataType> &srcImage,
			const ParametersType &parameters,
			const long &x,
			const long &y)
		{
			TempType tempData;
			DerivedAlgorithmType::initial(tempData,parameters);
			const PixelDataType *filterDataPtr = parameters.filterDataPtr;
			for (long yf=y-parameters.yOffset; yf<y-parameters.yOffset+parameters.filterHeight; ++yf){
				for (long xf=x-parameters.xOffset; xf<x-parameters.xOffset+parameters.filterWidth; ++xf){
					DerivedAlgorithmType::inner(tempData,parameters,srcImage.getPixel(xf,yf),(*filterDataPtr));
					++filterDataPtr;
				}
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.tempPixel;
		}
		static __forceinline void process(
			PixelDataType * const &dstImageDataPtr,
			const PixelDataType * const &srcImageDataPtrIn,
			const ParametersType &parameters)
		{
			TempType tempData;
			DerivedAlgorithmType::initial(tempData,parameters);
			const PixelDataType *srcImageDataPtr=srcImageDataPtrIn;
			const PixelDataType *filterDataPtr = parameters.filterDataPtr;
			const PixelDataType *filterDataPtrRowEnd = parameters.filterDataPtr+parameters.filterWidth; //TODO: store this information in the parameters and just use a lookup?
			for (;filterDataPtr!=parameters.filterDataPtrEnd;){
				for (;filterDataPtr!=filterDataPtrRowEnd;){
					DerivedAlgorithmType::inner(tempData,parameters,(*srcImageDataPtr),(*filterDataPtr));
					++filterDataPtr;
					++srcImageDataPtr;
				}
				filterDataPtrRowEnd+=parameters.filterWidth;
				srcImageDataPtr+=parameters.srcImageWidth_filterWidth;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.tempPixel;
		}

};

}

#endif
