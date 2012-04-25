

#ifndef VIDEO__FFMPEGplayer_H
#define VIDEO__FFMPEGplayer_H

#include "AML_ffmpeg.h"
#include <Image/Image.h>

#include <Media/PlayerControlPacket.h>
#include <Video/QueuePipe.h>
#include <Audio/QueuePipe.h>

#include <agents.h>
#include <string>

namespace Media {

class AML_FFMPEG_DLL_EXPORT FFMPEGmediaPlayerAgent : public Concurrency::agent {
	public:
		typedef FFMPEGmediaPlayerAgent ThisType;

		ThisType(Data::DataManager * const & _dataManager, Concurrency::ISource<Media::Player::ControlPacket> & _controlQueue , Video::Queue::Pipe & _videoPipe, Audio::Queue::Pipe & _audioPipe);
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
		I8u frameIndex;
		Data::DataManager * const dataManager;

		Concurrency::ISource<Media::Player::ControlPacket> & controlQueue;

		I8u flushID;
		Video::Queue::Pipe & videoPipe;
		Concurrency::ITarget<Video::Queue::DataPacket>    & videoDataQueue;
		Concurrency::ITarget<Video::Queue::ControlPacket> & videoControlQueue;

		Audio::Queue::Pipe & audioPipe;
		Concurrency::ITarget<Audio::Queue::DataPacket>    & audioDataQueue;
		Concurrency::ITarget<Audio::Queue::ControlPacket> & audioControlQueue;
};
	
}

#endif
