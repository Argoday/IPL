
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
	const Image::ImageView<PixelDataType> &srcImage,
	Image::ImageView<PixelDataType> &dstImage,
	const ParameterType &parameter)
{
	if((srcImage.isSimpleView()==false)||(dstImage.isSimpleView()==false)){return;} // TODO: implement the other cases
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	long srcImageHeight = srcImage.getHeight();
	long srcImageWidth  = srcImage.getWidth();

	long borderXLeft   = parameter.borderXLeft;
	long borderXRight  = parameter.borderXRight;

	long borderXRightAndLeft=borderXRight+borderXLeft;

	const PixelDataType *srcImageDataPtr = srcImage.getDataPtr();
	PixelDataType *dstImageDataPtr = dstImage.getDataPtr();
	const PixelDataType *dstImageDataPtrRowEnd = dstImage.getDataPtr() + srcImageWidth-borderXLeft;

	long y = 0;
	long x = 0;

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
