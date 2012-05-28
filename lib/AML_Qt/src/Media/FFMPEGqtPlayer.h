
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
		FFMPEGqtPlayer(Data::DataManager * const _dataManager);
		~FFMPEGqtPlayer();

		void start(QAbstractVideoSurface * surface);
		void stop();

		Media::Player::Control * getMediaControl(){return mediaControl.get();}

	private:
		Data::DataManager * const dataManager;

		Concurrency::unbounded_buffer<Media::Player::ControlPacket> controlQueue;
		std::unique_ptr<Thread::Queue::Pipe> videoPipe;
		std::unique_ptr<Thread::Queue::Pipe> audioPipe;
		std::unique_ptr<Video::Queue::QtTarget> videoQtTarget;
		std::unique_ptr<Audio::Queue::QtTarget> audioQtTarget;
		std::unique_ptr<Media::Player::Control> mediaControl;
		std::unique_ptr<Thread::Queue::ReaderAgent> videoReaderAgent;
		std::unique_ptr<Thread::Queue::ReaderAgent> audioReaderAgent;
		std::unique_ptr<Media::FFMPEGmediaPlayerAgent> mediaPlayerAgent;

};


}

#endif 
