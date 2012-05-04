
#ifndef ALGORITHM__Algorithm3x3_H
#define ALGORITHM__Algorithm3x3_H

#include "AIL.h"

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelType
> void Algorithm3x3 (
	const Image::ImageView<PixelType> & srcImage,
	Image::ImageView<PixelType> & dstImage
);

}

#include "Algorithm3x3_cpp.h"

#endif
