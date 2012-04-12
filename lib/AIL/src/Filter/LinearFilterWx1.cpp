
#include "LinearFilterWx1.h"
#include <Algorithm/BaseAlgorithmWx1.h>
#include "BaseLinearFilterAlgorithm.h"
#include "SimpleWx1dataOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void LinearFilterWx1<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	BaseLinearFilterParametersType<PixelDataType> parameters(
		getFilterData().getDataView(),
		getXoffset(),
		getYoffset(),
		srcImage.getWidth(),
		getTotalColor(),
		PixelType::RangeType::getMinPixel()
	);

	Algorithm::BaseAlgorithmWx1<
		SimpleWx1dataOperationBaseAlgorithm<
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
CREATE_PIXEL_TEMPLATE_CALLS(Filter::LinearFilterWx1)
