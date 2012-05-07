
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
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	if((srcImage.isSimpleView()==true)||(dstImage.isSimpleView()==true)){
		const auto & srcImageHeight = srcImage.getHeight();
		const auto & srcImageWidth  = srcImage.getWidth();

		const auto & yOffset      = parameter.yOffset;
		const auto & filterHeight = parameter.filterHeight;

		auto srcImageHeight_filterHeightOffset = srcImageHeight - (filterHeight - yOffset - 1);

		auto srcImageDataPtr = srcImage.getDataPtr();
		auto dstImageDataPtr = dstImage.getDataPtr();
		auto dstImageDataPtrRowsEnd = dstImage.getDataPtr() + (srcImageHeight_filterHeightOffset)*srcImageWidth;

		I4 y = 0;
		I4 x = 0;

		//First Rows
		for(;y<yOffset;++y){
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
		for(y=srcImageHeight_filterHeightOffset;y<srcImageHeight;++y){
			for (x=0; x<srcImageWidth; ++x){
				AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
				++dstImageDataPtr;
			}
		}
	}else{
		const auto & srcImageHeight = srcImage.getHeight();
		const auto & srcImageWidth  = srcImage.getWidth();

		const auto & yOffset      = parameter.yOffset;
		const auto & filterHeight = parameter.filterHeight;

		auto srcImageHeight_filterHeightOffset = srcImageHeight - (filterHeight - yOffset - 1);

		auto srcImageDataPtr = srcImage.getDataPtr();
		auto dstImageDataPtr = dstImage.getDataPtr();

		I4 y = 0;
		I4 x = 0;

		if(srcImage.hasYbeginSection()==true){
			//First Rows - Inside Section
			for(y=0;y<yOffset;++y){
				for(x=0;x<srcImageWidth;++x){
					AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
					++dstImageDataPtr;
				}
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
			}
		}else{
			dstImageDataPtr+=yOffset*srcImage.getStride();
		}

		//Inside Rows
		for(y=yOffset;y<srcImageHeight_filterHeightOffset;++y){
			auto dstImageDataPtrRowEnd = dstImageDataPtr + srcImageWidth;
			for(;dstImageDataPtr!=dstImageDataPtrRowEnd;){
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr,parameter);
				++dstImageDataPtr;
				++srcImageDataPtr;
			}
			dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
			srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
		}

		if(srcImage.hasYendSection()==true){
			//Last Rows
			for(y=srcImageHeight_filterHeightOffset;y<srcImageHeight;++y){
				for(x=0;x<srcImageWidth;++x){
					AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
					++dstImageDataPtr;
				}
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
			}
		}
	}

}

};

#endif
