
#ifndef ALGORITHM__AlgorithmWxH_H
#define ALGORITHM__AlgorithmWxH_H

#include "AIL.h"

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelType,
	typename ParameterType
> void AlgorithmWxH (
	const Image::ImageView<PixelType> & srcImage,
	Image::ImageView<PixelType> & dstImage,
	const ParameterType & parameter
);

}

#include "AlgorithmWxH_cpp.h"

#endif
