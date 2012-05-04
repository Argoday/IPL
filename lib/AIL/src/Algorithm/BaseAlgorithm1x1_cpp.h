
#ifndef ALGORITHM__BaseAlgorithm1x1_CPP_H
#define ALGORITHM__BaseAlgorithm1x1_CPP_H

#include "BaseAlgorithm1x1.h"
#include <Image/ImageView.h>
#include <Meta/Unroller1.h>
#include <Meta/Unroller1p.h>
#include <Meta/Unroller2.h>

#define UNROLL_COUNT 16 //TODO: make UNROLL_COUNT a constexpr instead of a Macro

namespace Algorithm {

template <
	typename AlgorithmType,
	typename SrcPixelDataType,
	typename DstPixelDataType,
	typename ParameterType
> void BaseAlgorithm1x1p (
	const Image::ImageView<SrcPixelDataType> & srcImage,
	Image::ImageView<DstPixelDataType> & dstImage,
	const ParameterType & parameter)
{
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	if((srcImage.isSimpleView()==true)&&(dstImage.isSimpleView()==true)){
		auto srcImageDataPtr = srcImage.getDataPtr();
		auto dstImageDataPtr = dstImage.getDataPtr();
		
		I4 unrollCount = (dstImage.getSize().getNumPixels() / (I4)UNROLL_COUNT) * (I4)UNROLL_COUNT;
		auto dstImageDataPtrUnrollEnd = dstImage.getDataPtr() + unrollCount;
		for(;dstImageDataPtr!=dstImageDataPtrUnrollEnd;){
			Meta::Unroller2<DstPixelDataType,SrcPixelDataType,AlgorithmType,UNROLL_COUNT>::process(dstImageDataPtr,srcImageDataPtr,parameter);
		}

		auto & dstImageDataPtrEnd = dstImage.getDataPtrEnd();
		for(;dstImageDataPtr!=dstImageDataPtrEnd;){
			AlgorithmType::process(dstImageDataPtr,srcImageDataPtr);
			++dstImageDataPtr;
			++srcImageDataPtr;
		}
	}else{
		auto srcImageDataPtr = srcImage.getDataPtr();
		auto dstImageDataPtr = dstImage.getDataPtr();

		I4 unrollLineCount = (dstImage.getSize().getWidth() / (I4)UNROLL_COUNT) * (I4)UNROLL_COUNT;
		auto lineDiff = (dstImage.getSize().getWidth()-unrollLineCount);
		auto dstImageDataPtrEnd = dstImageDataPtr + unrollLineCount;

		for(I4 y=0; y<dstImage.getSize().getHeight(); ++y){
			for(;dstImageDataPtr!=dstImageDataPtrEnd;){
				Meta::Unroller2<DstPixelDataType,SrcPixelDataType,AlgorithmType,UNROLL_COUNT>::process(dstImageDataPtr,srcImageDataPtr,parameter);
			}
			dstImageDataPtrEnd+=lineDiff;
			for(;dstImageDataPtr!=dstImageDataPtrEnd;){
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr);
				++dstImageDataPtr;
				++srcImageDataPtr;
			}
			dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
			srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
			dstImageDataPtrEnd+=dstImage.getNumPixelsBetweenRows();
			dstImageDataPtrEnd+=unrollLineCount;
		}
	}
}

template <
	typename AlgorithmType,
	typename SrcPixelDataType,
	typename DstPixelDataType
