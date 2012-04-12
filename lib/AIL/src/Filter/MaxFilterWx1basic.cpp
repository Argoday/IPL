
#include "MaxFilterWx1basic.h"
#include <Algorithm/BaseAlgorithmWx1.h>
#include "BaseMaxFilterAlgorithm.h"
#include <Algorithm/BasicWx1baseAlgorithm.h>
#include "MaxFilterWx1basicParametersType.h"

namespace Filter {

template <
	typename PixelType
> void MaxFilterWx1basic<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	MaxFilterWx1basicParametersType<PixelDataType> parameters(xOffset,filterWidth,PixelType::RangeType::getMinPixel());

	Algorithm::BaseAlgorithmWx1<
		Algorithm::BasicWx1baseAlgorithm<
			BaseMaxFilterAlgorithm<
				PixelDataType,
				MaxFilterWx1basicParametersType<PixelDataType>,
				Algorithm::BaseOperationTempType<PixelDataType>
			>,
			PixelDataType,
			MaxFilterWx1basicParametersType<PixelDataType>,
			Algorithm::BaseOperationTempType<PixelDataType>
		>,
		PixelDataType,
		MaxFilterWx1basicParametersType<PixelDataType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MaxFilterWx1basic)
