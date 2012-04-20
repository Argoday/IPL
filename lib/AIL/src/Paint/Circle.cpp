
#include "Circle.h"

namespace Paint {

//TODO: use ImageSize
Image::Image<Pixel::PixelYb> MakeCircle(const I4 & width,const I4 & height,const F8 & radius){
	return MakeCircle(width,height,width/2,height/2,radius);
}

Image::Image<Pixel::PixelYb> MakeCircle(
	const I4 & width,
	const I4 & height,
	const I4 & xCenter,
	const I4 & yCenter,
	const F8 & radius)
{
	Image::Image<Pixel::PixelYb> image(width,height);
	F8 xCenterD = xCenter;
	F8 yCenterD = yCenter;
	F8 radiusSq = radius*radius;
	auto dataPtr = image.getDataPtr();
	for (I4 y=0; y<image.getHeight(); ++y)    { F8 yDistance = ((F8)y)-yCenterD;//TODO: test for a better way to do this
		for (I4 x=0; x<image.getWidth(); ++x) { F8 xDistance = ((F8)x)-xCenterD;
			if ((xDistance*xDistance + yDistance*yDistance) < radiusSq){
				dataPtr->setY(true);
			}else{
				dataPtr->setY(false);
			}
			++dataPtr;
		}
	}
	return image;
}

}
