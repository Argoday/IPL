
#include "MaxFilter1xHbasic.h"
#include <Algorithm/BaseAlgorithm1xH.h>
#include "BaseMaxFilterAlgorithm.h"
#include <Algorithm/Basic1xHbaseAlgorithm.h>
#include "MaxFilter1xHbasicParametersType.h"

namespace Filter {

template <
	typename PixelType
> void MaxFilter1xHbasic<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	MaxFilter1xHbasicParametersType<PixelDataType> parameters(yOffset,filterHeight,srcImage.getWidth(),PixelType::RangeType::getMinPixel());

	Algorithm::BaseAlgorithm1xH<
		Algorithm::Basic1xHbaseAlgorithm<
			BaseMaxFilterAlgorithm<
				PixelDataType,
				MaxFilter1xHbasicParametersType<PixelDataType>,
				Algorithm::BaseOperationTempType<PixelDataType>
			>,
			PixelDataType,
			MaxFilter1xHbasicParametersType<PixelDataType>,
			Algorithm::BaseOperationTempType<PixelDataType>
		>,
		PixelDataType,
		MaxFilter1xHbasicParametersType<PixelDataType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MaxFilter1xHbasic)
