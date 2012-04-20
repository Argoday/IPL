
#ifndef ALGORITHM__BaseAlgorithm1xH_CPP_H
#define ALGORITHM__BaseAlgorithm1xH_CPP_H

#include "BaseAlgorithm1xH.h"
#include <Image/ImageView.h>

namespace Algorithm {

//Concept: ParametersType must sub-class BaseAlgorithm1xHParametersType
template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void BaseAlgorithm1xH (
	const Image::ImageView<PixelDataType> & srcImage,
	Image::ImageView<PixelDataType> & dstImage,
	const ParameterType & parameter)
{
	if((srcImage.isSimpleView()==false)||(dstImage.isSimpleView()==false)){return;} // TODO: implement the other cases
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	auto srcImageHeight = srcImage.getHeight();
	auto srcImageWidth  = srcImage.getWidth();

	auto borderYBottom = parameter.borderYBottom;
	auto borderYTop    = parameter.borderYTop;

	auto srcImageDataPtr = srcImage.getDataPtr();

	auto dstImageDataPtr = dstImage.getDataPtr();
	auto dstImageDataPtrRowsEnd = dstImage.getDataPtr() + (srcImageHeight-borderYTop)*srcImageWidth;

	I4 y = 0;
	I4 x = 0;

	//First Rows
	for(;y<borderYBottom;++y){
		for (x=0; x<srcImageWidth; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
	}

	//Inside Rows
	for (;dstImageDataPtr!=dstImageDataPtrRowsEnd;){
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr,parameter);
		++dstImageDataPtr;
		++srcImageDataPtr;
	}

	//Last Rows
	for(y=srcImageHeight-borderYTop;y<srcImageHeight;++y){
		for (x=0; x<srcImageWidth; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
	}

}

};

#endif
