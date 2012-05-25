
#include "MaxFilter1xH.h"
#include <Algorithm/Algorithm1xH.h>
#include "BaseMaxFilterAlgorithm.h"
#include "BaseMaxFilterParametersType.h"
#include "Simple1xHbooleanOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void AIL_DLL_EXPORT MaxFilter1xH<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	filterData.calculateKernelSkipData(srcImage.getWidth());

	BaseMaxFilterParametersType<PixelDataType,PixelComputationType> parameters(getFilterData(),getXoffset(),getYoffset(),PixelType::ComputationRange::getMinPixel());

	Algorithm::Algorithm1xH<
		Simple1xHbooleanOperationBaseAlgorithm<
			BaseMaxFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				BaseMaxFilterParametersType<PixelDataType,PixelComputationType>,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			BaseMaxFilterParametersType<PixelDataType,PixelComputationType>,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		BaseMaxFilterParametersType<PixelDataType,PixelComputationType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MaxFilter1xH)
