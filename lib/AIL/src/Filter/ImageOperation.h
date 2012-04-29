
#ifndef FILTER__ImageOperation_H
#define FILTER__ImageOperation_H

#include <Image/Image.h>

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT ImageOperation {
	public:
		virtual void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const = 0 ;
};

}

#endif
