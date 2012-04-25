
#include "ImageSize.h"

namespace Image {

ImageSize::ImageSize()
	:width(0)
	,width_1(-1)
	,height(0)
	,height_1(-1)
	,numPixels(0)
{
}
ImageSize::ImageSize(const I4 & _width,const I4 & _height)
	:width(_width)
	,width_1(_width-1)
	,height(_height)
	,height_1(_height-1)
	,numPixels(_width*_height)
{
}

}


