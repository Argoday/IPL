
#include "LinearFilter1xH.h"
#include "BaseLinearFilterAlgorithm.h"
#include <Algorithm/Algorithm1xH.h>
#include "Simple1xHdataOperationBaseAlgorithm.h"
#include <Algorithm/BaseOperationTempType.h>
#include "BaseLinearFilterParametersType.h"

namespace Filter {

template <
	typename PixelType
> void LinearFilter1xH<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	BaseLinearFilterParametersType<PixelDataType,PixelComputationType> parameters(
		getFilterData().getDataView(),
		getXoffset(),
		getYoffset(),
		srcImage.getWidth(),
		getTotalColor()
	);

	Algorithm::Algorithm1xH<
		Simple1xHdataOperationBaseAlgorithm<
			BaseLinearFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				BaseLinearFilterParametersType<PixelDataType,PixelComputationType>,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			BaseLinearFilterParametersType<PixelDataType,PixelComputationType>,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		BaseLinearFilterParametersType<PixelDataType,PixelComputationType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::LinearFilter1xH)
