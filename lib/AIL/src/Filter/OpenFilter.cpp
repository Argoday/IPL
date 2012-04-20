
#include "OpenFilter.h"
#include "ErodeFilter.h"
#include "DilateFilter.h"

namespace Filter {

template <
	typename PixelType
> void OpenFilter<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {
	ErodeFilter <PixelType> erodeFilter (iterations,type);
	DilateFilter<PixelType> dilateFilter(iterations,type);

	Image::Image<PixelType> tempImage(dstImage.getSize(),dstImage.getDataManager());

	erodeFilter.applyTo(srcImage,tempImage);
	dilateFilter.applyTo(tempImage,dstImage);
}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::OpenFilter)
