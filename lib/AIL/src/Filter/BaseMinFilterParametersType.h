
#ifndef FILTER__BaseMinFilterParametersType_H
#define FILTER__BaseMinFilterParametersType_H

#include "SimpleWxHbooleanOperationParametersType.h"
#include "BaseMinFilter.h"

namespace Filter {

template <
	typename PixelType
> class BaseMinFilterParametersType
	: public SimpleWxHbooleanOperationParametersType
{
	public:

		BaseMinFilterParametersType(
			const Image::ImageKernel<Pixel::PixelYb,Pixel::BooleanTestType> & _kernel,
			const I4 & _xOffset,
			const I4 & _yOffset,
			const I4 & _srcImageWidth,
			const PixelType & _maxPixel)
			:SimpleWxHbooleanOperationParametersType(
				_kernel,
				_xOffset,
				_yOffset,
				_srcImageWidth)
			,maxPixel(_maxPixel)
		{
		}

		const PixelType maxPixel;
};

}

#endif
