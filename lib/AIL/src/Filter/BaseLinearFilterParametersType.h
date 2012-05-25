
#ifndef FILTER__BASE_LINEAR_FILTER_PARAMETERS_TYPE_H
#define FILTER__BASE_LINEAR_FILTER_PARAMETERS_TYPE_H

#include "SimpleWxHdataOperationParametersType.h"
#include "BaseLinearFilter.h"

namespace Filter {

template <
	typename PixelDataType,
	typename PixelComputationType
> class BaseLinearFilterParametersType
	: public SimpleWxHdataOperationParametersType<PixelDataType>
{
	public:

		BaseLinearFilterParametersType(
			const Image::ImageView<PixelDataType> & _filter,
			const I4 & _xOffset,
			const I4 & _yOffset,
			const I4 & _srcImageWidth,
			const PixelComputationType _totalColor
		)
			:SimpleWxHdataOperationParametersType<PixelDataType>(
				_filter,
				_xOffset,
				_yOffset,
				_srcImageWidth
			)
			,totalColor(_totalColor)
		{
		}

		const PixelComputationType totalColor;
};

}

#endif
