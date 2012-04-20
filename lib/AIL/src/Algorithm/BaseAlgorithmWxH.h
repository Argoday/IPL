
#ifndef ALGORITHM__BaseAlgorithmWxH_H
#define ALGORITHM__BaseAlgorithmWxH_H

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelType,
	typename ParameterType
> void BaseAlgorithmWxH (
	const Image::ImageView<PixelType> & srcImage,
	Image::ImageView<PixelType> & dstImage,
	const ParameterType & parameter
);

}

#include "BaseAlgorithmWxH_cpp.h"

#endif
