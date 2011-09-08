
#ifndef FILTER__MaxFilter1xHbasicParametersType_H
#define FILTER__MaxFilter1xHbasicParametersType_H

#include <Algorithm/Basic1xHbaseAlgorithmParametersType.h>

namespace Filter {

template <
	typename PixelType
> class MaxFilter1xHbasicParametersType
	: public Algorithm::Basic1xHbaseAlgorithmParametersType
{
	public:

		MaxFilter1xHbasicParametersType(
			const long &_yOffset,
			const long &_height,
			const long &_srcImageWidth,
			const PixelType & _minPixel
		)
			:Basic1xHbaseAlgorithmParametersType(
				_yOffset,
				_height,
				_srcImageWidth
			)
			,minPixel(_minPixel)
		{
		}

		const PixelType minPixel;
};

}

#endif
