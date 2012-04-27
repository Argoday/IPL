
#include "FFMPEGmediaPlayerAgent.h"

#include <Data/DataManager.h>
#include <Video/Frame.h>
#include <Audio/Frame.h>
#include <Audio/Config.h>
#include <limits.h>

#pragma warning (disable : 4244) // Ignore conversion from 'int64_t' to 'int32_t' - determined safe
#pragma warning (disable : 4005) // Ignore redefinition of macro UINT64_C
extern "C" {
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}
#pragma warning (default : 4244)
#pragma warning (default : 4005)


namespace Media {

class AML_FFMPEG_DLL_EXPORT FFMPEGmediaPlayerAgent::FFMPEGmediaPlayerAgent_d {
	public:
		FFMPEGmediaPlayerAgent_d()
			:formatCtx(nullptr)
			,codecCtx(nullptr)
			,codec(nullptr)
			,frame(nullptr)
			,numBytes(0)
			,videoStreamID(0)
			,hasVideoStream(false)
			,audioStreamID(0)
			,hasAudioStream(false)
			,buffer(nullptr)
			,img_convert_ctx(nullptr)
		{
		}

		//Video Support
		AVFormatContext * formatCtx;
		AVCodecContext  * codecCtx;
		AVCodec         * codec;
		AVStream        * vStream;
		AVFrame         * frame;
		AVPacket          packet;
		int               numBytes;
		unsigned int      videoStreamID;
		bool              hasVideoStream;
		uint8_t         * buffer;
		SwsContext      * img_convert_ctx;

