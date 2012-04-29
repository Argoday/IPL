
#ifndef FILTER__BoxFilter1xHparametersType_H
#define FILTER__BoxFilter1xHparametersType_H

#include <Algorithm/Basic1xHbaseAlgorithmParametersType.h>

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType
> class AIL_DLL_EXPORT BoxFilter1xHparametersType
	: public Algorithm::Basic1xHbaseAlgorithmParametersType
{
	public:

		BoxFilter1xHparametersType(
			const I4 & _yOffset,
			const I4 & _height,
			const I4 & _srcImageWidth,
			const PixelComputationType & _minPixel,
			const PixelComputationType & _size
		)
			:Basic1xHbaseAlgorithmParametersType(
				_yOffset,
				_height,
				_srcImageWidth
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
