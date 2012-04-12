
#ifndef FILTER__MinFilterWx1basicParametersType_H
#define FILTER__MinFilterWx1basicParametersType_H

#include <Algorithm/BasicWx1baseAlgorithmParametersType.h>

namespace Filter {

template <
	typename PixelType
> class MinFilterWx1basicParametersType
	: public Algorithm::BasicWx1baseAlgorithmParametersType
{
	public:

		MinFilterWx1basicParametersType(
			const long &_xOffset,
			const long &_filterWidth,
			const PixelType & _maxPixel
		)
			:BasicWx1baseAlgorithmParametersType(
				_xOffset,
				_filterWidth
			)
			,maxPixel(_maxPixel)
		{
		}

		const PixelType maxPixel;
};

}

#endif
