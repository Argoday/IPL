
#include "QueueQtTarget.h"

#include <Data/DataTypes.h>
#include <Audio/Frame.h>
#include <Audio/Config.h>

#include <QtCore/QMetaType>

namespace Audio {

namespace Queue {

void AAL_QT_DLL_EXPORT QtTarget::init(){
	qRegisterMetaType<I8u>("I8u");
	qRegisterMetaType<AudioData *>("AudioData *");
}

void AAL_QT_DLL_EXPORT QtTarget::release(Audio::Frame * data){
	data->release();
	delete data;
}
void AAL_QT_DLL_EXPORT QtTarget::release(Audio::Config * data){
	delete data;
}
void AAL_QT_DLL_EXPORT QtTarget::release(void * data){
	if(data!=nullptr){
		release(static_cast<Audio::Frame * >(data));
	}
}
void AAL_QT_DLL_EXPORT QtTarget::send(void * data){
	auto frame = static_cast<Audio::Frame * >(data);
	auto audioData = frame->takeData();

	if(QMetaObject::invokeMethod(device, "presentData", Qt::QueuedConnection, Q_ARG(AudioData *, audioData))==false){
		//TODO: ERROR
		int error=0;
	}
	release(frame);
}
void AAL_QT_DLL_EXPORT QtTarget::config(void * data){
	auto frame = static_cast<Audio::Config * >(data);
	if(QMetaObject::invokeMethod(device, "config", Qt::QueuedConnection, Q_ARG(I8u, frame->getChannels()),Q_ARG(I8u, frame->getFrequency()),Q_ARG(I8u, frame->getSampleSize()))==false){
		//TODO: ERROR
		int error=0;
	}
	release(frame);
}
void AAL_QT_DLL_EXPORT QtTarget::start(){
	if(QMetaObject::invokeMethod(device, "start", Qt::QueuedConnection)==false){
		//TODO: ERROR
		int error=0;
	}
}
void AAL_QT_DLL_EXPORT QtTarget::stop(){
	if(QMetaObject::invokeMethod(device, "stop", Qt::QueuedConnection)==false){
		//TODO: ERROR
		int error=0;
	}
}


}

}
