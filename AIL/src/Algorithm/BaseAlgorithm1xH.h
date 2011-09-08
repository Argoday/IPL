
#ifndef ALGORITHM__BaseAlgorithm1xH_H
#define ALGORITHM__BaseAlgorithm1xH_H

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void BaseAlgorithm1xH(
	const Image::ImageView<PixelDataType> &srcImage,
	Image::ImageView<PixelDataType> &dstImage,
	const ParameterType &parameter
);

}

#include "BaseAlgorithm1xH_cpp.h"

#endif
