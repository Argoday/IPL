
#include <iostream>
#include <Video/FFMPEGplayer.h>
#include <stdio.h>
#include <String/AString.h>
#include <Image/Image_IO.h>
#include <Data/DataManager.h>

int main(int argc, char *argv[]) {

	if(argc < 3) {
		printf("Please provide a movie file and file type - example:\n>FrameDump.exe movie.mpg png\n");
		return -1;
	}
	std::string fileName = argv[1];
	std::string fileType = argv[2];

	Data::DataManager dataManager;
	Video::FFMPEGplayer ffmpegPlayer(&dataManager);
  
	if(ffmpegPlayer.openFile(fileName)==false){
		return -1;
	}
	
	while(ffmpegPlayer.hasNextFrame()==true) {
		Image::IO::write(ffmpegPlayer.getFrame(),"frame"+String::getString(ffmpegPlayer.getFrameIndex())+"." + fileType);
	}

	return 0;
}
