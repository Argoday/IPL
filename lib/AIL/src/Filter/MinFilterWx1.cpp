
#include "MinFilterWx1.h"
#include <Algorithm/AlgorithmWx1.h>
#include "BaseMinFilterAlgorithm.h"
#include "BaseMinFilterParametersType.h"
#include "SimpleWx1booleanOperationBaseAlgorithm.h"

namespace Filter {

template <
	typename PixelType
> void AIL_DLL_EXPORT MinFilterWx1<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	filterData.calculateKernelSkipData(srcImage.getWidth());

	BaseMinFilterParametersType<PixelDataType,PixelComputationType> parameters(getFilterData(),getXoffset(),getYoffset(),PixelType::ComputationRange::getMaxPixel());

	Algorithm::AlgorithmWx1<
		SimpleWx1booleanOperationBaseAlgorithm<
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
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilterWx1)
