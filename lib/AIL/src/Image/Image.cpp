
#include "Image.h"
#include "ImageSize.h"
#include <Pixel/pixel_cast.h>
#include <Algorithm/Algorithm1x1.h>
#include <Meta/Operators.h>
#include <Meta/Assign.h>
#include <Data/DataManager.h>

#include <memory.h> //For: memcpy()

namespace Image {

template <typename PixelType> void Image<PixelType>::resetImageData(){
	if(dataNumBytes==(size.getNumPixels())*sizeof(PixelType)){
		return;
	}
	releaseImageData();
	Meta::assign(static_cast<size_t>(dataNumBytes),(size.getNumPixels())*sizeof(PixelType));
	if(dataManager==nullptr){
		dataPtr = static_cast<PixelType * const>(Data::DataManager::getMemory(dataNumBytes));
	}else{
		dataPtr = static_cast<PixelType * const>(dataManager->getMemoryFromPool(dataNumBytes));
	}
	dataPtrEnd = dataPtr + size.getNumPixels();
	dataView  = ImageView<typename PixelType::DataType>(dataPtr,dataPtrEnd,size);
	pixelView = ImageView<PixelType                   >(dataPtr,dataPtrEnd,size);
}
template <typename PixelType> Image<PixelType>::~Image(){
	releaseImageData();
}
template <typename PixelType> void Image<PixelType>::releaseImageData(){
	if(dataManager==nullptr){
		Data::DataManager::release(static_cast<void *>(dataPtr));
	}else{
		dataManager->releaseFromPool(static_cast<void *>(dataPtr),dataNumBytes);
	}
	dataPtr = nullptr;
	dataPtrEnd = nullptr;
	Meta::assign(static_cast<size_t>(dataNumBytes),0);
}

// --- Constructors ---
template <typename PixelType> Image<PixelType>::Image()
	:size(ImageSize(0,0))
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,dataView(nullptr,nullptr,ImageSize(0,0))
	,pixelView(nullptr,nullptr,ImageSize(0,0))
	,dataManager(nullptr)
{
}
template <typename PixelType> Image<PixelType>::Image(const ImageSize & _imageSize)
	:size(_imageSize)
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,dataView(nullptr,nullptr,ImageSize(0,0))
	,pixelView(nullptr,nullptr,ImageSize(0,0))
	,dataManager(nullptr)
{
	this->resetImageData();
}
template <typename PixelType> Image<PixelType>::Image(const I4 & _width,const I4 & _height)
	:size(_width,_height)
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,dataView(nullptr,nullptr,ImageSize(0,0))
	,pixelView(nullptr,nullptr,ImageSize(0,0))
	,dataManager(nullptr)
{
	this->resetImageData();
}template <typename PixelType> Image<PixelType>::Image(const ImageSize & _imageSize,Data::DataManager * const _dataManager)
	:size(_imageSize)
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,dataView(nullptr,nullptr,ImageSize(0,0))
	,pixelView(nullptr,nullptr,ImageSize(0,0))
	,dataManager(_dataManager)
{
	this->resetImageData();
}
template <typename PixelType> Image<PixelType>::Image(const I4 & _width,const I4 & _height,Data::DataManager * const _dataManager)
	:size(_width,_height)
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,dataView(nullptr,nullptr,ImageSize(0,0))
	,pixelView(nullptr,nullptr,ImageSize(0,0))
	,dataManager(_dataManager)
{
	this->resetImageData();
}
template <typename PixelType> Image<PixelType>::Image(const ThisType & _image)
	:size(_image.size)
	,dataPtr(nullptr)
	,dataPtrEnd(nullptr)
	,dataNumBytes(0)
	,dataView(nullptr,nullptr,ImageSize(0,0))
	,pixelView(nullptr,nullptr,ImageSize(0,0))
	,dataManager(_image.dataManager)
{
	this->resetImageData();
	memcpy(dataPtr,_image.getDataPtr(),size.getNumPixels()*sizeof(PixelType));
}
template <typename PixelType> Image<PixelType>::Image(ThisType && _image)
	:size(_image.size)
	,dataPtr(_image.dataPtr)
	,dataPtrEnd(_image.dataPtrEnd)
	,dataNumBytes(_image.dataNumBytes)
	,dataView(_image.dataView)
	,pixelView(_image.pixelView)
	,dataManager(_image.dataManager)
{
	_image.size = ImageSize(0,0);
	_image.dataPtr    = nullptr;
	_image.dataPtrEnd = nullptr;
	Meta::assign(static_cast<size_t>(_image.dataNumBytes),0);
	_image.dataView  = ImageView<typename PixelType::DataType>(nullptr,nullptr,ImageSize(0,0));
	_image.pixelView = ImageView<PixelType                   >(nullptr,nullptr,ImageSize(0,0));
}
template <typename PixelType> const Image<PixelType> &Image<PixelType>::operator=(ThisType && _image){
	releaseImageData();

	size=_image.size;
	dataPtr=_image.dataPtr;
	dataPtrEnd=_image.dataPtrEnd;
	Meta::assign(static_cast<size_t>(dataNumBytes),_image.dataNumBytes);
	dataView=_image.dataView;
	pixelView=_image.pixelView;
	Meta::assign(const_cast<Data::DataManager *>(dataManager),_image.dataManager);

	_image.size = ImageSize(0,0);
	_image.dataPtr    = nullptr;
	_image.dataPtrEnd = nullptr;
	Meta::assign(static_cast<size_t>(_image.dataNumBytes),0);
	_image.dataView  = ImageView<typename PixelType::DataType>(nullptr,nullptr,ImageSize(0,0));
	_image.pixelView = ImageView<PixelType                   >(nullptr,nullptr,ImageSize(0,0));
	
	return (*this);
}

// --- Copy Image ---
template <typename PixelType> const Image<PixelType> &Image<PixelType>::operator=(const ThisType & _image){
	size=_image.getSize();
	this->resetImageData();
	memcpy(this->getDataPtr(),_image.getDataPtr(),size.getNumPixels()*sizeof(PixelType));
	return (*this);
}
template <typename PixelType> void Image<PixelType>::resize(const I4 & _width,const I4 & _height){
	size = ImageSize(_width,_height);
	this->resetImageData();
}
template <typename PixelType> void Image<PixelType>::resize(const ImageSize & _imageSize){
	size = _imageSize;
	this->resetImageData();
}
template <typename PixelType> void Image<PixelType>::setAs(const ThisViewType & otherView){
	size = otherView.getSize();
	this->resetImageData();
	auto otherImageDataPtr = otherView.getDataPtr();
	auto imageDataPtr = dataPtr;
	auto regionRowSize = size.getWidth()*sizeof(PixelType);
	for (I4 y=0; y<size.getHeight(); ++y){//TODO: Place this in AlgorithmRx1 (row by 1)
		memcpy(imageDataPtr,otherImageDataPtr,regionRowSize);
		otherImageDataPtr+=otherView.getStride();
		imageDataPtr+=size.getWidth();
	}
}

template <typename T> class Clip {
	public:
		static FINLINE void process(typename T::DataType * const &object){typename T::RangeType::clip(*object);}
};

template <typename PixelType> void Image<PixelType>::clip(){
	Algorithm::Algorithm1x1<Clip<PixelType>>(dataView);
}

// --- Operators ---
template <typename PixelType> Image<PixelType> & Image<PixelType>::operator +=(const typename PixelType::NumberType & value){Algorithm::Algorithm1x1p<Meta::AddEq<PixelDataType,typename PixelType::NumberType>>(dataView,value);return (*this);}
template <typename PixelType> Image<PixelType> & Image<PixelType>::operator -=(const typename PixelType::NumberType & value){Algorithm::Algorithm1x1p<Meta::SubEq<PixelDataType,typename PixelType::NumberType>>(dataView,value);return (*this);}
template <typename PixelType> Image<PixelType> & Image<PixelType>::operator *=(const typename PixelType::NumberType & value){Algorithm::Algorithm1x1p<Meta::MulEq<PixelDataType,typename PixelType::NumberType>>(dataView,value);return (*this);}
template <typename PixelType> Image<PixelType> & Image<PixelType>::operator /=(const typename PixelType::NumberType & value){Algorithm::Algorithm1x1p<Meta::DivEq<PixelDataType,typename PixelType::NumberType>>(dataView,value);return (*this);} //TODO: Check for zero

template <typename PixelType> Image<PixelType> & Image<PixelType>::operator +=(const ThisType & value){if(size!=value.getSize()){return (*this);/*TODO: Report an error*/}Algorithm::Algorithm1x1p<Meta::AddEq<PixelDataType,PixelDataType>>(dataView,value.getDataView());return (*this);}
template <typename PixelType> Image<PixelType> & Image<PixelType>::operator -=(const ThisType & value){if(size!=value.getSize()){return (*this);/*TODO: Report an error*/}Algorithm::Algorithm1x1p<Meta::SubEq<PixelDataType,PixelDataType>>(dataView,value.getDataView());return (*this);}
template <typename PixelType> Image<PixelType> & Image<PixelType>::operator *=(const ThisType & value){if(size!=value.getSize()){return (*this);/*TODO: Report an error*/}Algorithm::Algorithm1x1p<Meta::MulEq<PixelDataType,PixelDataType>>(dataView,value.getDataView());return (*this);}
template <typename PixelType> Image<PixelType> & Image<PixelType>::operator /=(const ThisType & value){if(size!=value.getSize()){return (*this);/*TODO: Report an error*/}Algorithm::Algorithm1x1p<Meta::DivEq<PixelDataType,PixelDataType>>(dataView,value.getDataView());return (*this);} //TODO: Check for zero

template <typename PixelType> Image<PixelType> & Image<PixelType>::operator +=(const PixelType & value){Algorithm::Algorithm1x1p<Meta::AddEq<PixelDataType,PixelDataType>>(dataView,value);return (*this);}
template <typename PixelType> Image<PixelType> & Image<PixelType>::operator -=(const PixelType & value){Algorithm::Algorithm1x1p<Meta::SubEq<PixelDataType,PixelDataType>>(dataView,value);return (*this);}
template <typename PixelType> Image<PixelType> & Image<PixelType>::operator *=(const PixelType & value){Algorithm::Algorithm1x1p<Meta::MulEq<PixelDataType,PixelDataType>>(dataView,value);return (*this);}
template <typename PixelType> Image<PixelType> & Image<PixelType>::operator /=(const PixelType & value){Algorithm::Algorithm1x1p<Meta::DivEq<PixelDataType,PixelDataType>>(dataView,value);return (*this);} //TODO: Check for zero

}


#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Image::Image)
