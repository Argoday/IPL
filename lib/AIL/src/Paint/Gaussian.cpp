
#include "Gaussian.h"
#include <Image/Image.h>
#include <math.h> //For: exp()

namespace Paint {

template <typename PixelType> AIL_DLL_EXPORT Image::Image<PixelType> MakeGaussian(const I4 & width, const I4 & height,const F8 & sigma){
	return MakeGaussian<PixelType>(width,height,2*width+2*height,sigma);
}
template <typename PixelType> AIL_DLL_EXPORT Image::Image<PixelType> MakeGaussian(const I4 & width, const I4 & height,const F8 & radius,const F8 & sigma){
	return MakeGaussian<PixelType>(width,height,width/2,height/2,radius,sigma);
}
template <typename PixelType> AIL_DLL_EXPORT Image::Image<PixelType> MakeGaussian(const I4 & width, const I4 & height,const I4 & xCenter,const I4 & yCenter,const F8 & radius,const F8 & sigma){
	Image::Image<PixelType> image(width,height);
	F8 total = 0.0;
	PixelType::DataType * filterDataPtr = image.getDataPtr();
	F8 param = -1.0 / (2.0 * sigma * sigma);
	F8 radiusSq = radius*radius;
	for (I4 y=0; y<image.getHeight(); ++y)    { F8 yDistance = y-yCenter;
		for (I4 x=0; x<image.getWidth(); ++x) { F8 xDistance = x-xCenter;
			F8 distanceSq = (xDistance*xDistance + yDistance*yDistance);
			if (distanceSq < radiusSq){
				F8 pdfValue = exp(distanceSq*param);
				(*filterDataPtr) = (PixelType::RangeType::maxPixel*pdfValue);
				total += pdfValue;
			}else{
				(*filterDataPtr) = PixelType::RangeType::minPixel;
			}
			++filterDataPtr;
		}
	}
	image/=total;
	return image;
}

}

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_RETURN
#define ONLY_F

#define FUNCTION_RETURN AIL_DLL_EXPORT Image::Image
#define FUNCTION_NAME Paint::MakeGaussian
#define FUNCTION_SIGNATURE (const I4 & width, const I4 & height,const F8 & sigma)

#include <Pixel/PixelFunctionTemplateMacro.h>
//-------------------------------------------------------