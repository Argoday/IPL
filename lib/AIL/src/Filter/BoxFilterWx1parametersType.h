
#ifndef FILTER__BoxFilterWx1parametersType_H
#define FILTER__BoxFilterWx1parametersType_H

#include <Algorithm/BasicWx1baseAlgorithmParametersType.h>

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType
> class AIL_DLL_EXPORT BoxFilterWx1parametersType
	: public Algorithm::BasicWx1baseAlgorithmParametersType
{
	public:

		BoxFilterWx1parametersType(
			const I4 & _xOffset,
			const I4 & _filterWidth,
			const PixelComputationType & _minPixel,
			const PixelComputationType & _size
		)
			:BasicWx1baseAlgorithmParametersType(
				_xOffset,
				_filterWidth
			)
			,minPixel(_minPixel)
			,size(_size)
		{
		}

		const PixelComputationType minPixel;
		const PixelComputationType size;
};

}

#endif
