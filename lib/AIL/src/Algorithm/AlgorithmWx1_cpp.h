
#ifndef ALGORITHM__AlgorithmWx1_CPP_H
#define ALGORITHM__AlgorithmWx1_CPP_H

#include "AIL.h"
#include "BaseAlgorithmWx1.h"
#include <Image/ImageView.h>

#ifdef PPL
#include <ppl.h>
#endif

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void AlgorithmWx1(
	const Image::ImageView<PixelDataType> & srcImage,
	Image::ImageView<PixelDataType> & dstImage,
	const ParameterType & parameter)
{
	#ifdef PPL
		if(srcImage.getSize()!=dstImage.getSize()){return;}
		auto srcGrid = srcImage.makeGrid(100,100,parameter.xOffset,0,parameter.filterWidth,1);
		auto dstGrid = dstImage.makeGrid(100,100,parameter.xOffset,0,parameter.filterWidth,1);
		Concurrency::parallel_for<I8u>(0,srcGrid.size(),[&](I8u i){
			BaseAlgorithmWx1<AlgorithmType,PixelDataType,ParameterType>(srcGrid[i],dstGrid[i],parameter);
		});
	#else
		BaseAlgorithmWx1<AlgorithmType,PixelDataType,ParameterType>(srcImage,dstImage,parameter);
	#endif
}

}

#endif 
