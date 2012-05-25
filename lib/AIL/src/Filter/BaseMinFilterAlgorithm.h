
#ifndef FILTER__BaseMinFilterAlgorithm_H
#define FILTER__BaseMinFilterAlgorithm_H

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType,
	typename ParametersType,
	typename TempType
> class AIL_DLL_EXPORT BaseMinFilterAlgorithm {
	public:
		static FINLINE void initial(
			TempType & tempData,
			const ParametersType & parameters)
		{
		}

		static FINLINE void first(
			TempType & tempData,
			const ParametersType & parameters,
			const PixelComputationType & srcImageData)
		{
			tempData.tempPixel = srcImageData;
		}

		static FINLINE void inner(
			TempType & tempData,
			const ParametersType & parameters,
			const PixelComputationType & srcImageData)
		{
			tempData.tempPixel.setAsMin(srcImageData);
		}

		static FINLINE void final(
			TempType & tempData,
			const ParametersType & parameters)
		{
			tempData.resultPixel.setComp(tempData.tempPixel);
		}

};

}

#endif
