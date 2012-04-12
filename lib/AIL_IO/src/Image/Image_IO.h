

#ifndef IMAGE__Image_IO_H
#define IMAGE__Image_IO_H

#include "AIL_IO.h"
#include <Image/Image.h>
#include <string>

namespace Image {

namespace IO {
	template<typename PixelType> AIL_IO_DLL_EXPORT Image<PixelType> read(Data::DataManager * const dataManager,const std::string & fileName);
	template<typename PixelType> AIL_IO_DLL_EXPORT void write(const Image<PixelType> & image,const std::string & fileName);

	template<typename PixelType> AIL_IO_DLL_EXPORT void writePPM(const Image<PixelType> & image,const std::string & fileName);
}

}

#endif
