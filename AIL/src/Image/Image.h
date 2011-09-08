
#ifndef IMAGE__Image_H
#define IMAGE__Image_H

#include "AIL.h"
#include "ImageBase.h"
#include "ImageSize.h"
#include "ImageView.h"
#include <Meta/Swap.h>

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
		
		ThisType(const ImageSize &_imageSize);
		ThisType(const long &_width,const long &_height);
		ThisType(const ThisType &_image);
		ThisType(ThisType &&_image);

		ThisType(const ImageSize &_imageSize,Data::DataManager * const _dataManager);
		ThisType(const long &_width,const long &_height,Data::DataManager * const _dataManager);

		void setAs(const ThisType &otherImage,const ImageSize &_imageSize);
		const ThisType &operator=(const ThisType &_image);
		const ThisType &operator=(ThisType &&_image);

		~Image();

		__forceinline const ImageSize &getSize() const {return size;}
		__forceinline const long &getWidth()  const {return size.getWidth();}
		__forceinline const long &getHeight() const {return size.getHeight();}

		__forceinline       ImageView<typename PixelType::DataType> &getView()       {return view;}
		__forceinline const ImageView<typename PixelType::DataType> &getView() const {return view;}
		
		__forceinline       PixelType * getDataPtr()       {return dataPtr;}
		__forceinline const PixelType * getDataPtr() const {return dataPtr;}

		__forceinline const PixelType * const &getDataPtrEnd() const {return dataPtrEnd;}

		__forceinline       PixelType &operator()(const long &x,const long &y);
		__forceinline const PixelType &operator()(const long &x,const long &y) const ;

		__forceinline       PixelType &getPixel(const long &x,const long &y);
		__forceinline const PixelType &getPixel(const long &x,const long &y) const ;

		void clip();

	//Save/Load
		//void loadFromFile(const std::string &filePathName); //TODO: Implement
		//void saveToFile  (const std::string &filePathName); //TODO: Implement

	//Operators
		ThisType &operator -=(const typename PixelType::NumberType &value);
		ThisType &operator +=(const typename PixelType::NumberType &value);
		ThisType &operator *=(const typename PixelType::NumberType &value);
		ThisType &operator /=(const typename PixelType::NumberType &value);

		ThisType &operator -=(const PixelType &value);
		ThisType &operator +=(const PixelType &value);
		ThisType &operator *=(const PixelType &value);
		ThisType &operator /=(const PixelType &value);

		ThisType &operator -=(const ThisType &value);
		ThisType &operator +=(const ThisType &value);
		ThisType &operator *=(const ThisType &value);
		ThisType &operator /=(const ThisType &value);
		
		void swap(Image &other){
			Meta::swap(size,other.size);
			Meta::swap(dataPtr,other.dataPtr);
			Meta::swap(dataPtrEnd,other.dataPtrEnd);
			Meta::swap(static_cast<size_t>(dataNumBytes),static_cast<size_t>(other.dataNumBytes));

			Meta::swap(view,other.view);

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

		ImageView<typename PixelType::DataType> view;

		Data::DataManager * const dataManager;

};

template <typename PixelType> PixelType &Image<PixelType>::operator()(const long &x,const long &y) {
	return dataPtr[x+y*size.getWidth()];
}
template <typename PixelType> const PixelType &Image<PixelType>::operator()(const long &x,const long &y) const {
	return dataPtr[x+y*size.getWidth()];
}
template <typename PixelType> PixelType &Image<PixelType>::getPixel(const long &x,const long &y) {
	long tempX=x;if(x<0){tempX=0;}else if(x>=size.getWidth ()){tempX=size.getWidth_1 ();}
	long tempY=y;if(y<0){tempY=0;}else if(y>=size.getHeight()){tempY=size.getHeight_1();}
	return dataPtr[tempX+tempY*size.getWidth()];
}
template <typename PixelType> const PixelType &Image<PixelType>::getPixel(const long &x,const long &y) const {
	long tempX=x;if(x<0){tempX=0;}else if(x>=size.getWidth ()){tempX=size.getWidth_1 ();}
	long tempY=y;if(y<0){tempY=0;}else if(y>=size.getHeight()){tempY=size.getHeight_1();}
	return dataPtr[tempX+tempY*size.getWidth()];
}

}

#endif

