

#ifndef FILTER__MinFilterWxH_H
#define FILTER__MinFilterWxH_H

#include "BaseMinFilter.h"

namespace Filter {

template <
	typename PixelType = Image::ImageBase::DefaultPixelType
> class MinFilterWxH
	: public BaseMinFilter<PixelType>
{

	public:
		MinFilterWxH(Image::Image<Pixel::PixelYb> &&_filterData)
			:BaseMinFilter<PixelType>(Meta::forward(_filterData))
		{
		};

		void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;

};

}

#endif
