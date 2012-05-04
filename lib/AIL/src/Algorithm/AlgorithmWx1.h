
#ifndef ALGORITHM__AlgorithmWx1_H
#define ALGORITHM__AlgorithmWx1_H

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

#include "AlgorithmWx1_cpp.h"

#endif
