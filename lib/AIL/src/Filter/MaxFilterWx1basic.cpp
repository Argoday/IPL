
#include "MaxFilterWx1basic.h"
#include <Algorithm/BaseAlgorithmWx1.h>
#include "BaseMaxFilterAlgorithm.h"
#include <Algorithm/BasicWx1baseAlgorithm.h>
#include "MaxFilterWx1basicParametersType.h"

namespace Filter {

template <
	typename PixelType
> void MaxFilterWx1basic<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	MaxFilterWx1basicParametersType<PixelDataType,PixelComputationType> parameters(xOffset,filterWidth,PixelType::ComputationRange::getMinPixel());

	Algorithm::BaseAlgorithmWx1<
		Algorithm::BasicWx1baseAlgorithm<
			BaseMaxFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				MaxFilterWx1basicParametersType<PixelDataType,PixelComputationType>,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			MaxFilterWx1basicParametersType<PixelDataType,PixelComputationType>,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		MaxFilterWx1basicParametersType<PixelDataType,PixelComputationType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MaxFilterWx1basic)
