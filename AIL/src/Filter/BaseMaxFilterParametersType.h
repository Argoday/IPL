
#ifndef FILTER__BaseMaxFilterParametersType_H
#define FILTER__BaseMaxFilterParametersType_H

#include "SimpleWxHbooleanOperationParametersType.h"
#include "BaseMaxFilter.h"

namespace Filter {

template <
	typename PixelType
> class BaseMaxFilterParametersType
	: public SimpleWxHbooleanOperationParametersType
{
	public:

		BaseMaxFilterParametersType(
			const Image::ImageKernel<Pixel::PixelGRAYb,Image::BooleanTestType> &_kernel,
			const long &_xOffset,
			const long &_yOffset,
			const long &_srcImageWidth,
			const PixelType &_minPixel)
			:SimpleWxHbooleanOperationParametersType(
				_kernel,
				_xOffset,
				_yOffset,
				_srcImageWidth)
			,minPixel(_minPixel)
		{
		}

		const PixelType minPixel;
};

}

#endif
