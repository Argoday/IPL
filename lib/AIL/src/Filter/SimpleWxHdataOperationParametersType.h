
#ifndef FILTER__SimpleWxHdataOperationParametersType_H
#define FILTER__SimpleWxHdataOperationParametersType_H

#include "SimpleWxHdataOperation.h"
#include <Algorithm/BaseAlgorithmWxHparametersType.h>

namespace Filter {

template <
	typename PixelType
> class SimpleWxHdataOperationParametersType
	: public Image::BaseAlgorithmWxHparametersType
{
	public:

		SimpleWxHdataOperationParametersType(
			const Image::ImageView<PixelType> & _filter,
			const I4 & _xOffset,
			const I4 & _yOffset,
			const I4 & _srcImageWidth
		)
			:BaseAlgorithmWxHparametersType(
				_xOffset,
				_filter.getWidth()  - _xOffset -1,
				_yOffset,
				_filter.getHeight() - _yOffset -1)

			,srcImageWidth(_srcImageWidth)

			,filterDataPtr   (_filter.getDataPtr())
			,filterDataPtrEnd(_filter.getDataPtrEnd())

			,xOffset(_xOffset)
			,yOffset(_yOffset)

			,filterWidth (_filter.getWidth())
			,filterHeight(_filter.getHeight())

			,srcImageWidth_filterWidth(_srcImageWidth - _filter.getWidth())
		{

		}

		const I4 srcImageWidth;

		const PixelType * const filterDataPtr;
		const PixelType * const filterDataPtrEnd;

		const I4 srcImageWidth_filterWidth;

		const I4 xOffset;
		const I4 yOffset;

		const I4 filterHeight;
		const I4 filterWidth;

};

}

#endif
