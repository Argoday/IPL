
#include "MinFilterWxH.h"
#include <Algorithm/BaseAlgorithmWxH.h>
#include "BaseMinFilterAlgorithm.h"
#include "BaseMinFilterParametersType.h"
#include "SimpleWxHbooleanOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void MinFilterWxH<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	filterData.calculateKernelSkipData(srcImage.getWidth());

	BaseMinFilterParametersType<PixelDataType> parameters(getFilterData(),getXoffset(),getYoffset(),srcImage.getWidth(),PixelType::RangeType::getMaxPixel());

	Algorithm::BaseAlgorithmWxH<
		SimpleWxHbooleanOperationBaseAlgorithm<
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
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilterWxH)
