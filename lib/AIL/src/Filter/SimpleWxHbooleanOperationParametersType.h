
#ifndef FILTER__SimpleWxHbooleanOperationParametersType_H
#define FILTER__SimpleWxHbooleanOperationParametersType_H

#include "AIL.h"
#include "SimpleWxHbooleanOperation.h"
#include <Algorithm/BaseAlgorithmWxHparametersType.h>

namespace Filter {

class AIL_DLL_EXPORT SimpleWxHbooleanOperationParametersType
	: public Image::BaseAlgorithmWxHparametersType
{
	public:

		SimpleWxHbooleanOperationParametersType(
			const Image::ImageKernel<Pixel::PixelYb1,Pixel::BooleanTestType> & _kernel,
			const I4 & _xOffset,
			const I4 & _yOffset)
			:BaseAlgorithmWxHparametersType(
				_xOffset,
				_yOffset,
				_kernel.getKernel().getWidth(),
				_kernel.getKernel().getHeight())

			,filterDataPtr       (_kernel.getKernel().getDataView().getDataPtr())

			,filterSkipDataPtr   (_kernel.getKernelSkipDataPtr())
			,filterSkipDataPtrEnd(_kernel.getKernelSkipDataPtrEnd())
		{

		}

		const Pixel::PixelYb1::DataType * const filterDataPtr;

		const I4 * const filterSkipDataPtr;
		const I4 * const filterSkipDataPtrEnd;

};

}

#endif
