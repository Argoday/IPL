
#ifndef FILTER__BaseMaxFilterParametersType_H
#define FILTER__BaseMaxFilterParametersType_H

#include "SimpleWxHbooleanOperationParametersType.h"
#include "BaseMaxFilter.h"

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType
> class BaseMaxFilterParametersType
	: public SimpleWxHbooleanOperationParametersType
{
	public:

		BaseMaxFilterParametersType(
			const Image::ImageKernel<Pixel::PixelYb1,Pixel::BooleanTestType> & _kernel,
			const I4 & _xOffset,
			const I4 & _yOffset,
			const PixelComputationType & _minPixel)
			:SimpleWxHbooleanOperationParametersType(
				_kernel,
				_xOffset,
				_yOffset)
			,minPixel(_minPixel)
		{
		}

		const PixelComputationType minPixel;
};

}

#endif
