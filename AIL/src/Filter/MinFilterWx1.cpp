
#include "MinFilterWx1.h"
#include <Algorithm/BaseAlgorithmWx1.h>
#include "BaseMinFilterAlgorithm.h"
#include "BaseMinFilterParametersType.h"
#include "SimpleWx1booleanOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void MinFilterWx1<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	filterData.calculateKernelSkipData(srcImage.getWidth());

	BaseMinFilterParametersType<PixelDataType> parameters(getFilterData(),getXoffset(),getYoffset(),srcImage.getWidth(),PixelType::RangeType::getMaxPixel());

	Algorithm::BaseAlgorithmWx1<
		SimpleWx1booleanOperationBaseAlgorithm<
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
		srcImage.getView(),
		dstImage.getView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilterWx1)
