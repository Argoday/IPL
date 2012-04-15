
#include "FFMPEGplayer.h"

extern "C" {
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

namespace Video {

class AIL_FFMPEG_DLL_EXPORT FFMPEGplayer_d {
	public:
		FFMPEGplayer_d()
			:formatCtx(nullptr)
			,codecCtx(nullptr)
			,codec(nullptr)
			,frame(nullptr)
			,frameRGB(nullptr)
			,numBytes(0)
			,buffer(nullptr)
		{
		}

		AVFormatContext * formatCtx;
		AVCodecContext  * codecCtx;
		AVCodec         * codec;
		AVFrame         * frame; 
		AVFrame         * frameRGB;
		AVPacket        packet;
		int             numBytes;
		int             videoStreamID;
		uint8_t         *buffer;

};

AIL_FFMPEG_DLL_EXPORT FFMPEGplayer::FFMPEGplayer(Data::DataManager * const dataManager)
	:dataManager(dataManager)
	,frameIndex(0)
{
	_this = new FFMPEGplayer_d;
	av_register_all();
	_this->formatCtx = avformat_alloc_context();
}
AIL_FFMPEG_DLL_EXPORT FFMPEGplayer::~FFMPEGplayer(){
	closeFile();
	avformat_free_context(_this->formatCtx);
	delete _this;
}
AIL_FFMPEG_DLL_EXPORT bool FFMPEGplayer::hasNextFrame(){
	auto & pCodecCtx  = _this->codecCtx;
	auto & pFrame     = _this->frame;
	auto & pFrameRGB  = _this->frameRGB;
	auto & packet     = _this->packet;

	int frameFinished=0;
	while(av_read_frame(_this->formatCtx, &packet)>=0) {
		if(packet.stream_index==_this->videoStreamID) {

			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished,&packet);
      
			if(frameFinished) {
				static struct SwsContext * img_convert_ctx;
				auto w = pCodecCtx->width;
				auto h = pCodecCtx->height;
				img_convert_ctx = sws_getContext(w, h, pCodecCtx->pix_fmt, w, h, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);
				sws_scale(img_convert_ctx,pFrame->data, pFrame->linesize,0,pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);

				++frameIndex;
				return true;
			}
		}
    
		av_free_packet(&packet);
	}
	return false;
}


AIL_FFMPEG_DLL_EXPORT bool FFMPEGplayer::openFile(std::string fileName){
	auto & pFormatCtx    = _this->formatCtx;
	auto & pCodecCtx     = _this->codecCtx;
	auto & videoStreamID = _this->videoStreamID;
	frameIndex = 0;

	if(avformat_open_input(&pFormatCtx, fileName.c_str(), NULL, 0)!=0){return false;}
  
	if(av_find_stream_info(pFormatCtx)<0){return false;}
  
	// Find the first video stream
	videoStreamID=-1;
	for(int i=0; i<pFormatCtx->nb_streams; i++){
		if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
			videoStreamID=i;
			break;
		}
	}
	if(videoStreamID==-1){
		//TODO: ERROR: No Video Stream Found
		return false;
	}
  
	pCodecCtx=pFormatCtx->streams[videoStreamID]->codec;
  
	_this->codec=avcodec_find_decoder(pCodecCtx->codec_id);
	if(_this->codec==NULL) {
		//TODO: ERROR: Unsupported codec
		return false;
	}

	if(avcodec_open(pCodecCtx, _this->codec)<0){return false;}
  
	_this->frame=avcodec_alloc_frame();
  
	_this->frameRGB=avcodec_alloc_frame();
	if(_this->frameRGB==NULL){return false;}
  
	_this->numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,pCodecCtx->height);
	_this->buffer = (uint8_t *)av_malloc(_this->numBytes*sizeof(uint8_t));
  
	// Assign appropriate parts of buffer to image planes in pFrameRGB
	// Note that pFrameRGB is an AVFrame, but AVFrame is a superset of AVPicture
	avpicture_fill((AVPicture *)_this->frameRGB, _this->buffer, PIX_FMT_RGB24,pCodecCtx->width, pCodecCtx->height);

	return true;
}

AIL_FFMPEG_DLL_EXPORT void FFMPEGplayer::closeFile(){
	frameIndex = 0;
	if(_this->buffer   !=nullptr){av_free(_this->buffer);               _this->buffer    = nullptr;}
	if(_this->frame    !=nullptr){av_free(_this->frame);                _this->frame     = nullptr;}
	if(_this->frameRGB !=nullptr){av_free(_this->frameRGB);             _this->frameRGB  = nullptr;}
	if(_this->codecCtx !=nullptr){avcodec_close(_this->codecCtx);       _this->codecCtx  = nullptr;}
	if(_this->formatCtx!=nullptr){av_close_input_file(_this->formatCtx);_this->formatCtx = nullptr;}
}

AIL_FFMPEG_DLL_EXPORT Image::Image<Pixel::PixelRGBi1u> FFMPEGplayer::getFrame() const {
	
	auto & pFrame = _this->frameRGB;
	auto & width  = _this->codecCtx->width;
	auto & height = _this->codecCtx->height;

	Image::Image<Pixel::PixelRGBi1u> image(width,height,dataManager);
	if(pFrame->linesize[0]==width*3){
		memcpy(image.getDataPtr(),pFrame->data[0],_this->numBytes);
	}else{
		auto dataPtr  = image.getDataPtr();
		auto framePtr = pFrame->data[0];
		auto linesize = pFrame->linesize[0];
		for(int y=0; y<height; y++){
			memcpy(dataPtr,framePtr,linesize);
			dataPtr+=width;
			framePtr+=linesize;
		}
	}
	return image;
}

}
