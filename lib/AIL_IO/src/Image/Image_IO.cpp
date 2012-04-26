
#include "Image_IO.h"
#include <Image/Image.h>
#include <Image/Image_Qt.h>
#include <Image/Image_png.h>
#include <Image/image_cast.h>
#include <String/AString.h>

namespace Image {

namespace IO {

template<typename PixelType> AIL_IO_DLL_EXPORT Image<PixelType> read(Data::DataManager * const dataManager,const std::string & fileName) {
	if(String::hasEnding(fileName,".png")){ //TODO: Add intelligent determination of fileType using Magic Bytes - or at least try multiple
		return readPNG<PixelType>(dataManager,fileName);
	}else{
		return readQt<PixelType>(dataManager,fileName);
	}
}

//TODO: Add configuration parameters (for color space, compression settings, etc..)
template<typename PixelType> AIL_IO_DLL_EXPORT void write(const Image<PixelType> & image,const std::string & fileName) {
	if(String::hasEnding(fileName,".png")){
		writePNG(image,fileName);
	}else if(String::hasEnding(fileName,".ppm")){
		writePPM(image,fileName);
	}else{
		writeQt(image,fileName);
	}
}

//TODO: Move writePPM to a seperate module ?
template<typename PixelType> AIL_IO_DLL_EXPORT void writePPM(const Image<PixelType> & _image,const std::string & fileName){
	Image<Pixel::PixelRGBi1u> image = image_cast<Pixel::PixelRGBi1u>(_image);

    FILE * pFile = nullptr;
	if(fopen_s(&pFile,fileName.c_str(), "wb") !=0){
		return; //TODO: ERROR: File could not be opened for writing
	}
	
	fprintf(pFile, "P6\n%d %d\n255\n", image.getWidth(), image.getHeight());
	fwrite(image.getDataPtr(), 1, image.getSize().getNumPixels()*3, pFile);
  
	fclose(pFile);
}

}

}

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_RETURN
#define FUNCTION_RETURN AIL_IO_DLL_EXPORT Image::Image
#define FUNCTION_NAME Image::IO::read
#define FUNCTION_SIGNATURE (Data::DataManager * const dataManager,const std::string & fileName)

#include <Pixel/PixelFunctionTemplateMacro.h>
//-------------------------------------------------------

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_ARGUMENT_1
#define FUNCTION_RETURN AIL_IO_DLL_EXPORT void
#define FUNCTION_NAME Image::IO::write
#define FUNCTION_SIGNATURE_1 (const Image
#define FUNCTION_SIGNATURE_2 & image,const std::string & fileName)

#include <Pixel/PixelFunctionTemplateMacro.h>
//-------------------------------------------------------

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_ARGUMENT_1
#define FUNCTION_RETURN AIL_IO_DLL_EXPORT void
#define FUNCTION_NAME Image::IO::writePPM
#define FUNCTION_SIGNATURE_1 (const Image
#define FUNCTION_SIGNATURE_2 & image,const std::string & fileName)

#include <Pixel/PixelFunctionTemplateMacro.h>
//-------------------------------------------------------
