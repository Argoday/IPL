
#ifndef FILTER__MaxFilterWx1basic_H
#define FILTER__MaxFilterWx1basic_H

#include "BaseMaxFilter.h"

namespace Filter {

template <
	typename PixelType = Image::ImageBase::DefaultPixelType
> class MaxFilterWx1basic {

	public:
		MaxFilterWx1basic(
			const long &_filterWidth
		)
			:filterWidth(_filterWidth)	
			,xOffset( (_filterWidth - 1) / 2 )
		{
		};
		MaxFilterWx1basic(
			const long &_filterWidth,
			const long &_xOffset
		)
			:filterWidth(_filterWidth)
			,xOffset(_xOffset)
		{
		};

		__forceinline const long & getWidth() const {return filterWidth;}
		__forceinline const long & getXoffset() const {return xOffset;}

		void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;

	private:
		const long filterWidth;
		const long xOffset;

};

}

#endif
