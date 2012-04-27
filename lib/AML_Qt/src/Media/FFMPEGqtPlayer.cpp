
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

FFMPEGqtPlayer::FFMPEGqtPlayer(Data::DataManager * const _dataManager,QAbstractVideoSurface * surface)
	:dataManager(_dataManager)
{
	videoPipe = new Thread::Queue::Pipe(20);
	audioPipe = new Thread::Queue::Pipe(0);

	mediaControl = new Media::Player::Control(controlQueue);

	videoReaderAgent = new Thread::Queue::ReaderAgent(*videoPipe);
	videoQtTarget = new Video::Queue::QtTarget(surface);
	videoReaderAgent->registerTarget(videoQtTarget);

	audioReaderAgent = new Thread::Queue::ReaderAgent(*audioPipe);
	auto audioQtDevice = new Audio::AudioQtDevice();
	audioQtTarget = new Audio::Queue::QtTarget(audioQtDevice);
	audioReaderAgent->registerTarget(audioQtTarget);

	mediaPlayerAgent = new Media::FFMPEGmediaPlayerAgent(dataManager,controlQueue,*videoPipe,*audioPipe);

	mediaPlayerAgent->start();
	videoReaderAgent->start();
	audioReaderAgent->start();
}
FFMPEGqtPlayer::~FFMPEGqtPlayer(){
	mediaControl->quit();
	Concurrency::agent::wait(mediaPlayerAgent);
	Concurrency::agent::wait(videoReaderAgent);
	Concurrency::agent::wait(audioReaderAgent);

	delete videoPipe;
	delete audioPipe;
	delete videoQtTarget;
	delete audioQtTarget;
	delete mediaControl;
	delete videoReaderAgent;
	delete mediaPlayerAgent;
};


}

