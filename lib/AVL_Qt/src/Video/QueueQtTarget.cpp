
#include "QueueQtTarget.h"

#include <Data/DataTypes.h>
#include <Video/Frame.h>
#include <Video/Config.h>

#include <QMetaType>

namespace Video {

namespace Queue {

void AVL_QT_DLL_EXPORT QtTarget::init(){
	qRegisterMetaType<I8u>("I8u");
	qRegisterMetaType<Image::Image<Pixel::PixelRGBi1u> *>("Image::Image<Pixel::PixelRGBi1u> *");
}

void AVL_QT_DLL_EXPORT QtTarget::release(Video::Frame<Pixel::PixelRGBi1u> * data){
	data->release();
	delete data;
}
void AVL_QT_DLL_EXPORT QtTarget::release(Video::Config * data){
	delete data;
}
void AVL_QT_DLL_EXPORT QtTarget::release(void * data){
	if(data!=nullptr){
		release(static_cast<Video::Frame<Pixel::PixelRGBi1u> * >(data));
	}
}
void AVL_QT_DLL_EXPORT QtTarget::send(void * data){
	auto frame = static_cast<Video::Frame<Pixel::PixelRGBi1u> * >(data);
	auto image = frame->takeImage();
	auto frameIndex = frame->getFrameIndex();

	if(QMetaObject::invokeMethod(surface, "renderFrame", Qt::QueuedConnection, Q_ARG(Image::Image<Pixel::PixelRGBi1u> *, image), Q_ARG(I8u, frameIndex))==false){
		//TODO: ERROR
		int error=0;
	}
	release(frame);
}

void AVL_QT_DLL_EXPORT QtTarget::config(void * data){
	auto frame = static_cast<Video::Config * >(data);
	if(QMetaObject::invokeMethod(surface, "config", Qt::QueuedConnection, Q_ARG(I8u, frame->getDurationFrames()))==false){
		//TODO: ERROR
		int error=0;
	}
	release(frame);
}

}

}
