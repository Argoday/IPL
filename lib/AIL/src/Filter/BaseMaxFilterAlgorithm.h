
#ifndef FILTER__BaseMaxFilterAlgorithm_H
#define FILTER__BaseMaxFilterAlgorithm_H

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType,
	typename ParametersType,
	typename TempType
> class BaseMaxFilterAlgorithm {
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
			tempData.tempPixel.setAsMax(srcImageData);
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
