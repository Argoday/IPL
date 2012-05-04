
#ifndef ALGORITHM__Algorithm1xH_H
#define ALGORITHM__Algorithm1xH_H

#include "AIL.h"

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void Algorithm1xH(
	const Image::ImageView<PixelDataType> & srcImage,
	Image::ImageView<PixelDataType> & dstImage,
	const ParameterType & parameter
);

}

#include "Algorithm1xH_cpp.h"

#endif
