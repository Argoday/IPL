
#ifndef VIDEO__QUEUE_DataMessage_H
#define VIDEO__QUEUE_DataMessage_H

#include "AVL.h"
#include <Image/Image.h>

namespace Video {

namespace Queue {

enum class AVL_DLL_EXPORT DataMessageType {
	none,
	image, // Image::Image<PixelType> image, I8u timeStamp, I4 frameIndex
	flush, // I8u flushID
	quit
};

class AVL_DLL_EXPORT DataMessageParameter {
	public:
		typedef DataMessageParameter ThisType;
		virtual void releaseParameter() = 0 ;
};

class AVL_DLL_EXPORT MessageDefaultParameter : public DataMessageParameter {
	public:
		typedef MessageDefaultParameter ThisType;
		ThisType(const ThisType & other){}
		ThisType(ThisType && other){}
		ThisType(){}
		void releaseParameter() {}
};
class AVL_DLL_EXPORT DataMessageFlushParameter : public DataMessageParameter {
	public:
		typedef DataMessageFlushParameter ThisType;
		ThisType(const ThisType & other):flushID(other.flushID){}
		ThisType(ThisType && other){
			flushID=other.flushID;
		}
		ThisType(const I8u & _flushID):flushID(_flushID){}

		const I8u & getFlushID() const {return flushID;}

		void releaseParameter() {}
	private:
		I8u flushID;
};
template<typename PixelType> class AVL_DLL_EXPORT DataMessageImageParameter : public DataMessageParameter {
	public:
		typedef DataMessageImageParameter ThisType;
		ThisType(const ThisType & other):image(other.image),timeStamp(other.timeStamp){}
		ThisType(ThisType && other){
			image=(other.image);
			timeStamp=other.timeStamp;
		}
		ThisType(Image::Image<PixelType> * const & _image,const I8u & _timeStamp,const I8u & _frameIndex):image(_image),timeStamp(_timeStamp),frameIndex(_frameIndex){}

		Image::Image<PixelType> * takeImage() {
			Image::Image<PixelType> * tempImage = image;
			image = nullptr;
			return tempImage;
		}

		const Image::Image<PixelType> * const & getImage() const {return image;}
		const I8u & getTimeStamp()  const {return timeStamp ;}
		const I8u & getFrameIndex() const {return frameIndex;}

		void releaseParameter() {if(image!=nullptr){delete image;image=nullptr;}}
	private:
		Image::Image<PixelType> * image;
		I8u timeStamp;
		I8u frameIndex;
};

}

}

#endif 
