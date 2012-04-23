
#include "MediaPlayer.h"

#include <QtGui/QApplication>

#include <Data/DataManager.h>

#include <Media/FFMPEGmediaPlayerAgent.h>
#include <Media/PlayerControl.h>
#include <Video/ReaderAgent.h>

int main(int argc, char *argv[]){

	Data::DataManager dataManager;

	Concurrency::unbounded_buffer<Media::Player::ControlPacket> controlQueue;
	Video::Queue::Pipe videoPipe(60);
	Audio::Queue::Pipe audioPipe(6000);

	Media::Player::Control mediaControl(controlQueue);

	Media::FFMPEGmediaPlayerAgent mediaPlayerAgent(&dataManager,controlQueue,videoPipe,audioPipe);
	Video::Queue::ReaderAgent videoReaderAgent(videoPipe);

	mediaPlayerAgent.start();
	videoReaderAgent.start();

	QApplication a(argc, argv);
	MediaPlayer w(&dataManager,&mediaControl,&videoReaderAgent);

	w.show();

	I4 ret = a.exec();
	
	mediaControl.quit();

	Concurrency::agent::wait(&mediaPlayerAgent);
	Concurrency::agent::wait(&videoReaderAgent);

	return ret;
}
