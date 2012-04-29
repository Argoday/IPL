
#include "MaxFilter1xHbasic.h"
#include <Algorithm/BaseAlgorithm1xH.h>
#include "BaseMaxFilterAlgorithm.h"
#include "MaxFilter1xHbasicParametersType.h"
#include <Algorithm/Basic1xHbaseAlgorithm.h>

namespace Filter {

template <
	typename PixelType
> void AIL_DLL_EXPORT MaxFilter1xHbasic<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	MaxFilter1xHbasicParametersType<PixelDataType,PixelComputationType> parameters(yOffset,filterHeight,srcImage.getWidth(),PixelType::ComputationRange::getMinPixel());

	Algorithm::BaseAlgorithm1xH<
		Algorithm::Basic1xHbaseAlgorithm<
			BaseMaxFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				MaxFilter1xHbasicParametersType<PixelDataType,PixelComputationType>,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			MaxFilter1xHbasicParametersType<PixelDataType,PixelComputationType>,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		MaxFilter1xHbasicParametersType<PixelDataType,PixelComputationType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MaxFilter1xHbasic)
