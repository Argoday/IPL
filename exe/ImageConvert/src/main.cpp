
#include <Image/Image_IO.h>

#include <string>
#include <iostream>

int main(int argc, char * argv[]){
	if(argc!=3){
		std::cout<<"Usage example: ./ImageConvert.exe A.bmp A.png"<<std::endl;
		return 0;
	}
	std::string fromFileName = argv[1];
	std::string toFileName   = argv[2];
	Image::Image<Pixel::PixelRGBf8> image = Image::IO::read<Pixel::PixelRGBf8>(nullptr,fromFileName);
	if(image.getHeight()==0){
		std::cout<<"Error Reading File - received image of zero height"<<std::endl;
	}else{
		Image::IO::write(image,toFileName);
	}
	return 1;
}
