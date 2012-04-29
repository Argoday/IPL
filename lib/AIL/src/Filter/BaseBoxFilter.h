
#ifndef FILTER__BaseMaxFilter_H
#define FILTER__BaseMaxFilter_H

#include <Meta/Forward.h>
#include "SimpleWxHbooleanOperation.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT BaseBoxFilter
	: public ImageOperation<PixelType>
{

	public:
		BaseBoxFilter(){};

		virtual void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const = 0 ;
	
};

}

#endif
