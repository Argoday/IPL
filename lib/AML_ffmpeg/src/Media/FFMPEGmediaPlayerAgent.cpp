
#include "FFMPEGmediaPlayerAgent.h"

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
			,frameRGB(nullptr)
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
		AVFrame         * frameRGB;
		AVPacket          packet;
		int               numBytes;
		unsigned int      videoStreamID;
		bool              hasVideoStream;
		uint8_t         * buffer;
		SwsContext      * img_convert_ctx;

		//Audio Support
		AVCodecContext * aCodecCtx;
		AVCodec        * aCodec;
		unsigned int     audioStreamID;
		bool             hasAudioStream;
};

AML_FFMPEG_DLL_EXPORT FFMPEGmediaPlayerAgent::FFMPEGmediaPlayerAgent(Data::DataManager * const & _dataManager, Concurrency::ISource<Media::Player::ControlPacket> & _controlQueue , Video::Queue::Pipe & _videoPipe, Audio::Queue::Pipe & _audioPipe)
	:dataManager(_dataManager)
	,controlQueue(_controlQueue)
	,videoPipe(_videoPipe)
	,videoDataQueue(_videoPipe.getDataQueue())
	,videoControlQueue(_videoPipe.getControlQueue())
	,audioPipe(_audioPipe)
	,audioDataQueue(_audioPipe.getDataQueue())
	,audioControlQueue(_audioPipe.getControlQueue())
	,flushID(0)
{
	_this = new FFMPEGmediaPlayerAgent_d;
	av_register_all();
	state = State::closed;
}
AML_FFMPEG_DLL_EXPORT FFMPEGmediaPlayerAgent::~FFMPEGmediaPlayerAgent(){
	closeFile();
	sws_freeContext(_this->img_convert_ctx);
	delete _this;
}
AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::sendFlush(){
	++flushID;
	auto dataFlushMessageParameter = new Video::Queue::DataMessageFlushParameter(flushID);
	auto videoDataPacket = Video::Queue::DataPacket(Video::Queue::DataMessageType::flush,dataFlushMessageParameter);
	videoPipe.aboutToSendData();
	Concurrency::asend(videoDataQueue,videoDataPacket);

	auto controlMessageParameter = new Video::Queue::ControlMessageFlushParameter(flushID);
	auto videoControlPacket = Video::Queue::ControlPacket(Video::Queue::ControlMessageType::flush,controlMessageParameter);
	Concurrency::asend(videoControlQueue,videoControlPacket);
}
AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::sendPause(){
	auto videoControlPacket = Video::Queue::ControlPacket(Video::Queue::ControlMessageType::pause);
	Concurrency::asend(videoControlQueue,videoControlPacket);
}
AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::sendPlay(){
	auto videoControlPacket = Video::Queue::ControlPacket(Video::Queue::ControlMessageType::play);
	Concurrency::asend(videoControlQueue,videoControlPacket);
}
AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::sendQuit(){
	auto videoDataPacket = Video::Queue::DataPacket(Video::Queue::DataMessageType::quit);
	Concurrency::asend(videoDataQueue,videoDataPacket);

	auto videoControlPacket = Video::Queue::ControlPacket(Video::Queue::ControlMessageType::quit);
	Concurrency::asend(videoControlQueue,videoControlPacket);
}
AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::run(){
	auto & pCodecCtx  = _this->codecCtx;
	auto & pFrame     = _this->frame;
	auto & pFrameRGB  = _this->frameRGB;
	auto & packet     = _this->packet;

	int frameFinished = 0;
	for(;;){
		
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
			
			Video::Queue::DataPacket videoDataPacket;
			Video::Queue::ControlPacket videoControlPacket;
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
						playPauseParameter = reinterpret_cast<const Media::Player::CommandPlayPauseParameter * const>(controlPacket.getParameter());
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
					openParameter = reinterpret_cast<const Media::Player::CommandOpenParameter * const>(controlPacket.getParameter());
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
				if(packet.stream_index==_this->videoStreamID) {

					avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished,&packet);
      
					if(frameFinished) {
				
						AVRational ratQ;
						ratQ.num = 1;
						ratQ.den = AV_TIME_BASE;
						I8u timeStamp = av_rescale_q(packet.pts,_this->vStream->time_base, ratQ);
						
						AVFrame * frame;
						if(pCodecCtx->pix_fmt!=PIX_FMT_RGB24){
							auto w = pCodecCtx->width;
							auto h = pCodecCtx->height;
							_this->img_convert_ctx = sws_getCachedContext(_this->img_convert_ctx,w, h, pCodecCtx->pix_fmt, w, h, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);
							sws_scale(_this->img_convert_ctx,pFrame->data, pFrame->linesize,0,pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
							frame=pFrameRGB;
						}else{
							frame=pFrame;
						}

						auto & width  = _this->codecCtx->width;
						auto & height = _this->codecCtx->height;

						auto imagePtr = new Image::Image<Pixel::PixelRGBi1u>(width,height,dataManager);
						if(frame->linesize[0]==width*3){
							memcpy(imagePtr->getDataPtr(),frame->data[0],_this->numBytes);
						}else{
							auto dataPtr  = imagePtr->getDataPtr();
							auto framePtr = frame->data[0];
							auto linesize = frame->linesize[0];
							for(int y=0; y<height; y++){
								memcpy(dataPtr,framePtr,linesize);
								dataPtr+=width;
								framePtr+=linesize;
							}
						}
						++frameIndex;
						auto messageParameter = new Video::Queue::DataMessageImageParameter<Pixel::PixelRGBi1u>(imagePtr,timeStamp,frameIndex);
						auto videoPacket = Video::Queue::DataPacket(Video::Queue::DataMessageType::image,messageParameter);
						
						videoPipe.aboutToSendData();
						Concurrency::asend(videoDataQueue,videoPacket);
					}
				}else if(packet.stream_index==_this->audioStreamID) {
					//Concurrency::asend(audioQueue,audioPacket);
				}
			}else{
				//av_read_frame failed?
				closeFile();
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
	auto & videoStreamID  = _this->videoStreamID;
	auto & hasVideoStream = _this->hasVideoStream;
	auto & audioStreamID  = _this->audioStreamID;
	auto & hasAudioStream = _this->hasAudioStream;
	auto & aCodecCtx      = _this->aCodecCtx;
	auto & aCodec         = _this->aCodec;
	frameIndex=0;
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
		pVStream = pFormatCtx->streams[videoStreamID];
		pCodecCtx=pFormatCtx->streams[videoStreamID]->codec;
  
		_this->codec=avcodec_find_decoder(pCodecCtx->codec_id);
		if(_this->codec==NULL) {
			//TODO: ERROR: Unsupported codec
			hasVideoStream=false;
			return false;
		}

		if(avcodec_open2(pCodecCtx, _this->codec, NULL)<0){return false;}
  
		_this->frame=avcodec_alloc_frame();
		if(_this->frame==NULL){return false;}
  
		_this->frameRGB=avcodec_alloc_frame();
		if(_this->frameRGB==NULL){return false;}
  
		_this->numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,pCodecCtx->height);
		_this->buffer = (uint8_t *)av_malloc(_this->numBytes*sizeof(uint8_t));
  
		avpicture_fill((AVPicture *)_this->frameRGB, _this->buffer, PIX_FMT_RGB24,pCodecCtx->width, pCodecCtx->height);
	}
	if(hasAudioStream==true){
		aCodecCtx=pFormatCtx->streams[audioStreamID]->codec;

		aCodec = avcodec_find_decoder(aCodecCtx->codec_id);
		if(!aCodec) {
			//TODO: ERROR Unsupported codec
			hasAudioStream=false;
			return false;
		}
		avcodec_open(aCodecCtx, aCodec);
	}

	return true;
}

AML_FFMPEG_DLL_EXPORT void FFMPEGmediaPlayerAgent::closeFile(){
	if(_this->buffer   !=nullptr){av_free(_this->buffer);               _this->buffer    = nullptr;}
	if(_this->frame    !=nullptr){av_free(_this->frame);                _this->frame     = nullptr;}
	if(_this->frameRGB !=nullptr){av_free(_this->frameRGB);             _this->frameRGB  = nullptr;}
	if(_this->codecCtx !=nullptr){avcodec_close(_this->codecCtx);       _this->codecCtx  = nullptr;}
	if(_this->formatCtx!=nullptr){avformat_close_input(&_this->formatCtx);_this->formatCtx  = nullptr;}
	state = State::closed;
	frameIndex=0;
}

}
