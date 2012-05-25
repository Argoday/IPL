
#ifndef ALGORITHM__Algorithm1xH_CPP_H
#define ALGORITHM__Algorithm1xH_CPP_H

#include "AIL.h"
#include "BaseAlgorithm1xH.h"
#include <Image/ImageView.h>

#ifdef PPL
#include <ppl.h>
#endif

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void Algorithm1xH(
	const Image::ImageView<PixelDataType> & srcImage,
	Image::ImageView<PixelDataType> & dstImage,
	const ParameterType & parameter)
{
	#ifdef PPL
		if(srcImage.getSize()!=dstImage.getSize()){return;}
		auto srcGrid = srcImage.makeGrid(100,100,0,parameter.yOffset,1,parameter.filterHeight);
		auto dstGrid = dstImage.makeGrid(100,100,0,parameter.yOffset,1,parameter.filterHeight);
		Concurrency::parallel_for<I8u>(0,srcGrid.size(),[&](I8u i){
			BaseAlgorithm1xH<AlgorithmType,PixelDataType,ParameterType>(srcGrid[i],dstGrid[i],parameter);
		});
	#else
		BaseAlgorithm1xH<AlgorithmType,PixelDataType,ParameterType>(srcImage,dstImage,parameter);
	#endif
}

}

#endif 
