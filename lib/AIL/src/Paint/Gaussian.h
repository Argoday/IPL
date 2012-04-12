
#ifndef PAINT__Gaussian_H
#define PAINT__Gaussian_H

#include <AIL.h>
#include <Image/Image.h>

namespace Paint {

template <typename PixelType> Image::Image<PixelType> AIL_DLL_EXPORT MakeGaussian(const long &width, const long &height,const double &sigma);
template <typename PixelType> Image::Image<PixelType> AIL_DLL_EXPORT MakeGaussian(const long &width, const long &height,const double &radius,const double &sigma);
template <typename PixelType> Image::Image<PixelType> AIL_DLL_EXPORT MakeGaussian(const long &width, const long &height,const long &xCenter,const long &yCenter,const double &radius,const double &sigma);

}

#endif
