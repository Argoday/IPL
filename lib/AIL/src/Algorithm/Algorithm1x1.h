
#ifndef ALGORITHM__Algorithm1x1_H
#define ALGORITHM__Algorithm1x1_H

#include "ACore.h"
#include "Algorithm1x1.h"

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelDataType
> void Algorithm1x1(
	Image::ImageView<PixelDataType> & image
);

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void Algorithm1x1p(
	Image::ImageView<PixelDataType> & image,
	const ParameterType & parameter
);

template <
	typename AlgorithmType,
	typename PixelDataType
> void Algorithm1x1p(
	Image::ImageView<PixelDataType> & srcImage,
	const Image::ImageView<PixelDataType> & parameterImage
);

template <
	typename AlgorithmType,
	typename SrcPixelDataType,
	typename DstPixelDataType
> void Algorithm1x1(
	const Image::ImageView<SrcPixelDataType> & srcImage,
	Image::ImageView<DstPixelDataType> & dstImage
);

template <
	typename AlgorithmType,
	typename SrcPixelDataType,
	typename DstPixelDataType,
	typename ParameterType
> void Algorithm1x1p(
	const Image::ImageView<SrcPixelDataType> & srcImage,
	Image::ImageView<DstPixelDataType> & dstImage,
	const ParameterType & parameter
);

}

#include "Algorithm1x1_cpp.h"

#endif 
