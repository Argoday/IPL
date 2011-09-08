
#ifndef FILTER__MaxFilterWx1basicParametersType_H
#define FILTER__MaxFilterWx1basicParametersType_H

#include <Algorithm/BasicWx1baseAlgorithmParametersType.h>

namespace Filter {

template <
	typename PixelType
> class MaxFilterWx1basicParametersType
	: public Algorithm::BasicWx1baseAlgorithmParametersType
{
	public:

		MaxFilterWx1basicParametersType(
			const long &_xOffset,
			const long &_filterWidth,
			const PixelType & _minPixel
		)
			:BasicWx1baseAlgorithmParametersType(
				_xOffset,
				_filterWidth
			)
			,minPixel(_minPixel)
		{
		}

		const PixelType minPixel;
};

}

#endif
