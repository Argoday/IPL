

#ifndef VIDEO__FFMPEGplayer_H
#define VIDEO__FFMPEGplayer_H

#include "AIL_ffmpeg.h"
#include <Image/Image.h>
#include <string>

namespace Video {

class FFMPEGplayer_d;
class AIL_FFMPEG_DLL_EXPORT FFMPEGplayer {
	public:
		FFMPEGplayer(Data::DataManager * const dataManager);
		~FFMPEGplayer();

		bool openFile(std::string fileName);
		void closeFile();

		bool hasNextFrame();

		const int & getFrameIndex() const {return frameIndex;}
		Image::Image<Pixel::PixelRGBi1u> getFrame();

	private:
		int frameIndex;
		FFMPEGplayer_d * _this;
		Data::DataManager * const dataManager;
};
	
}

#endif
