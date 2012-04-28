
#ifndef FILTER__BaseLinearFilter_H
#define FILTER__BaseLinearFilter_H

#include <AIL.h>
#include <Meta/Forward.h>
#include "SimpleWxHdataOperation.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT BaseLinearFilter
	: public SimpleWxHdataOperation<PixelType>
{

	public:
		BaseLinearFilter(Image::Image<PixelType> && _filterData)
			:SimpleWxHdataOperation<PixelType>(Meta::forward(_filterData))
		{
			resetTotalColor();
		};

		virtual ~BaseLinearFilter(){}

		virtual void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const = 0 ;

		void resetTotalColor();

		FINLINE const typename PixelType::ComputationType & getTotalColor() const {return totalColor;}

	protected:
		typename PixelType::ComputationType totalColor; //TODO: pick a better name

};

}

#endif
