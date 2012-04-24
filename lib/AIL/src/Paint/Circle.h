
#ifndef PAINT__Circle_H
#define PAINT__Circle_H

#include <AIL.h>
#include <Image/Image.h>
#include <Pixel/PixelY.h>

namespace Paint {

Image::Image<Pixel::PixelYb1> AIL_DLL_EXPORT MakeCircle(const I4 & width,const I4 & height,const F8 & radius);
Image::Image<Pixel::PixelYb1> AIL_DLL_EXPORT MakeCircle(const I4 & width,const I4 & height,const I4 & xCenter,const I4 & yCenter,const F8 & radius);

}

#endif
