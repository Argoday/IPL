

#ifndef VIDEO__FFMPEGplayer_H
#define VIDEO__FFMPEGplayer_H

#include "AML_ffmpeg.h"
#include <Image/Image.h>

#include <Media/PlayerControlPacket.h>
#include <Thread/QueuePipe.h>
#include <Thread/QueueReaderAgentTarget.h>

#include <agents.h>
#include <string>

namespace Media {

class AML_FFMPEG_DLL_EXPORT FFMPEGmediaPlayerAgent : public Concurrency::agent {
	public:
		typedef FFMPEGmediaPlayerAgent ThisType;

		FFMPEGmediaPlayerAgent(Data::DataManager * const & _dataManager,Concurrency::ISource<Media::Player::ControlPacket> & _controlQueue,Thread::Queue::Pipe & _videoPipe,Thread::Queue::Pipe & _audioPipe);
		~FFMPEGmediaPlayerAgent();

	protected:
		void run();

	private:

		enum class State {
			playing,
			paused,
			stopped,
			closed,
		};

		bool openFile(const std::string & fileName);
		void closeFile();
		Image::Image<Pixel::PixelRGBi1u> getFrame() const ;

		void sendFlush();
		void sendPause();
		void sendPlay();
		void sendQuit();

		class FFMPEGmediaPlayerAgent_d;
		FFMPEGmediaPlayerAgent_d * _this;

		State state;
		I8u videoFrameIndex;
		I8u audioFrameIndex;

		F8 lastVideoTimeStamp;
		F8 lastVideoTimeDelta;
		F8 lastAudioTimeStamp;
		F8 lastAudioTimeDelta;
		B1 resetVideoTime;
		B1 resetAudioTime;

		Data::DataManager * const dataManager;

		Concurrency::ISource<Media::Player::ControlPacket> & controlQueue;

		I8u flushID;
		Thread::Queue::Pipe & videoPipe;
		Thread::Queue::Pipe & audioPipe;
};
	
}

#endif
