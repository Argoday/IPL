
#ifndef FILTER__BaseMinFilter_H
#define FILTER__BaseMinFilter_H

#include <Meta/Forward.h>
#include "SimpleWxHbooleanOperation.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT BaseMinFilter
	: public SimpleWxHbooleanOperation<PixelType>
{

	public:
		BaseMinFilter(Image::Image<Pixel::PixelYb1> && _filterData)
			:SimpleWxHbooleanOperation<PixelType>(Meta::forward(_filterData))
		{
		};

		virtual void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const = 0 ;

};

}

#endif
