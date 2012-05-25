
#include "BoxFilter1xH.h"
#include "BaseBoxFilterAlgorithm.h"
#include "BoxFilter1xHparametersType.h"
#include <Algorithm/Algorithm1xH.h>
#include <Algorithm/Basic1xHbaseAlgorithm.h>

namespace Filter {

template <
	typename PixelType
> void AIL_DLL_EXPORT BoxFilter1xH<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	BoxFilter1xHparametersType<PixelDataType,PixelComputationType> parameters(yOffset,filterHeight,srcImage.getWidth(),PixelType::ComputationRange::getMinPixel(),PixelComputationType(filterHeight));

	Algorithm::Algorithm1xH<
		Algorithm::Basic1xHbaseAlgorithm<
			BaseBoxFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				BoxFilter1xHparametersType<PixelDataType,PixelComputationType>,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			BoxFilter1xHparametersType<PixelDataType,PixelComputationType>,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		BoxFilter1xHparametersType<PixelDataType,PixelComputationType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::BoxFilter1xH)
