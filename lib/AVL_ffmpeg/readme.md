# AVL_ffmpeg - Video Library integration with ffmpeg

## Contents

### FFMPEGvideoFile
A very simple class that lets you open a video file and get the frames.

## Example Usage
 ------------
Data::DataManager dataManager;  
Video::FFMPEGvideoFile ffmpegFile(&dataManager);  
  
if(ffmpegFile.openFile(fileName)==false){  
	std::cout<<"Error opening movie file"<<std::endl;  
	return -1;  
}  
Image::Image<Pixel::PixelRGBi1u> * image = nullptr;  
while(ffmpegFile.hasNextFrame(image)==true) {  
	//Use (*image) ...  
}  
if(image!=nullptr){delete image;}  
 ------------

## Example Program
See ./exe/FrameDump  

## Dependencies

./lib/AIL  
