
#include "Gaussian.h"
#include <Image/Image.h>
#include <math.h> //For: exp()

namespace Paint {

template <typename PixelType> AIL_DLL_EXPORT Image::Image<PixelType> MakeGaussian(const long &width, const long &height,const double &sigma){
	return MakeGaussian<PixelType>(width,height,2*width+2*height,sigma);
}
template <typename PixelType> AIL_DLL_EXPORT Image::Image<PixelType> MakeGaussian(const long &width, const long &height,const double &radius,const double &sigma){
	return MakeGaussian<PixelType>(width,height,width/2,height/2,radius,sigma);
}
template <typename PixelType> AIL_DLL_EXPORT Image::Image<PixelType> MakeGaussian(const long &width, const long &height,const long &xCenter,const long &yCenter,const double &radius,const double &sigma){
	Image::Image<PixelType> image(width,height);
	double total = 0.0;
	PixelType::DataType * filterDataPtr = image.getDataPtr();
	double param = -1.0 / (2.0 * sigma * sigma);
	double radiusSq = radius*radius;
	for (long y=0; y<image.getHeight(); ++y)    { float yDistance = ((float)y)-yCenter;
		for (long x=0; x<image.getWidth(); ++x) { float xDistance = ((float)x)-xCenter;
			double distanceSq = (xDistance*xDistance + yDistance*yDistance);
			if (distanceSq < radiusSq){
				double pdfValue = exp(distanceSq*param);
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
#define FUNCTION_SIGNATURE (const long &width, const long &height,const double &sigma)

#include <Pixel/PixelFunctionTemplateMacro.h>
//-------------------------------------------------------