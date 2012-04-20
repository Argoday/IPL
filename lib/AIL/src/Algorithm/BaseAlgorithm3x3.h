
#ifndef ALGORITHM__BaseAlgorithm3x3_H
#define ALGORITHM__BaseAlgorithm3x3_H

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelType
> void BaseAlgorithm3x3 (
	const Image::ImageView<PixelType> & srcImage,
	Image::ImageView<PixelType> & dstImage
);

}

#include "BaseAlgorithm3x3_cpp.h"

#endif
