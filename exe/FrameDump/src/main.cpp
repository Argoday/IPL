
#include <iostream>

#include <Video/FFMPEGvideoFile.h>
#include <String/AString.h>
#include <Image/Image_IO.h>
#include <Data/DataManager.h>

int main(int argc, char *argv[]) {
	if(argc < 3) {
		std::cout<<"Please provide a movie file and file type - example:\n>FrameDump.exe movie.mpg png"<<std::endl;
		return -1;
	}
	std::string fileName = argv[1];
	std::string fileType = argv[2];

	Data::DataManager dataManager;
	Video::FFMPEGvideoFile ffmpegFile(&dataManager);
  
	if(ffmpegFile.openFile(fileName)==false){
		std::cout<<"Error opening movie file"<<std::endl;
		return -1;
	}
	Image::Image<Pixel::PixelRGBi1u> image;
	while(ffmpegFile.hasNextFrame(image)==true) {
		Image::IO::write(image,"frame"+String::getString(ffmpegFile.getFrameIndex(),6)+"." + fileType);
	}
	return 0;
}
