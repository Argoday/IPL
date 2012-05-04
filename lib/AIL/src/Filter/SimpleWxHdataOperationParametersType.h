
#ifndef FILTER__SimpleWxHdataOperationParametersType_H
#define FILTER__SimpleWxHdataOperationParametersType_H

#include "SimpleWxHdataOperation.h"
#include <Algorithm/BaseAlgorithmWxHparametersType.h>

namespace Filter {

template <
	typename PixelDataType
> class SimpleWxHdataOperationParametersType
	: public Image::BaseAlgorithmWxHparametersType
{
	public:

		SimpleWxHdataOperationParametersType(
			const Image::ImageView<PixelDataType> & _filter,
			const I4 & _xOffset,
			const I4 & _yOffset,
			const I4 & _srcImageWidth
		)
			:BaseAlgorithmWxHparametersType(
				_xOffset,
				_yOffset,
				_filter.getWidth(),
				_filter.getHeight())

			,srcImageWidth(_srcImageWidth)

			,filterDataPtr   (_filter.getDataPtr())
			,filterDataPtrEnd(_filter.getDataPtrEnd())

			,srcImageWidth_filterWidth(_srcImageWidth - _filter.getWidth())
		{
		}

		const I4 srcImageWidth;

		const PixelDataType * const filterDataPtr;
		const PixelDataType * const filterDataPtrEnd;

		const I4 srcImageWidth_filterWidth;

};

}

#endif
