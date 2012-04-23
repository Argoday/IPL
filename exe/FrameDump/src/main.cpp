
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
	while(ffmpegFile.hasNextFrame()==true) {
		Image::IO::write(ffmpegFile.getFrame(),"frame"+String::getString(ffmpegFile.getFrameIndex())+"." + fileType);
	}
	return 0;
}
