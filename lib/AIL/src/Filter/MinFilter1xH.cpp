
#include "MinFilter1xH.h"
#include <Algorithm/BaseAlgorithm1xH.h>
#include "BaseMinFilterAlgorithm.h"
#include "BaseMinFilterParametersType.h"
#include "Simple1xHbooleanOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void AIL_DLL_EXPORT MinFilter1xH<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	filterData.calculateKernelSkipData(srcImage.getWidth());

	BaseMinFilterParametersType<PixelDataType,PixelComputationType> parameters(getFilterData(),getXoffset(),getYoffset(),srcImage.getWidth(),PixelType::ComputationRange::getMaxPixel());

	Algorithm::BaseAlgorithm1xH<
		Simple1xHbooleanOperationBaseAlgorithm<
			BaseMinFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				BaseMinFilterParametersType<PixelDataType,PixelComputationType>,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			BaseMinFilterParametersType<PixelDataType,PixelComputationType>,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		BaseMinFilterParametersType<PixelDataType,PixelComputationType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilter1xH)
