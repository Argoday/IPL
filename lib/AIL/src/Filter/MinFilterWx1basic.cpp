
#include "MinFilterWx1basic.h"
#include <Algorithm/BaseAlgorithmWx1.h>
#include "BaseMinFilterAlgorithm.h"
#include <Algorithm/BasicWx1baseAlgorithm.h>
#include "MinFilterWx1basicParametersType.h"

namespace Filter {

template <
	typename PixelType
> void MinFilterWx1basic<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	MinFilterWx1basicParametersType<PixelDataType> parameters(xOffset,filterWidth,PixelType::RangeType::getMaxPixel());

	Algorithm::BaseAlgorithmWx1<
		Algorithm::BasicWx1baseAlgorithm<
			BaseMinFilterAlgorithm<
				PixelDataType,
				MinFilterWx1basicParametersType<PixelDataType>,
				Algorithm::BaseOperationTempType<PixelDataType>
			>,
			PixelDataType,
			MinFilterWx1basicParametersType<PixelDataType>,
			Algorithm::BaseOperationTempType<PixelDataType>
		>,
		PixelDataType,
		MinFilterWx1basicParametersType<PixelDataType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilterWx1basic)
