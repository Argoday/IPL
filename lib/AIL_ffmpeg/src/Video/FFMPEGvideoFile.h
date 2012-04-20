

#ifndef VIDEO__FFMPEGvideoFile_H
#define VIDEO__FFMPEGvideoFile_H

#include "AIL_ffmpeg.h"
#include <Image/Image.h>
#include <string>

namespace Video {

class AIL_FFMPEG_DLL_EXPORT FFMPEGvideoFile {
	public:
		typedef FFMPEGvideoFile ThisType;

		ThisType(Data::DataManager * const & dataManager);
		~ThisType();

		bool openFile(std::string fileName);
		void closeFile();

		bool hasNextFrame();

		const I8u & getFrameIndex() const {return frameIndex;}
		Image::Image<Pixel::PixelRGBi1u> getFrame() const ;

	private:
		I8u frameIndex;

		class FFMPEGvideoFile_d;
		FFMPEGvideoFile_d * _this;
		Data::DataManager * const dataManager;
};
	
}

#endif
