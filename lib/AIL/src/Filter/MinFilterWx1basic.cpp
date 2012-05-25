
#include "MinFilterWx1basic.h"
#include <Algorithm/AlgorithmWx1.h>
#include "BaseMinFilterAlgorithm.h"
#include <Algorithm/BasicWx1baseAlgorithm.h>
#include "MinFilterWx1basicParametersType.h"

namespace Filter {

template <
	typename PixelType
> void AIL_DLL_EXPORT MinFilterWx1basic<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	MinFilterWx1basicParametersType<PixelDataType,PixelComputationType> parameters(xOffset,filterWidth,PixelType::ComputationRange::getMaxPixel());

	Algorithm::AlgorithmWx1<
		Algorithm::BasicWx1baseAlgorithm<
			BaseMinFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				MinFilterWx1basicParametersType<PixelDataType,PixelComputationType>,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			MinFilterWx1basicParametersType<PixelDataType,PixelComputationType>,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		MinFilterWx1basicParametersType<PixelDataType,PixelComputationType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilterWx1basic)
