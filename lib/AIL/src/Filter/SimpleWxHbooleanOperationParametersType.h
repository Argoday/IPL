
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
			const Image::ImageKernel<Pixel::PixelGRAYb,Pixel::BooleanTestType> &_kernel,
			const long &_xOffset,
			const long &_yOffset,
			const long &_srcImageWidth)
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

		const long srcImageWidth;

		const Pixel::PixelGRAYb::DataType * const filterDataPtr;

		const long * const filterSkipDataPtr;
		const long * const filterSkipDataPtrEnd;

		const long srcImageWidth_filterWidth;

		const long xOffset;
		const long yOffset;

		const long filterHeight;
		const long filterWidth;
};

}

#endif
