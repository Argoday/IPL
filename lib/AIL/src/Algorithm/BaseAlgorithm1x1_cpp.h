
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
	const Image::ImageView<SrcPixelDataType> &srcImage,
	Image::ImageView<DstPixelDataType> &dstImage,
	const ParameterType &parameter)
{
	if((srcImage.isSimpleView()==false)||(dstImage.isSimpleView()==false)){return;} // TODO: implement the other cases
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	auto   srcImageDataPtr = srcImage.getDataPtr();
	auto   dstImageDataPtr = dstImage.getDataPtr();
	auto & dstImageDataPtrEnd = dstImage.getDataPtrEnd();

	long unrollCount = dstImage.getSize().getNumPixels() / (long)UNROLL_COUNT;
	auto dstImageDataPtrUnrollEnd = dstImage.getDataPtr() + (unrollCount * UNROLL_COUNT);
	for(;dstImageDataPtr!=dstImageDataPtrUnrollEnd;){
		Meta::Unroller2<DstPixelDataType,SrcPixelDataType,AlgorithmType,UNROLL_COUNT>::process(dstImageDataPtr,srcImageDataPtr,parameter);
	}

	for(;dstImageDataPtr!=dstImageDataPtrEnd;){
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr);
		++dstImageDataPtr;
		++srcImageDataPtr;
	}
}

template <
	typename AlgorithmType,
	typename SrcPixelDataType,
	typename DstPixelDataType
>
	void BaseAlgorithm1x1(
		const Image::ImageView<SrcPixelDataType> &srcImage,
		Image::ImageView<DstPixelDataType> &dstImage)
	{
	if((srcImage.isSimpleView()==false)||(dstImage.isSimpleView()==false)){return;} // TODO: implement the other cases
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	auto   srcImageDataPtr = srcImage.getDataPtr();
	auto   dstImageDataPtr = dstImage.getDataPtr();
	auto & dstImageDataPtrEnd = dstImage.getDataPtrEnd();

	long unrollCount = srcImage.getSize().getNumPixels() / (long)UNROLL_COUNT;
	auto dstImageDataPtrUnrollEnd = dstImage.getDataPtr() + (unrollCount * UNROLL_COUNT);
	for(;dstImageDataPtr!=dstImageDataPtrUnrollEnd;){
		Meta::Unroller2<DstPixelDataType,SrcPixelDataType,AlgorithmType,UNROLL_COUNT>::process(dstImageDataPtr,srcImageDataPtr);
	}

	for(;dstImageDataPtr!=dstImageDataPtrEnd;){
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr);
		++dstImageDataPtr;
		++srcImageDataPtr;
	}
}

template <
	typename AlgorithmType,
	typename PixelDataType
>
	void BaseAlgorithm1x1(
		Image::ImageView<PixelDataType> &image)
	{

	auto   imageDataPtr = image.getDataPtr();
	auto & imageDataPtrEnd = image.getDataPtrEnd();

	long unrollCount = image.getSize().getNumPixels() / (long)UNROLL_COUNT;
	auto imageDataPtrUnrollEnd = image.getDataPtr() + (unrollCount * UNROLL_COUNT);
	for(;imageDataPtr!=imageDataPtrUnrollEnd;){
		Meta::Unroller1<PixelDataType,AlgorithmType,UNROLL_COUNT>::process(imageDataPtr);
	}

	for(;imageDataPtr!=imageDataPtrEnd;){
		AlgorithmType::process(imageDataPtr);
		++imageDataPtr;
	}
}

template <
	typename AlgorithmType,
	typename PixelDataType,
	typename ParameterType
>
	void BaseAlgorithm1x1p(
		Image::ImageView<PixelDataType> &image,
		const ParameterType &parameter)
	{

	PixelDataType * imageDataPtr = image.getDataPtr();
	const PixelDataType * const &imageDataPtrEnd = image.getDataPtrEnd();

	long unrollCount = image.getSize().getNumPixels() / (long)UNROLL_COUNT;
	const PixelDataType * const imageDataPtrUnrollEnd = image.getDataPtr() + (unrollCount * UNROLL_COUNT);
	for(;imageDataPtr!=imageDataPtrUnrollEnd;){
		Meta::Unroller1p<PixelDataType,AlgorithmType,ParameterType,UNROLL_COUNT>::process(imageDataPtr,parameter);
	}

	for(;imageDataPtr!=imageDataPtrEnd;){
		AlgorithmType::process(imageDataPtr,parameter);
		++imageDataPtr;
	}
}

template <
	typename AlgorithmType,
	typename PixelDataType
>
	void BaseAlgorithm1x1p(
		Image::ImageView<PixelDataType> &srcImage,
		const Image::ImageView<PixelDataType> &parameterImage)
	{
	if(srcImage.getSize()!=parameterImage.getSize()){return;}

	PixelDataType * srcImageDataPtr = srcImage.getDataPtr();
	const PixelDataType * parameterImageDataPtr = parameterImage.getDataPtr();
	const PixelDataType * const &parameterImageDataPtrEnd = parameterImage.getDataPtrEnd();

	long unrollCount = srcImage.getSize().getNumPixels() / (long)UNROLL_COUNT;
	const PixelDataType * const srcImageDataPtrUnrollEnd = srcImage.getDataPtr() + (unrollCount * UNROLL_COUNT);
	for(;srcImageDataPtr!=srcImageDataPtrUnrollEnd;){
		Meta::Unroller2<PixelDataType,PixelDataType,AlgorithmType,UNROLL_COUNT>::process(srcImageDataPtr,parameterImageDataPtr);
	}

	for(;parameterImageDataPtr!=parameterImageDataPtrEnd;){
		AlgorithmType::process(srcImageDataPtr,parameterImageDataPtr);
		++parameterImageDataPtr;
		++srcImageDataPtr;
	}
}

};

#endif
