
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
		static __forceinline void initial(
			TempType & tempData,
			const ParametersType & parameters)
		{
			tempData.tempPixel = parameters.minPixel;
		}

		static __forceinline void inner(
			TempType & tempData,
			const ParametersType & parameters,
			const PixelType & srcImageData,
			const PixelType & filterData)
		{
			tempData.tempPixel+=srcImageData*filterData;
		}

		static __forceinline void final(
			TempType & tempData,
			const ParametersType & parameters)
		{
			tempData.tempPixel/=parameters.totalColor;
		}

};

}

#endif
