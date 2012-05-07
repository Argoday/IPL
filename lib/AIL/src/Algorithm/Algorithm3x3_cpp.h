
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
	typename PixelDataType
> void Algorithm3x3(
	const Image::ImageView<PixelDataType> & srcImage,
	Image::ImageView<PixelDataType> & dstImage)
{
	#ifndef PPL
		BaseAlgorithm3x3<AlgorithmType,PixelDataType>(srcImage,dstImage);
	#else
		if(srcImage.getSize()!=dstImage.getSize()){return;}
		auto srcGrid = srcImage.makeGrid(100,100,1,1,3,3);
		auto dstGrid = dstImage.makeGrid(100,100,1,1,3,3);
		Concurrency::parallel_for<I8u>(0,srcGrid.size(),[&](I8u i){
			BaseAlgorithm3x3<AlgorithmType,PixelDataType>(srcGrid[i],dstGrid[i]);
		});
	#endif
}

}

#endif 
