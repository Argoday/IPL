
#ifndef FILTER__MaxFilter1xH_H
#define FILTER__MaxFilter1xH_H

#include "BaseMaxFilter.h"

namespace Filter {

template <
	typename PixelType = Image::ImageBase::DefaultPixelType
> class MaxFilter1xH
	: public BaseMaxFilter<PixelType>
{

	public:
		MaxFilter1xH(Image::Image<Pixel::PixelGRAYb> &&_filterData)
			:BaseMaxFilter<PixelType>(Meta::forward(_filterData))
		{
		};

		void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;

};

}

#endif
