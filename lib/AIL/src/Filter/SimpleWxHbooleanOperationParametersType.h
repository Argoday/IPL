
#ifndef FILTER__SimpleWxHbooleanOperationParametersType_H
#define FILTER__SimpleWxHbooleanOperationParametersType_H

#include <Algorithm/BaseAlgorithmWxHparametersType.h>
#include "SimpleWxHbooleanOperation.h"
#include <Meta/Boolean.h>

namespace Filter {

class SimpleWxHbooleanOperationParametersType
	: public Image::BaseAlgorithmWxHparametersType
{
	public:

		SimpleWxHbooleanOperationParametersType(
			const Image::ImageKernel<Pixel::PixelYb,Pixel::BooleanTestType> & _kernel,
			const I4 & _xOffset,
			const I4 & _yOffset,
			const I4 & _srcImageWidth)
			:BaseAlgorithmWxHparametersType(
				_xOffset,
				_kernel.getKernel().getWidth()  - _xOffset - 1,
				_yOffset,
				_kernel.getKernel().getHeight() - _yOffset - 1)
			,srcImageWidth(_srcImageWidth)

			,filterDataPtr       (_kernel.getKernel().getDataView().getDataPtr())

			,filterSkipDataPtr   (_kernel.getKernelSkipDataPtr())
			,filterSkipDataPtrEnd(_kernel.getKernelSkipDataPtrEnd())

			,xOffset(_xOffset)
			,yOffset(_yOffset)

			,filterWidth (_kernel.getKernel().getWidth())
			,filterHeight(_kernel.getKernel().getHeight())

			,srcImageWidth_filterWidth(_srcImageWidth - _kernel.getKernel().getWidth())
		{

		}

		const I4 srcImageWidth;

		const Pixel::PixelYb::DataType * const filterDataPtr;

		const I4 * const filterSkipDataPtr;
		const I4 * const filterSkipDataPtrEnd;

		const I4 srcImageWidth_filterWidth;

		const I4 xOffset;
		const I4 yOffset;

		const I4 filterHeight;
		const I4 filterWidth;
};

}

#endif
