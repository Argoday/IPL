
#include "QueueQtTarget.h"

#include <Data/DataTypes.h>
#include <Video/Frame.h>

#include <QMetaType>

namespace Video {

namespace Queue {

void AVL_QT_DLL_EXPORT QtTarget::init(){
	qRegisterMetaType<I8u>("I8u");
	qRegisterMetaType<Image::Image<Pixel::PixelRGBi1u> *>("Image::Image<Pixel::PixelRGBi1u> *");
}

void AVL_QT_DLL_EXPORT QtTarget::release(Video::Frame<Pixel::PixelRGBi1u> * data){
	data->release();
}
void AVL_QT_DLL_EXPORT QtTarget::release(void * data){
	if(data!=nullptr){
		release(reinterpret_cast<Video::Frame<Pixel::PixelRGBi1u> * >(data));
	}
}
void AVL_QT_DLL_EXPORT QtTarget::send(void * data){
	auto frame = reinterpret_cast<Video::Frame<Pixel::PixelRGBi1u> * >(data);
	auto image = frame->takeImage();
	auto frameIndex = frame->getFrameIndex();

	if(QMetaObject::invokeMethod(surface, "renderFrame", Qt::QueuedConnection, Q_ARG(Image::Image<Pixel::PixelRGBi1u> *, image), Q_ARG(I8u, frameIndex))==false){
		//TODO: ERROR
	}
	release(frame);
}


}

}
