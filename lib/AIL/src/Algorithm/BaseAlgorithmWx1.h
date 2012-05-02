
#ifndef ALGORITHM__BaseAlgorithmWx1_H
#define ALGORITHM__BaseAlgorithmWx1_H

#include "AIL.h"

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelType,
	typename ParameterType
> void BaseAlgorithmWx1 (
	const Image::ImageView<PixelType> & srcImage,
	Image::ImageView<PixelType> & dstImage,
	const ParameterType & parameter
);

}

#include "BaseAlgorithmWx1_cpp.h"

#endif
