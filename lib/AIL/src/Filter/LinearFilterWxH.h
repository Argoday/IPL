
#ifndef FILTER__LinearFilterWxH_H
#define FILTER__LinearFilterWxH_H

#include "AIL.h"
#include "BaseLinearFilter.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT LinearFilterWxH
	: public BaseLinearFilter<PixelType>
{

	public:
		LinearFilterWxH(Image::Image<PixelType> && _filterData)
			:BaseLinearFilter<PixelType>(Meta::forward(_filterData))
		{
		};

		void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const ;

};

}

#endif
