
#ifndef ALGORITHM__BaseAlgorithmWx1_CPP_H
#define ALGORITHM__BaseAlgorithmWx1_CPP_H

#include "BaseAlgorithmWx1.h"
#include <Image/ImageView.h>

namespace Algorithm {

//Concept: ParametersType must sub-class BaseAlgorithmWx1ParametersType
template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void BaseAlgorithmWx1 (
	const Image::ImageView<PixelDataType> & srcImage,
	Image::ImageView<PixelDataType> & dstImage,
	const ParameterType & parameter)
{
	if((srcImage.isSimpleView()==false)||(dstImage.isSimpleView()==false)){return;} // TODO: implement the other cases
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	auto srcImageHeight = srcImage.getHeight();
	auto srcImageWidth  = srcImage.getWidth();

	auto borderXLeft   = parameter.borderXLeft;
	auto borderXRight  = parameter.borderXRight;

	auto borderXRightAndLeft=borderXRight+borderXLeft;

	auto srcImageDataPtr = srcImage.getDataPtr();
	auto dstImageDataPtr = dstImage.getDataPtr();
	auto dstImageDataPtrRowEnd = dstImage.getDataPtr() + srcImageWidth-borderXLeft;

	I4 y = 0;
	I4 x = 0;

	for (;y<srcImageHeight;++y){
		//First Pixels of Row
		for (x=0;x<borderXRight;++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
		//Inside Row
		for (;dstImageDataPtr!=dstImageDataPtrRowEnd;){
			AlgorithmType::process(dstImageDataPtr,srcImageDataPtr,parameter);
			++dstImageDataPtr;
			++srcImageDataPtr;
		}
		//Last Pixels of Row
		for (x=srcImageWidth-borderXLeft;x<srcImageWidth;++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
		dstImageDataPtrRowEnd+=srcImageWidth;
		srcImageDataPtr+=borderXRightAndLeft;
	}

}

};

#endif
