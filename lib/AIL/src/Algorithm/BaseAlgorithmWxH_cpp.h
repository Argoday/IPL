
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
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	if((srcImage.isSimpleView()==true)&&(dstImage.isSimpleView()==true)){
		auto srcImageHeight = srcImage.getHeight();
		auto srcImageWidth  = srcImage.getWidth();

		const auto & xOffset = parameter.xOffset;
		const auto & yOffset = parameter.yOffset;
	
		const auto & filterWidth  = parameter.filterWidth;
		const auto & filterHeight = parameter.filterHeight;

		auto srcImageWidth_filterWidthOffset   = srcImageWidth  - (filterWidth  - xOffset - 1);
		auto srcImageHeight_filterHeightOffset = srcImageHeight - (filterHeight - yOffset - 1);

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
	}else{
		auto srcImageHeight = srcImage.getHeight();
		auto srcImageWidth  = srcImage.getWidth();

		auto srcImageStride = srcImage.getStride();
		auto dstImageStride = dstImage.getStride();

		const auto & xOffset = parameter.xOffset;
		const auto & yOffset = parameter.yOffset;
	
		const auto & filterWidth = parameter.filterWidth;

		const auto & filterWidth_1  = parameter.filterWidth - 1;
		const auto & filterHeight_1 = parameter.filterHeight - 1;

		auto srcImageWidth_filterWidthOffset   = srcImageWidth  - (filterWidth_1  - xOffset);
		auto srcImageHeight_filterHeightOffset = srcImageHeight - (filterHeight_1 - yOffset);

		auto srcImageDataPtr = srcImage.getDataPtr();
		auto dstImageDataPtr = dstImage.getDataPtr();

		I4 y = 0; // TODO: Write these loops to reduce use of x and y
		I4 x = 0;

		if(srcImage.hasYbeginSection()==true){
			if(srcImage.hasXbeginSection()==true){
				//First Rows - First Section
				for(y=0;y<yOffset;++y){
					for(x=0; x<xOffset; ++x){
						AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
						++dstImageDataPtr;
					}
					dstImageDataPtr+=dstImage.getStride() - xOffset;
				}
			}
			dstImageDataPtr = dstImage.getDataPtr() + xOffset;
			//First Rows - Inside Section
			for(y=0;y<yOffset;++y){
				for(x=xOffset; x<srcImageWidth_filterWidthOffset; ++x){
					AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
					++dstImageDataPtr;
				}
				dstImageDataPtr+=filterWidth_1;
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
			}

			if(srcImage.hasXendSection()==true){
				dstImageDataPtr = dstImage.getDataPtr() + srcImageWidth_filterWidthOffset;
				//First Rows - Last Section
				for(y=0;y<yOffset;++y){
					for(x=srcImageWidth_filterWidthOffset; x<srcImageWidth; ++x){
						AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
						++dstImageDataPtr;
					}
					dstImageDataPtr+=dstImageStride - filterWidth_1 + xOffset;
				}
			}
		}

		dstImageDataPtr=dstImage.getDataPtr() + yOffset*srcImageStride;

		auto dstImageDataPtrRowEnd = dstImageDataPtr + srcImageWidth_filterWidthOffset;

		if((srcImage.hasXbeginSection()==false)&&(srcImage.hasXendSection()==false)){
			for(y=yOffset;y<srcImageHeight_filterHeightOffset;++y){
				dstImageDataPtr+=xOffset;
				//Inside Row
				for(x=xOffset;x<srcImageWidth_filterWidthOffset;++x){
					AlgorithmType::process(dstImageDataPtr,srcImageDataPtr,parameter);
					++dstImageDataPtr;
					++srcImageDataPtr;
				}
				dstImageDataPtr+=(filterWidth_1 - xOffset);
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();

				srcImageDataPtr+=filterWidth_1;
				srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
			}
		}else if((srcImage.hasXbeginSection()==true)&&(srcImage.hasXendSection()==false)){
			for(y=yOffset;y<srcImageHeight_filterHeightOffset;++y){	
				//First Pixels of inside Row
				for(x=0;x<xOffset; ++x){
					AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
					++dstImageDataPtr;
				}
				//Inside Row
				for(;x<srcImageWidth_filterWidthOffset;++x){
					AlgorithmType::process(dstImageDataPtr,srcImageDataPtr,parameter);
					++dstImageDataPtr;
					++srcImageDataPtr;
				}
				dstImageDataPtr+=(filterWidth_1 - xOffset);
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();

				srcImageDataPtr+=filterWidth_1;
				srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
			}
		}else if((srcImage.hasXbeginSection()==false)&&(srcImage.hasXendSection()==true)){
			for(y=yOffset;y<srcImageHeight_filterHeightOffset;++y){	
				dstImageDataPtr+=xOffset;
				//Inside Row
				for(;dstImageDataPtr!=dstImageDataPtrRowEnd;){
					AlgorithmType::process(dstImageDataPtr,srcImageDataPtr,parameter);
					++dstImageDataPtr;
					++srcImageDataPtr;
				}
				//Last Pixels of Row
				for(x=srcImageWidth_filterWidthOffset;x<srcImageWidth;++x){
					AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
					++dstImageDataPtr;
				}
				dstImageDataPtrRowEnd+=dstImageStride;
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();

				srcImageDataPtr+=filterWidth_1;
				srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
			}
		}else{
			for(y=yOffset;y<srcImageHeight_filterHeightOffset;++y){	
				//First Pixels of inside Row
				for(x=0;x<xOffset; ++x){
					AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
					++dstImageDataPtr;
				}
				//Inside Row
				for(;x<srcImageWidth_filterWidthOffset;++x){
					AlgorithmType::process(dstImageDataPtr,srcImageDataPtr,parameter);
					++dstImageDataPtr;
					++srcImageDataPtr;
				}
				//Last Pixels Inside Row
				for(;x<srcImageWidth;++x){
					AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
					++dstImageDataPtr;
				}
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();

				srcImageDataPtr+=filterWidth;
				srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
			}
		}

		if(srcImage.hasYendSection()==true){
			auto dstImageDataPtrRowsEnd = dstImageDataPtr;
			if(srcImage.hasXbeginSection()==true){
				//First Rows - First Section
				for(y=srcImageHeight_filterHeightOffset;y<srcImageHeight;++y){
					for(x=0; x<xOffset; ++x){
						AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
						++dstImageDataPtr;
					}
					dstImageDataPtr+=dstImageStride - xOffset;
				}
			}
			dstImageDataPtr=dstImageDataPtrRowsEnd+xOffset;
			//Last Rows - Inside Section
			for(y=srcImageHeight_filterHeightOffset;y<srcImageHeight;++y){
				for(x=xOffset;x<srcImageWidth_filterWidthOffset; ++x){
					AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
					++dstImageDataPtr;
				}
				dstImageDataPtr+=filterWidth_1;
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
			}
			dstImageDataPtr=dstImageDataPtrRowsEnd + srcImageWidth_filterWidthOffset;
			if(srcImage.hasXendSection()==true){
				//Last Rows - Last Section
				for(y=srcImageHeight_filterHeightOffset;y<srcImageHeight;++y){
					for(x=srcImageWidth_filterWidthOffset; x<srcImageWidth; ++x){
						AlgorithmType::process(dstImageDataPtr,srcImage,parameter,x,y);
						++dstImageDataPtr;
					}
					dstImageDataPtr+=dstImageStride - (filterWidth_1 - xOffset);
				}
			}
		}

	}

}

};

#endif
