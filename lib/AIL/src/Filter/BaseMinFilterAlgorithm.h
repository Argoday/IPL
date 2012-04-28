
#ifndef FILTER__BaseMinFilterAlgorithm_H
#define FILTER__BaseMinFilterAlgorithm_H

#include <Algorithm/BaseOperationTempType.h>
#include "BaseMinFilterParametersType.h"

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType,
	typename ParametersType,
	typename TempType
> class BaseMinFilterAlgorithm {
	public:
		static FINLINE void initial(
			TempType & tempData,
			const ParametersType & parameters)
		{
			tempData.tempPixel = parameters.maxPixel;
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
