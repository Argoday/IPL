
#ifndef FILTER__BaseMaxFilter_H
#define FILTER__BaseMaxFilter_H

#include <Meta/Forward.h>
#include "SimpleWxHbooleanOperation.h"

namespace Filter {

template <
	typename PixelType
> class BaseMaxFilter
	: public SimpleWxHbooleanOperation<PixelType>
{

	public:
		BaseMaxFilter(Image::Image<Pixel::PixelYb1> && _filterData)
			:SimpleWxHbooleanOperation<PixelType>(Meta::forward(_filterData))
		{
		};

		virtual void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const = 0 ;

};

}

#endif
