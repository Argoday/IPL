
#ifndef FILTER__MaxFilter1xHbasicParametersType_H
#define FILTER__MaxFilter1xHbasicParametersType_H

#include <Algorithm/Basic1xHbaseAlgorithmParametersType.h>

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType
> class MaxFilter1xHbasicParametersType
	: public Algorithm::Basic1xHbaseAlgorithmParametersType
{
	public:

		MaxFilter1xHbasicParametersType(
			const I4 & _yOffset,
			const I4 & _height,
			const I4 & _srcImageWidth,
			const PixelComputationType & _minPixel
		)
			:Basic1xHbaseAlgorithmParametersType(
				_yOffset,
				_height,
				_srcImageWidth
			)
			,minPixel(_minPixel)
		{
		}

		const PixelComputationType minPixel;
};

}

#endif
