
#include "BoxFilterWx1.h"
#include "BaseBoxFilterAlgorithm.h"
#include "BoxFilterWx1parametersType.h"
#include <Algorithm/AlgorithmWx1.h>
#include <Algorithm/BasicWx1baseAlgorithm.h>

namespace Filter {

template <
	typename PixelType
> void AIL_DLL_EXPORT BoxFilterWx1<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	BoxFilterWx1parametersType<PixelDataType,PixelComputationType> parameters(xOffset,filterWidth,PixelType::ComputationRange::getMinPixel(),PixelComputationType(filterWidth));

	Algorithm::AlgorithmWx1<
		Algorithm::BasicWx1baseAlgorithm<
			BaseBoxFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				BoxFilterWx1parametersType<PixelDataType,PixelComputationType>,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			BoxFilterWx1parametersType<PixelDataType,PixelComputationType>,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		BoxFilterWx1parametersType<PixelDataType,PixelComputationType>
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::BoxFilterWx1)
