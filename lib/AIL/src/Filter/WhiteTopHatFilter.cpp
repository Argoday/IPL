
#include "WhiteTopHatFilter.h"
#include "OpenFilter.h"

namespace Filter {

template <
	typename PixelType
> void WhiteTopHatFilter<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {
	OpenFilter<PixelType> openFilter(iterations,type);

	Image::Image<PixelType> tempImage(dstImage.getSize(),dstImage.getDataManager());

	openFilter.applyTo(srcImage,tempImage);
	dstImage=srcImage;
	dstImage-=tempImage;

}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::WhiteTopHatFilter)
