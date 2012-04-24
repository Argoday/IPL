
#ifndef IMAGE__Cross_CPP_H
#define IMAGE__Cross_CPP_H

#include "Cross.h"

namespace Paint {

//TODO use ImageSize
Image::Image<Pixel::PixelYb1> MakeCross(const I4 & width,const I4 & height){
	return MakeCross(width,height,width/2,height/2);
}

Image::Image<Pixel::PixelYb1> MakeCross(const I4 & width,const I4 & height,const I4 & xCenter,const I4 & yCenter){
	Image::Image<Pixel::PixelYb1> image(width,height);
	auto dataPtr = image.getDataPtr();
	for (I4 y=0; y<image.getHeight(); ++y)    {
		for (I4 x=0; x<image.getWidth(); ++x) {
			if((x==xCenter)||(y==yCenter)){
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

#endif
