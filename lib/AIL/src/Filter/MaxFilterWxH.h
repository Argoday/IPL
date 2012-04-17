

#ifndef FILTER__MaxFilterWxH_H
#define FILTER__MaxFilterWxH_H

#include "BaseMaxFilter.h"

namespace Filter {

template <
	typename PixelType = Image::ImageBase::DefaultPixelType
> class MaxFilterWxH
	: public BaseMaxFilter<PixelType>
{

	public:
		MaxFilterWxH(Image::Image<Pixel::PixelYb> &&_filterData)
			:BaseMaxFilter<PixelType>(Meta::forward(_filterData))
		{
		};

		void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;

};

}

#endif
