
#ifndef FILTER__LinearFilterWx1_H
#define FILTER__LinearFilterWx1_H

#include "AIL.h"
#include "BaseLinearFilter.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT LinearFilterWx1
	: public BaseLinearFilter<PixelType>
{

	public:
		LinearFilterWx1(Image::Image<PixelType> &&_filterData)
			:BaseLinearFilter<PixelType>(Meta::forward(_filterData))
		{
		};

		void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;

};

}

#endif
