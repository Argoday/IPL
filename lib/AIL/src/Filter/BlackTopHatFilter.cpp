
#include "BlackTopHatFilter.h"
#include "CloseFilter.h"

namespace Filter {

template <
	typename PixelType
> void BlackTopHatFilter<PixelType>::applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const {
	CloseFilter<PixelType> closeFilter(iterations,type);

	closeFilter.applyTo(srcImage,dstImage);
	dstImage-=srcImage;

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::BlackTopHatFilter)
