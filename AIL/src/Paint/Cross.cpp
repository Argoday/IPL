
#ifndef IMAGE__Cross_CPP_H
#define IMAGE__Cross_CPP_H

#include "Cross.h"

namespace Paint {

//TODO use ImageSize
Image::Image<Pixel::PixelGRAYb> MakeCross(const long &width,const long &height){
	return MakeCross(width,height,width/2,height/2);
}

Image::Image<Pixel::PixelGRAYb> MakeCross(const long &width,const long &height,const long &xCenter,const long &yCenter){
	Image::Image<Pixel::PixelGRAYb> image(width,height);
	for (long y=0; y<image.getHeight(); ++y)    {
		for (long x=0; x<image.getWidth(); ++x) {
			if((x==xCenter)||(y==yCenter)){
				image(x,y).setX(true);
			}else{
				image(x,y).setX(false);
			}
		}
	}
	return image;
}

}

#endif
