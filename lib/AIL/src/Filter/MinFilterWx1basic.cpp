
#include "MinFilterWx1basic.h"
#include <Algorithm/AlgorithmWx1.h>
#include "BaseMinFilterAlgorithm.h"
#include <Algorithm/BasicWx1baseAlgorithmParametersType.h>
#include <Algorithm/BasicWx1baseAlgorithm.h>
#include <Algorithm/BaseOperationTempType.h>

namespace Filter {

template <
	typename PixelType
> void AIL_DLL_EXPORT MinFilterWx1basic<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	Algorithm::BasicWx1baseAlgorithmParametersType parameters(xOffset,filterWidth);

	Algorithm::AlgorithmWx1<
		Algorithm::BasicWx1baseAlgorithm<
			BaseMinFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				Algorithm::BasicWx1baseAlgorithmParametersType,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			Algorithm::BasicWx1baseAlgorithmParametersType,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		Algorithm::BasicWx1baseAlgorithmParametersType
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilterWx1basic)
