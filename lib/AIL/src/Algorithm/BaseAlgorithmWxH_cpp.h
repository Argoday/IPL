
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
	const Image::ImageView<PixelDataType> & srcImage,
	Image::ImageView<PixelDataType> & dstImage,
	const ParameterType & parameter)
{
	if((srcImage.isSimpleView()==false)||(dstImage.isSimpleView()==false)){return;} // TODO: implement the other cases
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	auto srcImageHeight = srcImage.getHeight();
	auto srcImageWidth  = srcImage.getWidth();

	const auto & xOffset = parameter.xOffset;
	const auto & yOffset = parameter.yOffset;
	
	const auto & filterWidth  = parameter.filterWidth;
	const auto & filterHeight = parameter.filterHeight;

	auto srcImageWidth_filterWidthOffset   = srcImageWidth  - (filterWidth  - xOffset);
	auto srcImageHeight_filterHeightOffset = srcImageHeight - (filterHeight - yOffset);

	auto srcImageDataPtr = srcImage.getDataPtr();
	auto dstImageDataPtr = dstImage.getDataPtr();

	I4 y = 0; // TODO: Write these loops to reduce use of x and y
	I4 x = 0;

	//First Rows
	for(;y<yOffset;++y){
		for (x=0; x<srcImageWidth; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
	}
	
	for (; y<srcImageHeight_filterHeightOffset; ++y){	
		//First Pixels of inside Row
		for (x=0; x<xOffset; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
		//Inside Row
		for (; x<srcImageWidth_filterWidthOffset; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImageDataPtr,parameter);
			++dstImageDataPtr;
			++srcImageDataPtr;
		}
		//Last Pixels Inside Row
		for (; x<srcImageWidth; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
		srcImageDataPtr+=filterWidth;
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
