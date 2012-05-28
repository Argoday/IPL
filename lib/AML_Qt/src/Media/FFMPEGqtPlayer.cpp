
#include "FFMPEGqtPlayer.h"

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

FFMPEGqtPlayer::FFMPEGqtPlayer(Data::DataManager * const _dataManager)
	:dataManager(_dataManager)
{
}
void FFMPEGqtPlayer::start(QAbstractVideoSurface * surface){
	videoPipe = Meta::make_unique<Thread::Queue::Pipe>(20);
	audioPipe = Meta::make_unique<Thread::Queue::Pipe>(0);

	mediaControl = Meta::make_unique<Media::Player::Control>(controlQueue);

	videoReaderAgent = Meta::make_unique<Thread::Queue::ReaderAgent>(*videoPipe);
	videoQtTarget = Meta::make_unique<Video::Queue::QtTarget>(surface);
	videoReaderAgent->registerTarget(videoQtTarget.get());

	audioReaderAgent = Meta::make_unique<Thread::Queue::ReaderAgent>(*audioPipe);
	audioQtTarget = Meta::make_unique<Audio::Queue::QtTarget>();
	audioReaderAgent->registerTarget(audioQtTarget.get());

	mediaPlayerAgent = Meta::make_unique<Media::FFMPEGmediaPlayerAgent>(dataManager,controlQueue,*videoPipe,*audioPipe);

	mediaPlayerAgent->start();
	videoReaderAgent->start();
	audioReaderAgent->start();
}
void FFMPEGqtPlayer::stop(){
	mediaControl->quit();
	Concurrency::agent::wait(mediaPlayerAgent.get());
	Concurrency::agent::wait(videoReaderAgent.get());
	Concurrency::agent::wait(audioReaderAgent.get());
};
FFMPEGqtPlayer::~FFMPEGqtPlayer(){
	stop();
}

}

