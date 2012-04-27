
#include "FFMPEGvideoFile.h"

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

namespace Video {

class AVL_FFMPEG_DLL_EXPORT FFMPEGvideoFile::FFMPEGvideoFile_d {
	public:
		FFMPEGvideoFile_d()
			:formatCtx(nullptr)
			,codecCtx(nullptr)
			,codec(nullptr)
			,frame(nullptr)
			,numBytes(0)
			,img_convert_ctx(nullptr)
		{
		}

		AVFormatContext * formatCtx;
		AVCodecContext  * codecCtx;
		AVCodec         * codec;
		AVFrame         * frame; 
		AVPacket          packet;
		int               numBytes;
		unsigned int      videoStreamID;
		SwsContext      * img_convert_ctx;

};

AVL_FFMPEG_DLL_EXPORT FFMPEGvideoFile::FFMPEGvideoFile(Data::DataManager * const & dataManager)
	:dataManager(dataManager)
	,frameIndex(0)
{
	_this = new FFMPEGvideoFile_d;
	av_register_all();
	_this->formatCtx       = avformat_alloc_context();
	_this->frame           = nullptr;
	_this->codecCtx        = nullptr;
	_this->img_convert_ctx = nullptr;
}
AVL_FFMPEG_DLL_EXPORT FFMPEGvideoFile::~FFMPEGvideoFile(){
	closeFile();
	if(_this->img_convert_ctx!=nullptr){sws_freeContext(_this->img_convert_ctx);}
	delete _this;
}
AVL_FFMPEG_DLL_EXPORT bool FFMPEGvideoFile::hasNextFrame(Image::Image<Pixel::PixelRGBi1u> * & imagePtr){
	auto & pCodecCtx  = _this->codecCtx;
	auto & pFrame     = _this->frame;
	auto & packet     = _this->packet;

	int frameFinished=0;
	while(av_read_frame(_this->formatCtx, &packet)>=0) {
		if(packet.stream_index==_this->videoStreamID) {

			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished,&packet);
      
			if(frameFinished) {
				auto width  = pCodecCtx->width;
				auto height = pCodecCtx->height;

				Image::Image<Pixel::PixelRGBi1u> * image = nullptr;
				if((imagePtr->getWidth()==width)&&(imagePtr->getHeight()==height)){
					image = imagePtr;
				}else{
					if(imagePtr!=nullptr){delete imagePtr;}
					image = new Image::Image<Pixel::PixelRGBi1u>(width,height,dataManager);
					imagePtr = image;
				}

				uint8_t * data[AV_NUM_DATA_POINTERS];
				int linesize[AV_NUM_DATA_POINTERS];
				data[0] = static_cast<uint8_t*const>(static_cast<void*const>(image->getDataPtr()));
				linesize[0] = width*3;

				_this->img_convert_ctx = sws_getCachedContext(_this->img_convert_ctx,width, height, pCodecCtx->pix_fmt, width, height, PIX_FMT_RGB24, SWS_FAST_BILINEAR, NULL, NULL, NULL);
				sws_scale(_this->img_convert_ctx,pFrame->data, pFrame->linesize,0,pCodecCtx->height, data, linesize);

				++frameIndex;
				av_free_packet(&packet);
				return true;
			}
		}
    
		av_free_packet(&packet);
	}
	return false;
}


AVL_FFMPEG_DLL_EXPORT bool FFMPEGvideoFile::openFile(const std::string & fileName){
	auto & pFormatCtx    = _this->formatCtx;
	auto & pCodecCtx     = _this->codecCtx;
	auto & videoStreamID = _this->videoStreamID;
	frameIndex = 0;

	if(avformat_open_input(&pFormatCtx, fileName.c_str(), NULL, 0)!=0){
		//TODO: ERROR:
		return false;
	}
  
	if(avformat_find_stream_info(pFormatCtx,NULL)<0){
		//TODO: ERROR:
		return false;
	}
  
	// Find the first video stream
	videoStreamID=-1;
	for(unsigned int i=0; i<pFormatCtx->nb_streams; i++){
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

	if(avcodec_open2(pCodecCtx, _this->codec, NULL)<0){
		//TODO: ERROR:
		return false;
	}
  
	_this->frame=avcodec_alloc_frame();
	if(_this->frame==NULL){return false;}
  
	_this->numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,pCodecCtx->height);

	return true;
}

AVL_FFMPEG_DLL_EXPORT void FFMPEGvideoFile::closeFile(){
	frameIndex = 0;
	if(_this->frame    !=nullptr){av_free(_this->frame);                _this->frame     = nullptr;}
	if(_this->codecCtx !=nullptr){avcodec_close(_this->codecCtx);       _this->codecCtx  = nullptr;}
	if(_this->formatCtx!=nullptr){av_close_input_file(_this->formatCtx);_this->formatCtx = nullptr;}
}

}
