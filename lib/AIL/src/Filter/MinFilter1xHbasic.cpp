
#include "MinFilter1xHbasic.h"
#include <Algorithm/BaseAlgorithm1xH.h>
#include "BaseMinFilterAlgorithm.h"
#include <Algorithm/Basic1xHbaseAlgorithm.h>
#include "MinFilter1xHbasicParametersType.h"

namespace Filter {

template <
	typename PixelType
> void MinFilter1xHbasic<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	MinFilter1xHbasicParametersType<PixelDataType,PixelComputationType> parameters(yOffset,filterHeight,srcImage.getWidth(),PixelType::ComputationRange::getMaxPixel());

	Algorithm::BaseAlgorithm1xH<
		Algorithm::Basic1xHbaseAlgorithm<
			BaseMinFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				MinFilter1xHbasicParametersType<PixelDataType,PixelComputationType>,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			MinFilter1xHbasicParametersType<PixelDataType,PixelComputationType>,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		MinFilter1xHbasicParametersType<PixelDataType,PixelComputationType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilter1xHbasic)