		//Audio Support
		AVCodecContext * aCodecCtx;
		AVCodec        * aCodec;
		AVFrame        * aFrame;
		AVStream       * aStream;
		unsigned int     audioStreamID;
		bool             hasAudioStream;
};

AML_FFMPEG_DLL_EXPORT FFMPEGmediaPlayerAgent::FFMPEGmediaPlayerAgent(Data::DataManager * const & _dataManager, Concurrency::ISource<Media::Player::ControlPacket> & _controlQueue , Thread::Queue::Pipe & _videoPipe, Thread::Queue::Pipe & _audioPipe)
	:dataManager(_dataManager)
	,controlQueue(_controlQueue)
	,videoPipe(_videoPipe)
	,audioPipe(_audioPipe)
	,flushID(0)
{
	_this = new FFMPEGmediaPlayerAgent_d;
	av_register_all();
	state = State::closed;
	_this->buffer    = nullptr;
	_this->frame     = nullptr;
	_this->aFrame    = nullptr;
	_this->codecCtx  = nullptr;
	_this->aCodecCtx = nullptr;
	_this->formatCtx = nullptr;
}
AML_FFMPEG_DLL_EXPORT FFMPEGmediaPlayerAgent::~FFMPEGmediaPlayerAgent(){
	closeFile();
	sws_freeContext(_this->img_convert_ctx);
	delete _this;
}
AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::sendFlush(){
	videoPipe.sendFlush();
	audioPipe.sendFlush();
}
AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::sendPause(){
	videoPipe.sendStop();
	audioPipe.sendStop();
	lastVideoTimeStamp = 0.0;
	lastVideoTimeDelta = 0.0;
	lastAudioTimeStamp = 0.0;
	lastAudioTimeDelta = 0.0;
	resetVideoTime = true;
	resetAudioTime = true;
}
AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::sendPlay(){
	videoPipe.sendStart();
	audioPipe.sendStart();
	lastVideoTimeStamp = 0.0;
	lastVideoTimeDelta = 0.0;
	lastAudioTimeStamp = 0.0;
	lastAudioTimeDelta = 0.0;
	resetVideoTime = true;
	resetAudioTime = true;
}
AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::sendQuit(){
	videoPipe.sendQuit();
	audioPipe.sendQuit();
}
AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::run(){
	auto & pCodecCtx  = _this->codecCtx;
	auto & pACodecCtx = _this->aCodecCtx;
	auto & pFrame     = _this->frame;
	auto & pAFrame    = _this->aFrame;
	auto & packet     = _this->packet;
	auto & hasVideoStream = _this->hasVideoStream;
	auto & hasAudioStream = _this->hasAudioStream;

	int frameFinished = 0;
	lastVideoTimeStamp = 0.0;
	lastVideoTimeDelta = 0.0;
	lastAudioTimeStamp = 0.0;
	lastAudioTimeDelta = 0.0;
	resetVideoTime = true;
	resetAudioTime = true;
	for(;;){
		Concurrency::Context::Yield();
		Media::Player::ControlPacket controlPacket;
		B1 gotControlPacket = false;
		if(state!=State::playing){
			controlPacket = Concurrency::receive(controlQueue);
			gotControlPacket=true;
		}else if(Concurrency::try_receive(controlQueue,controlPacket)==true){
			gotControlPacket=true;
		}
		if(gotControlPacket==true){
			const Media::Player::CommandOpenParameter      * openParameter             = nullptr;
			const Media::Player::CommandPlayPauseParameter * playPauseParameter        = nullptr;
			
			switch(controlPacket.getCommand()){
				case Media::Player::Command::play :
					if((state==State::stopped) || (state==State::paused)){
						state = State::playing;
						sendPlay();
					}
				break;
				case Media::Player::Command::pause :
					if(state==State::playing){
						state = State::paused;
						sendPause();
					}
				break;
				case Media::Player::Command::stop :
					if((state==State::playing)||(state==State::paused)){
						state = State::stopped;
						sendFlush();
						//TODO: Seek to beginning
					}
				break;
				case Media::Player::Command::playPause :
					if(controlPacket.getParameter()!=nullptr){
						playPauseParameter = static_cast<const Media::Player::CommandPlayPauseParameter * const>(controlPacket.getParameter());
						if(playPauseParameter->getState()==true){
							state = State::playing;
							sendPlay();
						}else if(playPauseParameter->getState()==false){
							state = State::paused;
							sendPause();
						}
						delete playPauseParameter;
					}else{
						if(state==State::playing){
							state = State::paused;
							sendPause();
						}else if(state==State::paused){
							state = State::playing;
							sendPlay();
						}
					}
				break;
				case Media::Player::Command::seek :
					sendFlush();

					//TODO: seek?
					sendPlay();
				break;
				case Media::Player::Command::open :
					if(state!=State::closed){
						closeFile();
					}
					sendFlush();
					openParameter = static_cast<const Media::Player::CommandOpenParameter * const>(controlPacket.getParameter());
					if(openFile(openParameter->getFileName())==true){
						if(openParameter->getAutoPlay()==true){
							state = State::playing;
							sendPlay();
						}else{
							state = State::stopped;
							sendPause();
						}
					}
					delete openParameter;
				break;
				case Media::Player::Command::close :
					sendFlush();
					closeFile();
				break;
				case Media::Player::Command::quit :
					sendQuit();
					done();
					return;
				break;
			}
		}
		if(state==State::playing){
			if(av_read_frame(_this->formatCtx, &packet)>=0) {
				if((hasVideoStream==true)&&(packet.stream_index==_this->videoStreamID)){

					auto code = avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished,&packet);
					if(code<0){
						//TODO: Error decoding video
					}else if(frameFinished) {
				
						F8 timeStamp;
						if(pFrame->pkt_pts!=AV_NOPTS_VALUE){
							timeStamp = pFrame->pkt_pts * av_q2d(_this->vStream->time_base);
						}else if(pFrame->pts!=AV_NOPTS_VALUE){
							timeStamp = pFrame->pts * av_q2d(_this->vStream->time_base) / 1000.0;
						}else{
							timeStamp = static_cast<F8>(videoFrameIndex) * av_q2d(_this->vStream->r_frame_rate) / 1000.0;
						}
						F8 timeDelta = timeStamp - lastVideoTimeStamp;

						if(resetVideoTime==false){
							if((timeDelta>0.0)&&(timeDelta<1.0)){
								lastVideoTimeStamp = timeStamp;
								lastVideoTimeDelta = timeDelta;
							}else{
								timeStamp = lastVideoTimeStamp+timeDelta;
							}
						}else{
							resetVideoTime=false;
							lastVideoTimeStamp = timeStamp;
							lastVideoTimeDelta = timeDelta;
						}

						auto width  = pCodecCtx->width;
						auto height = pCodecCtx->height;
						_this->img_convert_ctx = sws_getCachedContext(_this->img_convert_ctx,width, height, pCodecCtx->pix_fmt, width, height, PIX_FMT_RGB24, SWS_FAST_BILINEAR, NULL, NULL, NULL);

						auto imagePtr = new Image::Image<Pixel::PixelRGBi1u>(width,height,dataManager);

						uint8_t * data[AV_NUM_DATA_POINTERS];
						int linesize[AV_NUM_DATA_POINTERS];
						data[0] = static_cast<uint8_t*const>(static_cast<void*const>(imagePtr->getDataPtr()));
						linesize[0] = width*3;
						sws_scale(_this->img_convert_ctx,pFrame->data, pFrame->linesize,0,pCodecCtx->height, data, linesize);

						++videoFrameIndex;
						auto videoFrame  = new Video::Frame<Pixel::PixelRGBi1u>(imagePtr,timeStamp,videoFrameIndex);
						auto videoPacket = Thread::Queue::DataPacket(videoFrame,timeStamp);
						
						videoPipe.asendData(videoPacket);
					}
				}else if((hasAudioStream==true)&&(packet.stream_index==_this->audioStreamID)){
					auto code = avcodec_decode_audio4(pACodecCtx, pAFrame, &frameFinished,&packet);
					if(code<0){
						//TODO: Error decoding audio
					}else if(frameFinished) {
						const int bps = av_get_bytes_per_sample(pACodecCtx->sample_fmt);
						const int decoded_data_size = pAFrame->nb_samples * pACodecCtx->channels * bps;

						F8 timeStamp;
						if(pAFrame->pkt_pts!=AV_NOPTS_VALUE){
							timeStamp = pAFrame->pkt_pts * av_q2d(_this->aStream->time_base);
						}else if(pAFrame->pts!=AV_NOPTS_VALUE){
							timeStamp = pAFrame->pts * av_q2d(_this->aStream->time_base) / 1000.0;
						}else{
							timeStamp = std::numeric_limits<F8>::infinity();
						}
						F8 timeDelta = timeStamp - lastAudioTimeStamp;

						if(resetAudioTime==false){
							if((timeDelta>0.0)&&(timeDelta<1.0)){
								lastAudioTimeStamp = timeStamp;
								lastAudioTimeDelta = timeDelta;
							}else{
								timeStamp = lastAudioTimeStamp+timeDelta;
							}
						}else{
							resetAudioTime=false;
							lastAudioTimeStamp = timeStamp;
							lastAudioTimeDelta = timeDelta;
						}

						auto audioData = new Audio::AudioData(dataManager,decoded_data_size);
						memcpy(audioData->getData(),pAFrame->data[0],decoded_data_size);

						++audioFrameIndex;
						auto audioFrame = new Audio::Frame(audioData,timeStamp,audioFrameIndex);
						auto audioPacket = Thread::Queue::DataPacket(audioFrame,timeStamp);
						
						audioPipe.asendData(audioPacket);
					}
				}
			}else{
				closeFile(); //av_read_frame failed
			}
			av_free_packet(&packet);
		}
	}
	done();
}


