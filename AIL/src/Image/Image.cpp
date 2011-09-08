
#include "Image.h"
#include "ImageSize.h"
#include <Pixel/pixel_cast.h>
#include <Algorithm/BaseAlgorithm1x1.h>
#include <Meta/Operators.h>
#include <Meta/Assign.h>
#include <Data/DataManager.h>
#include <memory.h> //For: memcpy()

//#pragma warning( disable : 4213 ) //Note: disable non-standard extension warning for performing a const_cast on an l-value

namespace Image {

template <typename PixelType> void Image<PixelType>::resetImageData(){
	if(dataNumBytes==(size.getNumPixels()+1)*sizeof(PixelType)){
		return;
	}
	releaseImageData();
	Meta::assign(static_cast<size_t>(dataNumBytes),(size.getNumPixels()+1)*sizeof(PixelType));
	if(dataManager==nullptr){
		dataPtr = static_cast<PixelType * const>(Data::DataManager::getMemory(dataNumBytes));
	}else{
		dataPtr = static_cast<PixelType * const>(dataManager->getMemoryFromPool(dataNumBytes));
	}
	dataPtrEnd = dataPtr + size.getNumPixels();
	view = ImageView<typename PixelType::DataType>(dataPtr,dataPtrEnd,size);
}
template <typename PixelType> Image<PixelType>::~Image(){
	releaseImageData();
}
template <typename PixelType> void Image<PixelType>::releaseImageData(){
	if(dataPtr!=nullptr){
		if(dataManager==nullptr){
			Data::DataManager::release(static_cast<void*>(dataPtr));
		}else{
			dataManager->releaseFromPool(static_cast<void*>(dataPtr));
		}
		dataPtr = nullptr;
	}
	dataPtrEnd = nullptr;
}

// --- Constructors ---
template <typename PixelType> Image<PixelType>::Image(const ImageSize &_imageSize)
	:size(_imageSize)
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,view(nullptr,nullptr,ImageSize(0,0))
	,dataManager(nullptr)
{
	this->resetImageData();
}
template <typename PixelType> Image<PixelType>::Image(const long &_width,const long &_height)
	:size(_width,_height)
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,view(nullptr,nullptr,ImageSize(0,0))
	,dataManager(nullptr)
{
	this->resetImageData();
}template <typename PixelType> Image<PixelType>::Image(const ImageSize &_imageSize,Data::DataManager * const _dataManager)
	:size(_imageSize)
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,view(nullptr,nullptr,ImageSize(0,0))
	,dataManager(_dataManager)
{
	this->resetImageData();
}
template <typename PixelType> Image<PixelType>::Image(const long &_width,const long &_height,Data::DataManager * const _dataManager)
	:size(_width,_height)
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,view(nullptr,nullptr,ImageSize(0,0))
	,dataManager(_dataManager)
{
	this->resetImageData();
}
template <typename PixelType> Image<PixelType>::Image(const ThisType &_image)
	:size(_image.size)
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,view(nullptr,nullptr,ImageSize(0,0))
	,dataManager(_image.dataManager)
{
	this->resetImageData();
	memcpy(dataPtr,_image.getDataPtr(),size.getNumPixels()*sizeof(PixelType)); //TODO: Is there something faster than memcpy()?
}
template <typename PixelType> Image<PixelType>::Image(ThisType &&_image)
	:size(_image.size)
	,dataPtr(_image.dataPtr)
	,dataPtrEnd(_image.dataPtrEnd)
	,dataNumBytes(_image.dataNumBytes)
	,view(_image.view)
	,dataManager(_image.dataManager)
{
	_image.size = ImageSize(0,0);
	_image.dataPtr    = nullptr;
	_image.dataPtrEnd = nullptr;
	Meta::assign(static_cast<size_t>(_image.dataNumBytes),0);
	_image.view = ImageView<typename PixelType::DataType>(nullptr,nullptr,ImageSize(0,0));
}
template <typename PixelType> const Image<PixelType> &Image<PixelType>::operator=(ThisType &&_image){
	releaseImageData();

	size=_image.size;
	dataPtr=_image.dataPtr;
	dataPtrEnd=_image.dataPtrEnd;
	Meta::assign(static_cast<size_t>(dataNumBytes),_image.dataNumBytes);
	view=_image.view;
	Meta::assign(const_cast<Data::DataManager *>(dataManager),_image.dataManager);

	_image.size = ImageSize(0,0);
	_image.dataPtr    = nullptr;
	_image.dataPtrEnd = nullptr;
	Meta::assign(static_cast<size_t>(_image.dataNumBytes),0);
	_image.view = ImageView<typename PixelType::DataType>(nullptr,nullptr,ImageSize(0,0));
	
	return (*this);
}

// --- Copy Image ---
template <typename PixelType> const Image<PixelType> &Image<PixelType>::operator=(const ThisType &_image){
	size=_image.getSize();
	this->resetImageData();
	memcpy(this->getDataPtr(),_image.getDataPtr(),size.getNumPixels()*sizeof(PixelType));
	return (*this);
}
//Set this as otherImage at imageSize
template <typename PixelType> void Image<PixelType>::setAs(const ThisType &otherImage,const ImageSize &_imageSize){
	size=_imageSize;
	this->resetImageData();
	const PixelType *otherImageDataPtr = otherImage.getDataPtr();
	PixelType *imageDataPtr = dataPtr;
	long regionRowSize = size.getWidth()*sizeof(PixelType);
	for (long y=0; y<size.getHeight(); ++y){
		memcpy(imageDataPtr,otherImageDataPtr,regionRowSize);
		otherImageDataPtr+=otherImage.getWidth();		
	}
}

template <typename T> class Clip {
	public:
		static __forceinline void process(typename T::DataType * const &object){typename T::RangeType::clip(*object);}
};

template <typename PixelType> void Image<PixelType>::clip(){
	Algorithm::BaseAlgorithm1x1<Clip<PixelType>>(view);
}

// --- Operators ---
template <typename PixelType> Image<PixelType> &Image<PixelType>::operator +=(const typename PixelType::NumberType &value){Algorithm::BaseAlgorithm1x1p<Meta::AddEq<PixelDataType,typename PixelType::NumberType>>(view,value);return (*this);}
template <typename PixelType> Image<PixelType> &Image<PixelType>::operator -=(const typename PixelType::NumberType &value){Algorithm::BaseAlgorithm1x1p<Meta::SubEq<PixelDataType,typename PixelType::NumberType>>(view,value);return (*this);}
template <typename PixelType> Image<PixelType> &Image<PixelType>::operator *=(const typename PixelType::NumberType &value){Algorithm::BaseAlgorithm1x1p<Meta::MulEq<PixelDataType,typename PixelType::NumberType>>(view,value);return (*this);}
template <typename PixelType> Image<PixelType> &Image<PixelType>::operator /=(const typename PixelType::NumberType &value){Algorithm::BaseAlgorithm1x1p<Meta::DivEq<PixelDataType,typename PixelType::NumberType>>(view,value);return (*this);} //TODO: Check for zero

template <typename PixelType> Image<PixelType> &Image<PixelType>::operator +=(const ThisType &value){if(size!=value.getSize()){return (*this);/*TODO: Report an error*/}Algorithm::BaseAlgorithm1x1p<Meta::AddEq<PixelDataType,PixelDataType>>(view,value.getView());return (*this);}
template <typename PixelType> Image<PixelType> &Image<PixelType>::operator -=(const ThisType &value){if(size!=value.getSize()){return (*this);/*TODO: Report an error*/}Algorithm::BaseAlgorithm1x1p<Meta::SubEq<PixelDataType,PixelDataType>>(view,value.getView());return (*this);}
template <typename PixelType> Image<PixelType> &Image<PixelType>::operator *=(const ThisType &value){if(size!=value.getSize()){return (*this);/*TODO: Report an error*/}Algorithm::BaseAlgorithm1x1p<Meta::MulEq<PixelDataType,PixelDataType>>(view,value.getView());return (*this);}
template <typename PixelType> Image<PixelType> &Image<PixelType>::operator /=(const ThisType &value){if(size!=value.getSize()){return (*this);/*TODO: Report an error*/}Algorithm::BaseAlgorithm1x1p<Meta::DivEq<PixelDataType,PixelDataType>>(view,value.getView());return (*this);} //TODO: Check for zero

template <typename PixelType> Image<PixelType> &Image<PixelType>::operator +=(const PixelType &value){Algorithm::BaseAlgorithm1x1p<Meta::AddEq<PixelDataType,PixelDataType>>(view,value);return (*this);}
template <typename PixelType> Image<PixelType> &Image<PixelType>::operator -=(const PixelType &value){Algorithm::BaseAlgorithm1x1p<Meta::SubEq<PixelDataType,PixelDataType>>(view,value);return (*this);}
template <typename PixelType> Image<PixelType> &Image<PixelType>::operator *=(const PixelType &value){Algorithm::BaseAlgorithm1x1p<Meta::MulEq<PixelDataType,PixelDataType>>(view,value);return (*this);}
template <typename PixelType> Image<PixelType> &Image<PixelType>::operator /=(const PixelType &value){Algorithm::BaseAlgorithm1x1p<Meta::DivEq<PixelDataType,PixelDataType>>(view,value);return (*this);} //TODO: Check for zero

}


#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Image::Image)
