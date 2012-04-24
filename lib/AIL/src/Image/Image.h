
#ifndef IMAGE__Image_H
#define IMAGE__Image_H

#include "AIL.h"
#include "ImageBase.h"
#include "ImageSize.h"
#include "ImageView.h"
#include <Meta/Swap.h>
#include "Data/DataTypes.h"

namespace Data {
	class DataManager;
}

namespace Image {

template <
	typename PixelType
> class AIL_DLL_EXPORT Image
	: public ImageBase
{

		typedef typename PixelType::DataType PixelDataType;
		typedef Image<PixelType> ThisType;

	public:
		
		ThisType();
		ThisType(const ImageSize & _imageSize);
		ThisType(const I4 & _width,const I4 & _height);
		ThisType(const ThisType & _image);
		ThisType(ThisType && _image);

		ThisType(const ImageSize & _imageSize,Data::DataManager * const _dataManager);
		ThisType(const I4 & _width,const I4 & _height,Data::DataManager * const _dataManager);

		void setAs(const ThisType & otherImage,const ImageSize & _imageSize);
		const ThisType & operator=(const ThisType & _image);
		const ThisType & operator=(ThisType && _image);

		~Image();

		__forceinline const ImageSize & getSize() const {return size;}
		__forceinline const I4 & getWidth()  const {return size.getWidth();}
		__forceinline const I4 & getHeight() const {return size.getHeight();}

		__forceinline const size_t & getNumBytes() const {return dataNumBytes;}

		__forceinline       ImageView<typename PixelType::DataType> & getDataView()       {return dataView;}
		__forceinline const ImageView<typename PixelType::DataType> & getDataView() const {return dataView;}

		__forceinline       ImageView<PixelType> & getPixelView()       {return pixelView;}
		__forceinline const ImageView<PixelType> & getPixelView() const {return pixelView;}

		__forceinline       PixelType * getDataPtr()       {return dataPtr;}
		__forceinline const PixelType * getDataPtr() const {return dataPtr;}

		__forceinline const PixelType * const & getDataPtrEnd() const {return dataPtrEnd;}

		__forceinline       PixelType & operator()(const I4 &x,const I4 &y);
		__forceinline const PixelType & operator()(const I4 &x,const I4 &y) const ;

		__forceinline       PixelType & getPixel(const I4 &x,const I4 &y);
		__forceinline const PixelType & getPixel(const I4 &x,const I4 &y) const ;

		void clip();

	//Operators
		ThisType & operator -=(const typename PixelType::NumberType & value);
		ThisType & operator +=(const typename PixelType::NumberType & value);
		ThisType & operator *=(const typename PixelType::NumberType & value);
		ThisType & operator /=(const typename PixelType::NumberType & value);

		ThisType & operator -=(const PixelType & value);
		ThisType & operator +=(const PixelType & value);
		ThisType & operator *=(const PixelType & value);
		ThisType & operator /=(const PixelType & value);

		ThisType & operator -=(const ThisType & value);
		ThisType & operator +=(const ThisType & value);
		ThisType & operator *=(const ThisType & value);
		ThisType & operator /=(const ThisType & value);
		
		void swap(Image & other){
			Meta::swap(size,other.size);
			Meta::swap(dataPtr,other.dataPtr);
			Meta::swap(dataPtrEnd,other.dataPtrEnd);
			Meta::swap(static_cast<size_t>(dataNumBytes),static_cast<size_t>(other.dataNumBytes));

			Meta::swap(dataView,other.dataView);
			Meta::swap(pixelView,other.pixelView);

			Meta::swap(const_cast<Data::DataManager *>(dataManager),const_cast<Data::DataManager *>(other.dataManager));
		}
		
		Data::DataManager * const getDataManager() const {return dataManager;};

	private:

		__forceinline void resetImageData();
		__forceinline void releaseImageData();

		ImageSize size;
		PixelType * dataPtr;
		const PixelType * dataPtrEnd;
		const size_t dataNumBytes;

		ImageView<typename PixelType::DataType> dataView;
		ImageView<PixelType                   > pixelView;

		Data::DataManager * const dataManager;

};

template <typename PixelType> PixelType & Image<PixelType>::operator()(const I4 & x,const I4 & y) {
	return dataPtr[x+y*size.getWidth()];
}
template <typename PixelType> const PixelType & Image<PixelType>::operator()(const I4 & x,const I4 & y) const {
	return dataPtr[x+y*size.getWidth()];
}
template <typename PixelType> PixelType & Image<PixelType>::getPixel(const I4 & x,const I4 & y) {
	I4 tempX=x;if(x<0){tempX=0;}else if(x>=size.getWidth ()){tempX=size.getWidth_1 ();}
	I4 tempY=y;if(y<0){tempY=0;}else if(y>=size.getHeight()){tempY=size.getHeight_1();}
	return dataPtr[tempX+tempY*size.getWidth()];
}
template <typename PixelType> const PixelType & Image<PixelType>::getPixel(const I4 & x,const I4 & y) const {
	I4 tempX=x;if(x<0){tempX=0;}else if(x>=size.getWidth ()){tempX=size.getWidth_1 ();}
	I4 tempY=y;if(y<0){tempY=0;}else if(y>=size.getHeight()){tempY=size.getHeight_1();}
	return dataPtr[tempX+tempY*size.getWidth()];
}

}

#endif

