
#ifndef ALGORITHM__AlgorithmWxH_CPP_H
#define ALGORITHM__AlgorithmWxH_CPP_H

#include "AIL.h"
#include "BaseAlgorithmWxH.h"
#include <Image/ImageView.h>

#ifdef PPL
#include <ppl.h>
#endif

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void AlgorithmWxH(
	const Image::ImageView<PixelDataType> & srcImage,
	Image::ImageView<PixelDataType> & dstImage,
	const ParameterType & parameter)
{
	#ifdef PPL
		if(srcImage.getSize()!=dstImage.getSize()){return;}
		auto srcGrid = srcImage.makeGrid(100,100,parameter.xOffset,parameter.yOffset,parameter.filterWidth,parameter.filterHeight);
		auto dstGrid = dstImage.makeGrid(100,100,parameter.xOffset,parameter.yOffset,parameter.filterWidth,parameter.filterHeight);
		Concurrency::parallel_for<I8u>(0,srcGrid.size(),[&](I8u i){
			BaseAlgorithmWxH<AlgorithmType,PixelDataType,ParameterType>(srcGrid[i],dstGrid[i],parameter);
		});
	#else
		BaseAlgorithmWxH<AlgorithmType,PixelDataType,ParameterType>(srcImage,dstImage,parameter);
	#endif
}

}

#endif 
