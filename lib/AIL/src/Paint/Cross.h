
#ifndef PAINT__Cross_H
#define PAINT__Cross_H

#include <AIL.h>
#include <Image/Image.h>
#include <Pixel/PixelY.h>

namespace Paint {

Image::Image<Pixel::PixelYb1> AIL_DLL_EXPORT MakeCross(const I4 & width,const I4 & height);
Image::Image<Pixel::PixelYb1> AIL_DLL_EXPORT MakeCross(const I4 & width,const I4 & height,const I4 & xCenter,const I4 & yCenter);

}

#endif
