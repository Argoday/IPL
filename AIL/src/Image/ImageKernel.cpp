
#include "ImageKernel.h"
#include <Data/DataManager.h>
#include <Meta/Forward.h>

namespace Image {

template <
	typename PixelType,
	typename InclusionTestType
> ImageKernel<PixelType,InclusionTestType>::ImageKernel(Image<PixelType> &&_kernel)
	:kernel(Meta::forward(_kernel))
	,kernelSkipDataPtr(nullptr)
	,kernelSkipDataPtrEnd(nullptr)
	,kernelSize(0)
	,parentImageWidth(0)
{
}

template <
	typename PixelType,
	typename InclusionTestType
> ImageKernel<PixelType,InclusionTestType>::ImageKernel(Image<PixelType> &&_kernel,const long &_parentImageWidth)
	:kernel(Meta::forward(_kernel))
	,kernelSkipDataPtr(nullptr)
	,kernelSkipDataPtrEnd(nullptr)
	,kernelSize(0)
	,parentImageWidth(0)
{

	//if((_parentImageWidth-kernel.getWidth())<0){ //TODO: Is this really faster/better?
	if(_parentImageWidth<kernel.getWidth()){return;} //TODO: Report an error

	calculateKernelSkipData(_parentImageWidth);
}

template <
	typename PixelType,
	typename InclusionTestType
> ImageKernel<PixelType,InclusionTestType>::~ImageKernel(){
	if(kernelSkipDataPtr!=nullptr){
		Data::DataManager::release(kernelSkipDataPtr);
		kernelSkipDataPtr=nullptr;
	}
	kernelSkipDataPtrEnd=nullptr;
}

template <
	typename PixelType,
	typename InclusionTestType
> void ImageKernel<PixelType,InclusionTestType>::calculateKernelSkipData(const long & _parentImageWidth){
	
	if(parentImageWidth==_parentImageWidth){return;}

	parentImageWidth=_parentImageWidth;

	kernelSize = calculateKernelSize(kernel);

	if(kernelSkipDataPtr!=nullptr){
		Data::DataManager::release(kernelSkipDataPtr);
		kernelSkipDataPtr=nullptr;
	}
	kernelSkipDataPtrEnd=nullptr;

	kernelSkipDataPtr = static_cast<long*>(Data::DataManager::getMemory(sizeof(long) * (kernelSize+2)));
	kernelSkipDataPtrEnd=kernelSkipDataPtr+kernelSize+1;

	long * kernelSkipDataPtrTemp = const_cast<long *>(kernelSkipDataPtr);

	long kernelDataSkipNum = 0;
	long kernelDataCount   = 0;
	for(long y=0; y<kernel.getHeight(); ++y){ //TODO: make this faster
		for(long x=0; x<kernel.getWidth(); ++x){
			if(InclusionTestType::isIncluded(kernel(x,y))==true){
				kernelSkipDataPtrTemp[kernelDataCount] = kernelDataSkipNum;
				++kernelDataCount;
				kernelDataSkipNum=1;
			}else{
				++kernelDataSkipNum;
			}
		}
		kernelDataSkipNum+=parentImageWidth-kernel.getWidth();
	}
	kernelSkipDataPtrTemp[kernelDataCount] = 1;
	//TODO: assert(kernelDataCount==kernelSize);
}

template <
	typename PixelType,
	typename InclusionTestType
> long ImageKernel<PixelType,InclusionTestType>::calculateKernelSize(const Image<PixelType> &image){
	long _kernelSize = 0;
	const PixelType * imageDataPtr = image.getDataPtr();
	for(;imageDataPtr!=image.getDataPtrEnd();){ //TODO: find a good way to put this into Algorithm1x1
		if(InclusionTestType::isIncluded(*imageDataPtr)==true){
			_kernelSize+=1;
		}
		++imageDataPtr;
	}
	return _kernelSize;
}

}

#include <Pixel/PixelTemplateMacros.h>
template class Image::ImageKernel<Pixel::PixelGRAYb,Image::BooleanTestType>;