AML_FFMPEG_DLL_EXPORT bool FFMPEGmediaPlayerAgent::openFile(const std::string & fileName){
	auto & pFormatCtx     = _this->formatCtx;
	auto & pCodecCtx      = _this->codecCtx;
	auto & pVStream       = _this->vStream;
	auto & pAStream       = _this->aStream;
	auto & videoStreamID  = _this->videoStreamID;
	auto & hasVideoStream = _this->hasVideoStream;
	auto & audioStreamID  = _this->audioStreamID;
	auto & hasAudioStream = _this->hasAudioStream;
	auto & aCodecCtx      = _this->aCodecCtx;
	auto & aCodec         = _this->aCodec;
	videoFrameIndex=0;
	audioFrameIndex=0;
	_this->formatCtx = avformat_alloc_context();

	if(avformat_open_input(&pFormatCtx, fileName.c_str(), NULL, 0)!=0){return false;}
  
	if(avformat_find_stream_info(pFormatCtx,NULL)<0){return false;}
  
	// Find the first audio and video streams
	videoStreamID=0;hasVideoStream=false;
	audioStreamID=0;hasAudioStream=false;
	for(unsigned int i=0; i<pFormatCtx->nb_streams; i++){
		if((pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) && (hasVideoStream==false)) {
			videoStreamID=i;
			hasVideoStream=true;
		}
		if((pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO) && (hasAudioStream==false)) {
			audioStreamID=i;
			hasAudioStream=true;
		}
	}
	/*
	I4 ret = av_find_best_stream(pCodecCtx, AVMEDIA_TYPE_VIDEO, -1, -1, &pFormatCtx, 0);
	if (ret < 0) {
		//TODO: ERROR: Cannot find a video stream in the input file
		return false;
	}
	videoStreamID = ret;
	//*/

	if(hasVideoStream==true){
		pVStream  = pFormatCtx->streams[videoStreamID];
		pCodecCtx = pFormatCtx->streams[videoStreamID]->codec;
  
		_this->codec=avcodec_find_decoder(pCodecCtx->codec_id);
		if(_this->codec==NULL) {
			//TODO: ERROR: Unsupported codec
			hasVideoStream=false;
			return false;
		}

		if(avcodec_open2(pCodecCtx, _this->codec, NULL)<0){return false;}
  
		_this->frame=avcodec_alloc_frame();
		if(_this->frame==NULL){return false;}
  
		_this->numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,pCodecCtx->height);
		_this->buffer = (uint8_t *)av_malloc(_this->numBytes*sizeof(uint8_t));
  
	}
	if(hasAudioStream==true){
		pAStream  = pFormatCtx->streams[audioStreamID];
		aCodecCtx = pFormatCtx->streams[audioStreamID]->codec;

		aCodec = avcodec_find_decoder(aCodecCtx->codec_id);
		if(!aCodec) {
			//TODO: ERROR: Unsupported codec
			hasAudioStream=false;
			return false;
		}
		avcodec_open(aCodecCtx, aCodec);

		_this->aFrame=avcodec_alloc_frame();
		if(_this->aFrame==NULL){return false;}

		auto bps           = av_get_bytes_per_sample(aCodecCtx->sample_fmt);
		auto channels      = aCodecCtx->channels;
		auto sampleRate    = aCodecCtx->sample_rate;
		//auto sampleFormat  = aCodecCtx->sample_fmt;
		//auto channelLayout = aCodecCtx->channel_layout;

		auto audioConfig = new Audio::Config(channels,sampleRate,bps);
		auto audioPacket = Thread::Queue::DataPacket(audioConfig,0,0);
		audioPipe.asendData(audioPacket);

	}
	dataManager->releaseFreeFromPool();
	return true;
}

AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::closeFile(){
	if(_this->buffer   !=nullptr){av_free(_this->buffer);                 _this->buffer    = nullptr;}
	if(_this->frame    !=nullptr){av_free(_this->frame);                  _this->frame     = nullptr;}
	if(_this->aFrame   !=nullptr){av_free(_this->aFrame);                 _this->aFrame    = nullptr;}
	if(_this->codecCtx !=nullptr){avcodec_close(_this->codecCtx);         _this->codecCtx  = nullptr;}
	if(_this->aCodecCtx!=nullptr){avcodec_close(_this->aCodecCtx);        _this->aCodecCtx = nullptr;}
	if(_this->formatCtx!=nullptr){avformat_close_input(&_this->formatCtx);_this->formatCtx = nullptr;}
	state = State::closed;
	videoFrameIndex=0;
	audioFrameIndex=0;
	dataManager->releaseFreeFromPool();
}

}
