
#include "Circle.h"

namespace Paint {

//TODO use ImageSize
Image::Image<Pixel::PixelGRAYb> MakeCircle(const long &width,const long &height,const double &radius){
	return MakeCircle(width,height,width/2,height/2,radius);
}

Image::Image<Pixel::PixelGRAYb> MakeCircle(
	const long &width,
	const long &height,
	const long &xCenter,
	const long &yCenter,
	const double &radius)
{
	Image::Image<Pixel::PixelGRAYb> image(width,height);
	double xCenterD = xCenter;
	double yCenterD = yCenter;
	double radiusSq = radius*radius;
	for (long y=0; y<image.getHeight(); ++y)    { double yDistance = ((double)y)-yCenterD;//TODO: test for a better way to do this
		for (long x=0; x<image.getWidth(); ++x) { double xDistance = ((double)x)-xCenterD;
			if ((xDistance*xDistance + yDistance*yDistance) < radiusSq){
				image(x,y).setX(true);
			}else{
				image(x,y).setX(false);
			}
		}
	}
	return image;
}

}
