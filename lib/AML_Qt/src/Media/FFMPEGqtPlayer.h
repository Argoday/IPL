
#ifndef MEDIA__FFMPEGqtPlayer_H
#define MEDIA__FFMPEGqtPlayer_H

#include "AML_Qt.h"

#include <Data/DataTypes.h>
#include <Image/Image.h>

#include <QtCore/QRect>
#include <QtGui/QImage>
#include <QtMultimedia/QAbstractVideoSurface>
#include <QtMultimedia/QVideoFrame>

#include <Thread/QueuePipe.h>
#include <Thread/QueueReaderAgent.h>
#include <Media/PlayerControl.h>
#include <Video/QueueQtTarget.h>
#include <Audio/QueueQtTarget.h>
#include <Audio/AudioQtDevice.h>
#include <Media/FFMPEGmediaPlayerAgent.h>

namespace Media {

class AML_QT_DLL_EXPORT FFMPEGqtPlayer {
	public:
		FFMPEGqtPlayer(Data::DataManager * const _dataManager,QAbstractVideoSurface * surface);
		Media::Player::Control * getMediaControl(){return mediaControl;}
		~FFMPEGqtPlayer();

	private:
		Data::DataManager * const dataManager;

		Concurrency::unbounded_buffer<Media::Player::ControlPacket> controlQueue;
		Thread::Queue::Pipe * videoPipe;
		Thread::Queue::Pipe * audioPipe;
		Video::Queue::QtTarget * videoQtTarget;
		Audio::Queue::QtTarget * audioQtTarget;
		Media::Player::Control * mediaControl;
		Thread::Queue::ReaderAgent * videoReaderAgent;
		Thread::Queue::ReaderAgent * audioReaderAgent;
		Media::FFMPEGmediaPlayerAgent * mediaPlayerAgent;

};


}

#endif 
