
#ifndef FILTER__BaseMaxFilterAlgorithm_H
#define FILTER__BaseMaxFilterAlgorithm_H

#include <Algorithm/BaseOperationTempType.h>
#include "BaseMaxFilterParametersType.h"

namespace Filter {

template <
	typename PixelType,
	typename ParametersType,
	typename TempType
> class BaseMaxFilterAlgorithm {
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
			const PixelType & srcImageData)
		{
			tempData.tempPixel.setAsMax(srcImageData);
		}

		static __forceinline void final(
			TempType & tempData,
			const ParametersType & parameters)
		{
		}

};

}

#endif
