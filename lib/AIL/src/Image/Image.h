
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
	public:

		typedef typename PixelType::DataType PixelDataType;
		typedef Image<PixelType> ThisType;
		typedef ImageView<PixelType> ThisViewType;
		
		Image();
		Image(const ImageSize & _imageSize);
		Image(const I4 & _width,const I4 & _height);
		Image(const ThisType & _image);
		Image(ThisType && _image);

		Image(const ImageSize & _imageSize,Data::DataManager * const _dataManager);
		Image(const I4 & _width,const I4 & _height,Data::DataManager * const _dataManager);

		void resize(const I4 & _width,const I4 & _height);
		void resize(const ImageSize & _imageSize);
		void setAs(const ThisViewType & otherView);

		const ThisType & operator=(const ThisType & _image);
		const ThisType & operator=(ThisType && _image);

		~Image();

		FINLINE const ImageSize & getSize() const {return size;}
		FINLINE const I4 & getWidth()  const {return size.getWidth();}
		FINLINE const I4 & getHeight() const {return size.getHeight();}

		FINLINE const size_t & getNumBytes() const {return dataNumBytes;}

		FINLINE       ImageView<typename PixelType::DataType> & getDataView()       {return dataView;}
		FINLINE const ImageView<typename PixelType::DataType> & getDataView() const {return dataView;}

		FINLINE       ImageView<PixelType> & getPixelView()       {return pixelView;}
		FINLINE const ImageView<PixelType> & getPixelView() const {return pixelView;}

		FINLINE       PixelType * getDataPtr()       {return dataPtr;}
		FINLINE const PixelType * getDataPtr() const {return dataPtr;}

		FINLINE const PixelType * const & getDataPtrEnd() const {return dataPtrEnd;}

		FINLINE       PixelType & operator()(const I4 &x,const I4 &y);
		FINLINE const PixelType & operator()(const I4 &x,const I4 &y) const ;

		FINLINE       PixelType & getPixel(const I4 &x,const I4 &y);
		FINLINE const PixelType & getPixel(const I4 &x,const I4 &y) const ;

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

		FINLINE void resetImageData();
		FINLINE void releaseImageData();

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

