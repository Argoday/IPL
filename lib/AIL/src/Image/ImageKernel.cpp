
#include "ImageKernel.h"
#include <Data/DataManager.h>
#include <Meta/Forward.h>

namespace Image {

template <
	typename PixelType,
	typename InclusionTestType
> ImageKernel<PixelType,InclusionTestType>::ImageKernel(Image<PixelType> && _kernel)
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
> ImageKernel<PixelType,InclusionTestType>::ImageKernel(Image<PixelType> && _kernel,const I4 & _parentImageWidth)
	:kernel(Meta::forward(_kernel))
	,kernelSkipDataPtr(nullptr)
	,kernelSkipDataPtrEnd(nullptr)
	,kernelSize(0)
	,parentImageWidth(0)
{
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
> void ImageKernel<PixelType,InclusionTestType>::calculateKernelSkipData(const I4 & _parentImageWidth){
	
	if(parentImageWidth==_parentImageWidth){return;}

	parentImageWidth=_parentImageWidth;

	kernelSize = calculateKernelSize(kernel);

	if(kernelSkipDataPtr!=nullptr){
		Data::DataManager::release(kernelSkipDataPtr);
		kernelSkipDataPtr=nullptr;
	}
	kernelSkipDataPtrEnd=nullptr;

	kernelSkipDataPtr = static_cast<I4*>(Data::DataManager::getMemory(sizeof(I4) * (kernelSize+2)));
	kernelSkipDataPtrEnd=kernelSkipDataPtr+kernelSize+1;

	auto kernelSkipDataPtrTemp = const_cast<I4 *>(kernelSkipDataPtr);

	I4 kernelDataSkipNum = 0;
	I4 kernelDataCount   = 0;
	auto dataPtr = kernel.getDataPtr();
	for(I4 y=0; y<kernel.getHeight(); ++y){ //TODO: make this faster
		for(I4 x=0; x<kernel.getWidth(); ++x){
			if(InclusionTestType::isIncluded(*dataPtr)==true){
				kernelSkipDataPtrTemp[kernelDataCount] = kernelDataSkipNum;
				++kernelDataCount;
				kernelDataSkipNum=1;
			}else{
				++kernelDataSkipNum;
			}
			++dataPtr;
		}
		kernelDataSkipNum+=parentImageWidth-kernel.getWidth();
	}
	kernelSkipDataPtrTemp[kernelDataCount] = 1;
	//TODO: assert(kernelDataCount==kernelSize);
}

template <
	typename PixelType,
	typename InclusionTestType
> I4 ImageKernel<PixelType,InclusionTestType>::calculateKernelSize(const Image<PixelType> & image){
	I4 _kernelSize = 0;
	auto imageDataPtr = image.getDataPtr();
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
template class Image::ImageKernel<Pixel::PixelYb1,Pixel::BooleanTestType>;
