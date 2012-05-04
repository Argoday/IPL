
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

	const auto & srcImageHeight = srcImage.getHeight();
	const auto & srcImageWidth  = srcImage.getWidth();

	const auto & xOffset     = parameter.xOffset;
	const auto & filterWidth = parameter.filterWidth;

	auto srcImageWidth_filterWidthOffset = srcImageWidth - (filterWidth - xOffset);

	auto srcImageDataPtr = srcImage.getDataPtr();
	auto dstImageDataPtr = dstImage.getDataPtr();
	auto dstImageDataPtrRowEnd = dstImage.getDataPtr() + srcImageWidth_filterWidthOffset;

	I4 y = 0;
	I4 x = 0;

	for (;y<srcImageHeight;++y){
		//First Pixels of Row
		for (x=0;x<xOffset;++x){
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
		for (x=srcImageWidth_filterWidthOffset;x<srcImageWidth;++x){
			AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
			++dstImageDataPtr;
		}
		dstImageDataPtrRowEnd+=srcImageWidth;
		srcImageDataPtr+=filterWidth;
	}

}

};

#endif
