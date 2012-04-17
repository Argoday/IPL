
#ifndef PAINT__Circle_H
#define PAINT__Circle_H

#include <AIL.h>
#include <Image/Image.h>
#include <Pixel/PixelY.h>

namespace Paint {

Image::Image<Pixel::PixelYb> AIL_DLL_EXPORT MakeCircle(const long &width,const long &height,const double &radius);
Image::Image<Pixel::PixelYb> AIL_DLL_EXPORT MakeCircle(const long &width,const long &height,const long &xCenter,const long &yCenter,const double &radius);

}

#endif
