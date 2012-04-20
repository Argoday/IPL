
#ifndef FILTER__MaxFilterWx1basic_H
#define FILTER__MaxFilterWx1basic_H

#include "BaseMaxFilter.h"

namespace Filter {

template <
	typename PixelType = Image::ImageBase::DefaultPixelType
> class MaxFilterWx1basic {

	public:
		MaxFilterWx1basic(
			const I4 & _filterWidth
		)
			:filterWidth(_filterWidth)	
			,xOffset( (_filterWidth - 1) / 2 )
		{
		};
		MaxFilterWx1basic(
			const I4 & _filterWidth,
			const I4 & _xOffset
		)
			:filterWidth(_filterWidth)
			,xOffset(_xOffset)
		{
		};

		__forceinline const I4 & getWidth()   const {return filterWidth;}
		__forceinline const I4 & getXoffset() const {return xOffset;}

		void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const ;

	private:
		const I4 filterWidth;
		const I4 xOffset;

};

}

#endif
