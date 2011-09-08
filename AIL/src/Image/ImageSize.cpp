
#include "ImageSize.h"

namespace Image {

ImageSize::ImageSize(const long &_width,const long &_height)
	:width(_width)
	,width_1(_width-1)
	,height(_height)
	,height_1(_height-1)
	,numPixels(_width*_height)
{
}

}


