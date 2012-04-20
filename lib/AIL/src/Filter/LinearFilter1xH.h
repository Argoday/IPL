
#ifndef FILTER__LinearFilter1xH_H
#define FILTER__LinearFilter1xH_H

#include "AIL.h"
#include "BaseLinearFilter.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT LinearFilter1xH
	: public BaseLinearFilter<PixelType>
{

	public:
		LinearFilter1xH(Image::Image<PixelType> && _filterData)
			:BaseLinearFilter<PixelType>(Meta::forward(_filterData))
		{
		};

		void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const ;

};

}

#endif
