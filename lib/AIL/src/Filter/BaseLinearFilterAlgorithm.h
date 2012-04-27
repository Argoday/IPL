
#ifndef FILTER__BaseLinearFilterAlgorithm_H
#define FILTER__BaseLinearFilterAlgorithm_H

#include <Algorithm/BaseOperationTempType.h>
#include "BaseLinearFilterParametersType.h"

namespace Filter {

template <
	typename PixelType,
	typename ParametersType,
	typename TempType
> class BaseLinearFilterAlgorithm {
	public:
		static FINLINE void initial(
			TempType & tempData,
			const ParametersType & parameters)
		{
			tempData.tempPixel = parameters.minPixel;
		}

		static FINLINE void inner(
			TempType & tempData,
			const ParametersType & parameters,
			const PixelType & srcImageData,
			const PixelType & filterData)
		{
			tempData.tempPixel+=srcImageData*filterData;
		}

		static FINLINE void final(
			TempType & tempData,
			const ParametersType & parameters)
		{
			tempData.tempPixel/=parameters.totalColor;
		}

};

}

#endif
