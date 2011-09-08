
#ifndef ALGORITHM__BaseAlgorithm1x1_H
#define ALGORITHM__BaseAlgorithm1x1_H

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelDataType
> void BaseAlgorithm1x1(
	Image::ImageView<PixelDataType> &image
);

template <
	typename AlgorithmType,
	typename PixelDataType
> void BaseAlgorithm1x1(
	const Image::ImageView<PixelDataType> &srcImage,
	Image::ImageView<PixelDataType> &dstImage
);

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void BaseAlgorithm1x1p(
	Image::ImageView<PixelDataType> &image,
	const ParameterType &parameter
);

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void BaseAlgorithm1x1p(
	const Image::ImageView<PixelDataType> &srcImage,
	Image::ImageView<PixelDataType> &dstImage,
	const ParameterType &parameter
);

template <
	typename AlgorithmType,
	typename PixelDataType
>
	void BaseAlgorithm1x1p(
		Image::ImageView<PixelDataType> &srcImage,
		const Image::ImageView<PixelDataType> &parameterImage
);

}

#include "BaseAlgorithm1x1_cpp.h"

#endif
