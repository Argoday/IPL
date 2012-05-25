
#include "MaxFilter1xHbasic.h"
#include <Algorithm/Algorithm1xH.h>
#include "BaseMaxFilterAlgorithm.h"
#include <Algorithm/Basic1xHbaseAlgorithmParametersType.h>
#include <Algorithm/Basic1xHbaseAlgorithm.h>
#include <Algorithm/BaseOperationTempType.h>

namespace Filter {

template <
	typename PixelType
> void AIL_DLL_EXPORT MaxFilter1xHbasic<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	Algorithm::Basic1xHbaseAlgorithmParametersType parameters(yOffset,filterHeight,srcImage.getWidth());

	Algorithm::Algorithm1xH<
		Algorithm::Basic1xHbaseAlgorithm<
			BaseMaxFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				Algorithm::Basic1xHbaseAlgorithmParametersType,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			Algorithm::Basic1xHbaseAlgorithmParametersType,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		Algorithm::Basic1xHbaseAlgorithmParametersType
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MaxFilter1xHbasic)
