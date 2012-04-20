
#include "LinearFilterWxH.h"
#include <Algorithm/BaseAlgorithmWxH.h>
#include "BaseLinearFilterAlgorithm.h"
#include "SimpleWxHdataOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void LinearFilterWxH<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	BaseLinearFilterParametersType<PixelDataType> parameters(
		getFilterData().getDataView(),
		getXoffset(),
		getYoffset(),
		srcImage.getWidth(),
		getTotalColor(),
		PixelType::RangeType::getMinPixel()
	);

	Algorithm::BaseAlgorithmWxH<
		SimpleWxHdataOperationBaseAlgorithm<
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
CREATE_PIXEL_TEMPLATE_CALLS(Filter::LinearFilterWxH)