> void BaseAlgorithm1x1(
	const Image::ImageView<SrcPixelDataType> & srcImage,
	Image::ImageView<DstPixelDataType> & dstImage)
{
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	if((srcImage.isSimpleView()==true)&&(dstImage.isSimpleView()==true)){
		auto   srcImageDataPtr = srcImage.getDataPtr();
		auto   dstImageDataPtr = dstImage.getDataPtr();

		I4 unrollCount = (srcImage.getSize().getNumPixels() / (I4)UNROLL_COUNT) * (I4)UNROLL_COUNT;
		auto dstImageDataPtrUnrollEnd = dstImage.getDataPtr() + unrollCount;
		for(;dstImageDataPtr!=dstImageDataPtrUnrollEnd;){
			Meta::Unroller2<DstPixelDataType,SrcPixelDataType,AlgorithmType,UNROLL_COUNT>::process(dstImageDataPtr,srcImageDataPtr);
		}

		auto & dstImageDataPtrEnd = dstImage.getDataPtrEnd();
		for(;dstImageDataPtr!=dstImageDataPtrEnd;){
			AlgorithmType::process(dstImageDataPtr,srcImageDataPtr);
			++dstImageDataPtr;
			++srcImageDataPtr;
		}
	}else{
		auto srcImageDataPtr = srcImage.getDataPtr();
		auto dstImageDataPtr = dstImage.getDataPtr();

		I4 unrollLineCount = (dstImage.getSize().getWidth() / (I4)UNROLL_COUNT) * (I4)UNROLL_COUNT;
		auto lineDiff = (dstImage.getSize().getWidth()-unrollLineCount);
		auto dstImageDataPtrEnd = dstImage.getDataPtr() + unrollLineCount;

		for(I4 y=0; y<dstImage.getSize().getHeight(); ++y){
			for(;dstImageDataPtr!=dstImageDataPtrEnd;){
				Meta::Unroller2<DstPixelDataType,SrcPixelDataType,AlgorithmType,UNROLL_COUNT>::process(dstImageDataPtr,srcImageDataPtr);
			}
			dstImageDataPtrEnd+=lineDiff;
			for(;dstImageDataPtr!=dstImageDataPtrEnd;){
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr);
				++dstImageDataPtr;
				++srcImageDataPtr;
			}
			dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
			srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
			dstImageDataPtrEnd+=dstImage.getNumPixelsBetweenRows();
			dstImageDataPtrEnd+=unrollLineCount;
		}
	}
}

template <
	typename AlgorithmType,
	typename PixelDataType
> void BaseAlgorithm1x1(
	Image::ImageView<PixelDataType> & image)
{
	if(image.isSimpleView()==true){
		I4 unrollCount = (image.getSize().getNumPixels() / (I4)UNROLL_COUNT) * (I4)UNROLL_COUNT;
		auto imageDataPtr = image.getDataPtr();
		auto imageDataPtrUnrollEnd = image.getDataPtr() + unrollCount;
		for(;imageDataPtr!=imageDataPtrUnrollEnd;){
			Meta::Unroller1<PixelDataType,AlgorithmType,UNROLL_COUNT>::process(imageDataPtr);
		}

		auto & imageDataPtrEnd = image.getDataPtrEnd();
		for(;imageDataPtr!=imageDataPtrEnd;){
			AlgorithmType::process(imageDataPtr);
			++imageDataPtr;
		}
	}else{
		auto imageDataPtr = image.getDataPtr();

		I4 unrollLineCount = (image.getSize().getWidth() / (I4)UNROLL_COUNT) * (I4)UNROLL_COUNT;
		auto lineDiff = (image.getSize().getWidth()-unrollLineCount);
		auto imageDataPtrEnd = image.getDataPtr() + unrollLineCount;
		for(I4 y=0; y<image.getSize().getHeight(); ++y){
			for(;imageDataPtr!=imageDataPtrEnd;){
				Meta::Unroller1<PixelDataType,AlgorithmType,UNROLL_COUNT>::process(imageDataPtr);
			}
			imageDataPtrEnd+=lineDiff;
			for(;imageDataPtr!=imageDataPtrEnd;){
				AlgorithmType::process(imageDataPtr);
				++imageDataPtr;
			}
			imageDataPtr+=image.getNumPixelsBetweenRows();
			imageDataPtrEnd+=image.getNumPixelsBetweenRows();
			imageDataPtrEnd+=unrollLineCount;
		}
	}
}

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
> void BaseAlgorithm1x1p(
	Image::ImageView<PixelDataType> & image,
	const ParameterType & parameter)
{
	if(image.isSimpleView()==true){
		auto imageDataPtr = image.getDataPtr();

		I4 unrollCount = (image.getSize().getNumPixels() / (I4)UNROLL_COUNT) * (I4)UNROLL_COUNT;
		auto imageDataPtrUnrollEnd = image.getDataPtr() + unrollCount;
		for(;imageDataPtr!=imageDataPtrUnrollEnd;){
			Meta::Unroller1p<PixelDataType,AlgorithmType,ParameterType,UNROLL_COUNT>::process(imageDataPtr,parameter);
		}

		auto & imageDataPtrEnd = image.getDataPtrEnd();
		for(;imageDataPtr!=imageDataPtrEnd;){
			AlgorithmType::process(imageDataPtr,parameter);
			++imageDataPtr;
		}
	}else{
		auto imageDataPtr = image.getDataPtr();

		I4 unrollLineCount = (image.getSize().getWidth() / (I4)UNROLL_COUNT) * (I4)UNROLL_COUNT;
		auto lineDiff = (image.getSize().getWidth()-unrollLineCount);
		auto imageDataPtrEnd = image.getDataPtr() + unrollLineCount;
		for(I4 y=0; y<image.getSize().getHeight(); ++y){
			for(;imageDataPtr!=imageDataPtrEnd;){
				Meta::Unroller1p<PixelDataType,AlgorithmType,ParameterType,UNROLL_COUNT>::process(imageDataPtr,parameter);
			}
			imageDataPtrEnd+=lineDiff;
			for(;imageDataPtr!=imageDataPtrEnd;){
				AlgorithmType::process(imageDataPtr,parameter);
				++imageDataPtr;
			}
			imageDataPtr+=image.getNumPixelsBetweenRows();
			imageDataPtrEnd+=image.getNumPixelsBetweenRows();
			imageDataPtrEnd+=unrollLineCount;
		}
	}
}

