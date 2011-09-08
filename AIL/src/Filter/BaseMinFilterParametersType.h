
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
			const Image::ImageKernel<Pixel::PixelGRAYb,Image::BooleanTestType> &_kernel,
			const long &_xOffset,
			const long &_yOffset,
			const long &_srcImageWidth,
			const PixelType &_maxPixel)
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
