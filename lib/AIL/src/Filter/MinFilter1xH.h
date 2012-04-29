

#ifndef FILTER__MinFilter1xH_H
#define FILTER__MinFilter1xH_H

#include "BaseMinFilter.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT MinFilter1xH
	: public BaseMinFilter<PixelType>
{

	public:
		MinFilter1xH(Image::Image<Pixel::PixelYb1> && _filterData)
			:BaseMinFilter<PixelType>(Meta::forward(_filterData))
		{
		};

		void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const ;

};

}

#endif
