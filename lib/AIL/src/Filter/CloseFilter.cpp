
#include "CloseFilter.h"
#include "ErodeFilter.h"
#include "DilateFilter.h"

namespace Filter {

template <
	typename PixelType
> void CloseFilter<PixelType>::applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const {
	DilateFilter<PixelType> dilateFilter(iterations,type);
	ErodeFilter <PixelType> erodeFilter (iterations,type);

	Image::Image<PixelType> tempImage(dstImage.getSize(),dstImage.getDataManager());

	dilateFilter.applyTo(srcImage,tempImage);
	erodeFilter.applyTo(tempImage,dstImage);
}

}

#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Filter::CloseFilter)
