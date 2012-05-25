
#include "MinFilterWxH.h"
#include <Algorithm/AlgorithmWxH.h>
#include "BaseMinFilterAlgorithm.h"
#include "SimpleWxHbooleanOperationParametersType.h"
#include "SimpleWxHbooleanOperationBaseAlgorithm.h"
#include <Algorithm/BaseOperationTempType.h>

namespace Filter {

template <
	typename PixelType
> void AIL_DLL_EXPORT MinFilterWxH<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {

	typedef typename PixelType::DataType        PixelDataType;
	typedef typename PixelType::ComputationType PixelComputationType;

	filterData.calculateKernelSkipData(srcImage.getWidth());

	SimpleWxHbooleanOperationParametersType parameters(getFilterData(),getXoffset(),getYoffset());

	Algorithm::AlgorithmWxH<
		SimpleWxHbooleanOperationBaseAlgorithm<
			BaseMinFilterAlgorithm<
				PixelDataType,
				PixelComputationType,
				SimpleWxHbooleanOperationParametersType,
				Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
			>,
			PixelDataType,
			PixelComputationType,
			SimpleWxHbooleanOperationParametersType,
			Algorithm::BaseOperationTempType<PixelDataType,PixelComputationType>
		>,
		PixelDataType,
		SimpleWxHbooleanOperationParametersType
	>(
		srcImage.getDataView(),
		dstImage.getDataView(),
		parameters
	);

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::MinFilterWxH)
