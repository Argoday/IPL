
#ifndef FILTER__MaxFilterWx1basicParametersType_H
#define FILTER__MaxFilterWx1basicParametersType_H

#include <Algorithm/BasicWx1baseAlgorithmParametersType.h>

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType
> class AIL_DLL_EXPORT MaxFilterWx1basicParametersType
	: public Algorithm::BasicWx1baseAlgorithmParametersType
{
	public:

		MaxFilterWx1basicParametersType(
			const I4 & _xOffset,
			const I4 & _filterWidth,
			const PixelComputationType & _minPixel
		)
			:BasicWx1baseAlgorithmParametersType(
				_xOffset,
				_filterWidth
			)
			,minPixel(_minPixel)
		{
		}

		const PixelComputationType minPixel;
};

}

#endif
