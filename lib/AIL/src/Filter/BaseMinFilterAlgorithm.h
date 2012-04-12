
#ifndef FILTER__BaseMinFilterAlgorithm_H
#define FILTER__BaseMinFilterAlgorithm_H

#include <Algorithm/BaseOperationTempType.h>
#include "BaseMinFilterParametersType.h"

namespace Filter {

template <
	typename PixelType,
	typename ParametersType,
	typename TempType
> class BaseMinFilterAlgorithm {
	public:
		static __forceinline void initial(
			TempType &tempData,
			const ParametersType &parameters)
		{
			tempData.tempPixel = parameters.maxPixel;
		}

		static __forceinline void inner(
			TempType &tempData,
			const ParametersType &parameters,
			const PixelType &srcImageData)
		{
			tempData.tempPixel.setAsMin(srcImageData);
		}

		static __forceinline void final(
			TempType &tempData,
			const ParametersType &parameters)
		{
		}

};

}

#endif
