
#include "LinearFilter1xH.h"
#include "BaseLinearFilterAlgorithm.h"
#include <Algorithm/BaseOperationTempType.h>
#include <Algorithm/BaseAlgorithm1xH.h>
#include "Simple1xHdataOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void LinearFilter1xH<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	BaseLinearFilterParametersType<PixelDataType> parameters(
		getFilterData().getDataView(),
		getXoffset(),
		getYoffset(),
		srcImage.getWidth(),
		getTotalColor(),
		PixelType::RangeType::getMinPixel()
	);

	Algorithm::BaseAlgorithm1xH<
		Simple1xHdataOperationBaseAlgorithm<
			BaseLinearFilterAlgorithm<
				PixelDataType,
				BaseLinearFilterParametersType<PixelDataType>,
				Algorithm::BaseOperationTempType<PixelDataType>
			>,
			PixelDataType,
			BaseLinearFilterParametersType<PixelDataType>,
			Algorithm::BaseOperationTempType<PixelDataType>
		>,
		PixelDataType,
		BaseLinearFilterParametersType<PixelDataType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::LinearFilter1xH)
