
#ifndef IMAGE__BasicWx1baseAlgorithm_H
#define IMAGE__BasicWx1baseAlgorithm_H

namespace Algorithm {

template <
	typename DerivedAlgorithmType,
	typename PixelDataType,
	typename ParametersType,
	typename TempType
> class BasicWx1baseAlgorithm {
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
			for (long xf=x-parameters.xOffset; xf<=x+parameters.borderXRight; ++xf){
				DerivedAlgorithmType::inner(tempData,parameters,srcImage.getPixel(xf,y));
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
			const PixelDataType * const srcImageDataPtrEnd=srcImageDataPtrIn+parameters.filterWidth;
			for (;srcImageDataPtr!=srcImageDataPtrEnd;){//TODO: loop unroll
				DerivedAlgorithmType::inner(tempData,parameters,(*srcImageDataPtr));
				++srcImageDataPtr;
			}
			DerivedAlgorithmType::final(tempData,parameters);
			(*dstImageDataPtr)=tempData.tempPixel;
		}
};

}

#endif
