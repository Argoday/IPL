
#ifndef FILTER__BaseBoxFilterAlgorithm_H
#define FILTER__BaseBoxFilterAlgorithm_H

#include <Algorithm/BaseOperationTempType.h>

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType,
	typename ParametersType,
	typename TempType
> class AIL_DLL_EXPORT BaseBoxFilterAlgorithm {
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
			tempData.tempPixel+= srcImageData;
		}

		static FINLINE void final(
			TempType & tempData,
			const ParametersType & parameters)
		{
			tempData.resultPixel.setComp(tempData.tempPixel/parameters.size);
		}

};

}

#endif
