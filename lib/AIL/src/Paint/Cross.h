
#ifndef PAINT__Cross_H
#define PAINT__Cross_H

#include <AIL.h>
#include <Image/Image.h>
#include <Pixel/PixelGRAY.h>

namespace Paint {

Image::Image<Pixel::PixelGRAYb> AIL_DLL_EXPORT MakeCross(const long &width,const long &height);
Image::Image<Pixel::PixelGRAYb> AIL_DLL_EXPORT MakeCross(const long &width,const long &height,const long &xCenter,const long &yCenter);

}

#endif
