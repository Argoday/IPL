
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
		static FINLINE void initial(
			TempType & tempData,
			const ParametersType & parameters)
		{
			tempData.tempPixel = parameters.minPixel;
		}

		static FINLINE void inner(
			TempType & tempData,
			const ParametersType & parameters,
			const PixelType & srcImageData)
		{
			tempData.tempPixel.setAsMax(srcImageData);
		}

		static FINLINE void final(
			TempType & tempData,
			const ParametersType & parameters)
		{
		}

};

}

#endif
