

#ifndef FILTER__MaxFilterWx1_H
#define FILTER__MaxFilterWx1_H

#include "BaseMaxFilter.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT MaxFilterWx1
	: public BaseMaxFilter<PixelType>
{

	public:
		MaxFilterWx1(Image::Image<Pixel::PixelYb1> && _filterData)
			:BaseMaxFilter<PixelType>(Meta::forward(_filterData))
		{
		};

		void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const ;

};

}

#endif
