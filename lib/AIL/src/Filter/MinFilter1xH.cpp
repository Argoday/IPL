
#include "MinFilter1xH.h"
#include <Algorithm/BaseAlgorithm1xH.h>
#include "BaseMinFilterAlgorithm.h"
#include "BaseMinFilterParametersType.h"
#include "Simple1xHbooleanOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void MinFilter1xH<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	filterData.calculateKernelSkipData(srcImage.getWidth());

	BaseMinFilterParametersType<PixelDataType> parameters(getFilterData(),getXoffset(),getYoffset(),srcImage.getWidth(),PixelType::RangeType::getMaxPixel());

	Algorithm::BaseAlgorithm1xH<
		Simple1xHbooleanOperationBaseAlgorithm<
			BaseMinFilterAlgorithm<
				PixelDataType,
				BaseMinFilterParametersType<PixelDataType>,
				Algorithm::BaseOperationTempType<PixelDataType>
			>,
			PixelDataType,
			BaseMinFilterParametersType<PixelDataType>,
			Algorithm::BaseOperationTempType<PixelDataType>
		>,
		PixelDataType,
		BaseMinFilterParametersType<PixelDataType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilter1xH)
