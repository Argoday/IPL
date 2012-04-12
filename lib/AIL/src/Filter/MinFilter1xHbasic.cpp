
#include "MinFilter1xHbasic.h"
#include <Algorithm/BaseAlgorithm1xH.h>
#include "BaseMinFilterAlgorithm.h"
#include <Algorithm/Basic1xHbaseAlgorithm.h>
#include "MinFilter1xHbasicParametersType.h"

namespace Filter {

template <
	typename PixelType
> void MinFilter1xHbasic<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	MinFilter1xHbasicParametersType<PixelDataType> parameters(yOffset,filterHeight,srcImage.getWidth(),PixelType::RangeType::getMaxPixel());

	Algorithm::BaseAlgorithm1xH<
		Algorithm::Basic1xHbaseAlgorithm<
			BaseMinFilterAlgorithm<
				PixelDataType,
				MinFilter1xHbasicParametersType<PixelDataType>,
				Algorithm::BaseOperationTempType<PixelDataType>
			>,
			PixelDataType,
			MinFilter1xHbasicParametersType<PixelDataType>,
			Algorithm::BaseOperationTempType<PixelDataType>
		>,
		PixelDataType,
		MinFilter1xHbasicParametersType<PixelDataType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilter1xHbasic)
