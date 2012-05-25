
#ifndef FILTER__BaseLinearFilterAlgorithm_H
#define FILTER__BaseLinearFilterAlgorithm_H

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType,
	typename ParametersType,
	typename TempType
> class BaseLinearFilterAlgorithm {
	public:
		static FINLINE void initial(
			TempType & tempData,
			const ParametersType & parameters)
		{
		}

		static FINLINE void first(
			TempType & tempData,
			const ParametersType & parameters,
			const PixelComputationType & srcImageData,
			const PixelComputationType & filterData)
		{
			tempData.tempPixel =srcImageData*filterData;
		}

		static FINLINE void inner(
			TempType & tempData,
			const ParametersType & parameters,
			const PixelComputationType & srcImageData,
			const PixelComputationType & filterData)
		{
			tempData.tempPixel+=srcImageData*filterData;
		}

		static FINLINE void final(
			TempType & tempData,
			const ParametersType & parameters)
		{
			tempData.tempPixel/=parameters.totalColor;
			tempData.resultPixel.setComp(tempData.tempPixel);
		}

};

}

#endif
