
#ifndef VIDEO__FFMPEGvideoFile_H
#define VIDEO__FFMPEGvideoFile_H

#include "AVL_ffmpeg.h"
#include <Image/Image.h>
#include <string>

namespace Video {

class AVL_FFMPEG_DLL_EXPORT FFMPEGvideoFile {
	public:
		typedef FFMPEGvideoFile ThisType;

		FFMPEGvideoFile(Data::DataManager * const & dataManager);
		~FFMPEGvideoFile();

		bool openFile(const std::string & fileName);
		void closeFile();

		bool hasNextFrame(Image::Image<Pixel::PixelRGBi1u> * & imagePtr);

		const I8u & getFrameIndex() const {return frameIndex;}

	private:
		I8u frameIndex;

		class FFMPEGvideoFile_d;
		FFMPEGvideoFile_d * _this;

		Data::DataManager * const dataManager;
};
	
}

#endif
