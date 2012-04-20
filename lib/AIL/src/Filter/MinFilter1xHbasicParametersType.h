
#ifndef FILTER__MinFilter1xHbasicParametersType_H
#define FILTER__MinFilter1xHbasicParametersType_H

#include <Algorithm/Basic1xHbaseAlgorithmParametersType.h>

namespace Filter {

template <
	typename PixelType
> class MinFilter1xHbasicParametersType
	: public Algorithm::Basic1xHbaseAlgorithmParametersType
{
	public:

		MinFilter1xHbasicParametersType(
			const I4 & _yOffset,
			const I4 & _height,
			const I4 & _srcImageWidth,
			const PixelType & _maxPixel
		)
			:Basic1xHbaseAlgorithmParametersType(
				_yOffset,
				_height,
				_srcImageWidth
			)
			,maxPixel(_maxPixel)
		{
		}

		const PixelType maxPixel;
};

}

#endif
