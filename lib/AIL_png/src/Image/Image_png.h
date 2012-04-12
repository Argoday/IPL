

#ifndef IMAGE__Image_png_H
#define IMAGE__Image_png_H

#include "AIL_png.h"
#include <Image/Image.h>
#include <string>

namespace Image {

namespace IO {
	template<typename PixelType> AIL_PNG_DLL_EXPORT Image<PixelType> readPNG(Data::DataManager * const dataManager,const std::string & fileName);
	template<typename PixelType> AIL_PNG_DLL_EXPORT void writePNG(const Image<PixelType> & image,const std::string & fileName);
}

}

#endif