template <
	typename AlgorithmType,
	typename PixelDataType
> void BaseAlgorithm1x1p(
	Image::ImageView<PixelDataType> & srcImage,
	const Image::ImageView<PixelDataType> & parameterImage)
{
	if(srcImage.getSize()!=parameterImage.getSize()){return;}

	if((srcImage.isSimpleView()==true)&&(parameterImage.isSimpleView()==true)){
		auto srcImageDataPtr       = srcImage.getDataPtr();
		auto parameterImageDataPtr = parameterImage.getDataPtr();

		I4 unrollCount = (srcImage.getSize().getNumPixels() / (I4)UNROLL_COUNT) * (I4)UNROLL_COUNT;
		auto srcImageDataPtrUnrollEnd = srcImage.getDataPtr() + unrollCount;
		for(;srcImageDataPtr!=srcImageDataPtrUnrollEnd;){
			Meta::Unroller2<PixelDataType,PixelDataType,AlgorithmType,UNROLL_COUNT>::process(srcImageDataPtr,parameterImageDataPtr);
		}

		auto srcImageDataPtrEnd = srcImage.getDataPtrEnd();
		for(;srcImageDataPtr!=srcImageDataPtrEnd;){
			AlgorithmType::process(srcImageDataPtr,parameterImageDataPtr);
			++parameterImageDataPtr;
			++srcImageDataPtr;
		}
	}else{
		auto srcImageDataPtr       = srcImage.getDataPtr();
		auto parameterImageDataPtr = parameterImage.getDataPtr();

		I4 unrollLineCount = (srcImage.getSize().getWidth() / (I4)UNROLL_COUNT) * (I4)UNROLL_COUNT;
		auto lineDiff = (srcImage.getSize().getWidth()-unrollLineCount);
		auto srcImageDataPtrEnd = srcImage.getDataPtr() + unrollLineCount;
		for(I4 y=0; y<srcImage.getSize().getHeight(); ++y){
			for(;srcImageDataPtr!=srcImageDataPtrEnd;){
				Meta::Unroller2<PixelDataType,PixelDataType,AlgorithmType,UNROLL_COUNT>::process(srcImageDataPtr,parameterImageDataPtr);
			}
			srcImageDataPtrEnd+=lineDiff;
			for(;srcImageDataPtr!=srcImageDataPtrEnd;){
				AlgorithmType::process(srcImageDataPtr,parameterImageDataPtr);
				++parameterImageDataPtr;
				++srcImageDataPtr;
			}
			parameterImageDataPtr+=parameterImage.getNumPixelsBetweenRows();
			srcImageDataPtrEnd+=srcImage.getNumPixelsBetweenRows();
			srcImageDataPtrEnd+=unrollLineCount;
		}
	}
}

};

#endif
