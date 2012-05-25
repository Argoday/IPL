
#include "LinearFilterWxH.h"
#include "BaseLinearFilterAlgorithm.h"
#include <Algorithm/AlgorithmWxH.h>
#include "SimpleWxHdataOperationBaseAlgorithm.h"
#include <Algorithm/BaseOperationTempType.h>
#include "BaseLinearFilterParametersType.h"

namespace Filter {

template <
	typename PixelType
> void LinearFilterWxH<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	BaseLinearFilterParametersType<PixelDataType,PixelComputationType> parameters(
		getFilterData().getDataView(),
		getXoffset(),
		getYoffset(),
		srcImage.getWidth(),
		getTotalColor()
	);

	Algorithm::AlgorithmWxH<
		SimpleWxHdataOperationBaseAlgorithm<
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
CREATE_PIXEL_TEMPLATE_CALLS(Filter::LinearFilterWxH)
