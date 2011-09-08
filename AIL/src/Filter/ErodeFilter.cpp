
#include "ErodeFilter.h"
#include "MinFilterWxH.h"
#include "MinFilterWx1basic.h"
#include "MinFilter1xHbasic.h"
#include "MorphFilterAlgorithm.h"
#include <Algorithm/BaseAlgorithm3x3.h>
#include <Paint/Cross.h>
#include <Paint/Circle.h>

namespace Filter {

template <
	typename PixelType
> void ErodeFilter<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {
	if(type==MorphKernelType::getCross()){
		this->applyToCross(srcImage,dstImage);
	}else if(type==MorphKernelType::getSquare()){
		this->applyToSquare(srcImage,dstImage);
	}else if(type==MorphKernelType::getCircle()){
		this->applyToCircle(srcImage,dstImage);
	}else if(type==MorphKernelType::getDiamond()){
		this->applyToDiamond(srcImage,dstImage);
	}
}

template <
	typename PixelType
> void ErodeFilter<PixelType>::applyToCross(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {
	MinFilterWxH<PixelType> minFilter(Paint::MakeCross(iterations,iterations));
	minFilter.applyTo(srcImage,dstImage);
}

template <
	typename PixelType
> void ErodeFilter<PixelType>::applyToSquare(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {
	Image::Image<PixelType> tempImage(dstImage.getSize(),dstImage.getDataManager());

	MinFilterWx1basic<PixelType> minFilter1(iterations);
	minFilter1.applyTo(srcImage,tempImage);
	
	MinFilter1xHbasic<PixelType> minFilter2(iterations);
	minFilter2.applyTo(tempImage,dstImage);
}

template <
	typename PixelType
> void ErodeFilter<PixelType>::applyToCircle(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {
	MinFilterWxH<PixelType> minFilter(Paint::MakeCircle(iterations,iterations,iterations/2));
	minFilter.applyTo(srcImage,dstImage);
}

template <
	typename PixelType
> void ErodeFilter<PixelType>::applyToDiamond(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {

	typedef typename PixelType::DataType PixelDataType;

	if(iterations==0){return;}
	Algorithm::BaseAlgorithm3x3<ErodeAlgorithm3x3Cross<PixelDataType>,PixelDataType>(srcImage.getView(),dstImage.getView());
	if(iterations==1){return;}

	Image::Image<PixelType> tempImage(dstImage.getSize(),dstImage.getDataManager());

	bool flip=false;

	Algorithm::BaseAlgorithm3x3<ErodeAlgorithm3x3Cross<PixelDataType>,PixelDataType>(dstImage.getView(),tempImage.getView());
	if(iterations==2){
		dstImage.swap(tempImage);
		return;
	}
	long x=2;

	if(iterations%2!=1){
		Algorithm::BaseAlgorithm3x3<ErodeAlgorithm3x3Cross<PixelDataType>,PixelDataType>(tempImage.getView(),dstImage.getView());
		if(iterations==3){return;}
		++x;
	}else{
		flip=true;
	}

	for(;x<=iterations;++x){
		if(flip==false){
			Algorithm::BaseAlgorithm3x3<ErodeAlgorithm3x3Cross<PixelDataType>,PixelDataType>(dstImage.getView(),tempImage.getView());
			flip=true;
		}else if(flip==true){
			Algorithm::BaseAlgorithm3x3<ErodeAlgorithm3x3Cross<PixelDataType>,PixelDataType>(tempImage.getView(),dstImage.getView());
			flip=false;
		}
	}
}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::ErodeFilter)
