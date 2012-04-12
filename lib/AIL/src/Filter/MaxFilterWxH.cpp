
#include "MaxFilterWxH.h"
#include <Algorithm/BaseAlgorithmWxH.h>
#include "BaseMaxFilterAlgorithm.h"
#include "BaseMaxFilterParametersType.h"
#include "SimpleWxHbooleanOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void MaxFilterWxH<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	filterData.calculateKernelSkipData(srcImage.getWidth());

	BaseMaxFilterParametersType<PixelDataType> parameters(getFilterData(),getXoffset(),getYoffset(),srcImage.getWidth(),PixelType::RangeType::getMinPixel());

	Algorithm::BaseAlgorithmWxH<
		SimpleWxHbooleanOperationBaseAlgorithm<
			BaseMaxFilterAlgorithm<
				PixelDataType,
				BaseMaxFilterParametersType<PixelDataType>,
				Algorithm::BaseOperationTempType<PixelDataType>
			>,
			PixelDataType,
			BaseMaxFilterParametersType<PixelDataType>,
			Algorithm::BaseOperationTempType<PixelDataType>
		>,
		PixelDataType,
		BaseMaxFilterParametersType<PixelDataType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MaxFilterWxH)
