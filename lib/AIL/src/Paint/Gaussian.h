
#ifndef PAINT__Gaussian_H
#define PAINT__Gaussian_H

#include <AIL.h>
#include <Image/Image.h>

namespace Paint {

template <typename PixelType> Image::Image<PixelType> AIL_DLL_EXPORT MakeGaussian(const I4 & width, const I4 & height,const F8 & sigma);
template <typename PixelType> Image::Image<PixelType> AIL_DLL_EXPORT MakeGaussian(const I4 & width, const I4 & height,const F8 & radius,const F8 & sigma);
template <typename PixelType> Image::Image<PixelType> AIL_DLL_EXPORT MakeGaussian(const I4 & width, const I4 & height,const I4 & xCenter,const I4 & yCenter,const F8 & radius,const F8 & sigma);

}

#endif
