
#ifndef FILTER__MinFilter1xHbasicParametersType_H
#define FILTER__MinFilter1xHbasicParametersType_H

#include <Algorithm/Basic1xHbaseAlgorithmParametersType.h>

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType
> class AIL_DLL_EXPORT MinFilter1xHbasicParametersType
	: public Algorithm::Basic1xHbaseAlgorithmParametersType
{
	public:

		MinFilter1xHbasicParametersType(
			const I4 & _yOffset,
			const I4 & _height,
			const I4 & _srcImageWidth,
			const PixelComputationType & _maxPixel
		)
			:Basic1xHbaseAlgorithmParametersType(
				_yOffset,
				_height,
				_srcImageWidth
			)
			,maxPixel(_maxPixel)
		{
		}

		const PixelComputationType maxPixel;
};

}

#endif
