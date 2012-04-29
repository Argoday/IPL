

#ifndef FILTER__MaxFilterWxH_H
#define FILTER__MaxFilterWxH_H

#include "BaseMaxFilter.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT MaxFilterWxH
	: public BaseMaxFilter<PixelType>
{

	public:
		MaxFilterWxH(Image::Image<Pixel::PixelYb1> && _filterData)
			:BaseMaxFilter<PixelType>(Meta::forward(_filterData))
		{
		};

		void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const ;

};

}

#endif
