
#include "MaxFilter1xH.h"
#include <Algorithm/BaseAlgorithm1xH.h>
#include "BaseMaxFilterAlgorithm.h"
#include "BaseMaxFilterParametersType.h"
#include "Simple1xHbooleanOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void MaxFilter1xH<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	filterData.calculateKernelSkipData(srcImage.getWidth());

	BaseMaxFilterParametersType<PixelDataType> parameters(getFilterData(),getXoffset(),getYoffset(),srcImage.getWidth(),PixelType::RangeType::getMinPixel());

	Algorithm::BaseAlgorithm1xH<
		Simple1xHbooleanOperationBaseAlgorithm<
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
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MaxFilter1xH)
