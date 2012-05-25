
#include "LinearFilterWx1.h"
#include "BaseLinearFilterAlgorithm.h"
#include <Algorithm/AlgorithmWx1.h>
#include "SimpleWx1dataOperationBaseAlgorithm.h"
#include <Algorithm/BaseOperationTempType.h>
#include "BaseLinearFilterParametersType.h"

namespace Filter {

template <
	typename PixelType
> void LinearFilterWx1<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	BaseLinearFilterParametersType<PixelDataType,PixelComputationType> parameters(
		getFilterData().getDataView(),
		getXoffset(),
		getYoffset(),
		srcImage.getWidth(),
		getTotalColor()
	);

	Algorithm::AlgorithmWx1<
		SimpleWx1dataOperationBaseAlgorithm<
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
CREATE_PIXEL_TEMPLATE_CALLS(Filter::LinearFilterWx1)
