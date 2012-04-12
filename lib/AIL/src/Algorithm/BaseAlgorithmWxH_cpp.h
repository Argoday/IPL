
#ifndef ALGORITHM__BaseAlgorithmWxH_CPP_H
#define ALGORITHM__BaseAlgorithmWxH_CPP_H

#include "BaseAlgorithmWxH.h"
#include <Image/ImageView.h>

namespace Algorithm {

//Concept: ParametersType must sub-class BaseAlgorithmWxHParametersType
template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void BaseAlgorithmWxH (
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
	long borderYBottom = parameter.borderYBottom;
	long borderYTop    = parameter.borderYTop;

	long borderXRightAndLeft=borderXRight+borderXLeft;

	const PixelDataType *srcImageDataPtr = srcImage.getDataPtr();
	PixelDataType *dstImageDataPtr = dstImage.getDataPtr();

	long y = 0; // TODO: Write these loops to reduce use of x and y
	long x = 0;

	//First Rows
	for(;y<borderYBottom;++y){
		for (x=0; x<srcImageWidth; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
	}
	
	for (; y<srcImageHeight-borderYTop; ++y){	
		//First Pixels of inside Row
		for (x=0; x<borderXRight; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
		//Inside Row
		for (; x<srcImageWidth-borderXLeft; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImageDataPtr,parameter);
			++dstImageDataPtr;
			++srcImageDataPtr;
		}
		//Last Pixels Inside Row
		for (; x<srcImageWidth; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
		srcImageDataPtr+=borderXRightAndLeft;
	}

	//Last Rows
	for(;y<srcImageHeight;++y){
		for (x=0; x<srcImageWidth; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
	}

}

};

#endif
