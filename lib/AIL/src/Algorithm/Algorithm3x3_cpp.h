
#ifndef ALGORITHM__Algorithm3x3_CPP_H
#define ALGORITHM__Algorithm3x3_CPP_H

#include "AIL.h"
#include "BaseAlgorithm3x3.h"
#include <Image/ImageView.h>

#ifdef PPL
#include <ppl.h>
#endif

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void Algorithm3x3(
	const Image::ImageView<PixelDataType> & srcImage,
	Image::ImageView<PixelDataType> & dstImage,
	const ParameterType & parameter)
{
	#ifndef PPL
		BaseAlgorithm3x3<AlgorithmType,PixelDataType,ParameterType>(srcImage,dstImage,parameter);
	#else
		if(srcImage.getSize()!=dstImage.getSize()){return;}
		auto srcGrid = srcImage.makeGrid(500,500,0,0,0,0);
		auto dstGrid = dstImage.makeGrid(500,500,0,0,0,0);
		Concurrency::parallel_for<I8u>(0,srcGrid.size(),[&](I8u i){
			BaseAlgorithm3x3<AlgorithmType,PixelDataType,ParameterType>(srcGrid[i],dstGrid[i],parameter);
		});
	#endif
}

}

#endif 
