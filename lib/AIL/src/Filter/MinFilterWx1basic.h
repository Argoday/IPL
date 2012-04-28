
#ifndef FILTER__MinFilterWx1basic_H
#define FILTER__MinFilterWx1basic_H

#include "BaseMinFilter.h"

namespace Filter {

template <
	typename PixelType
> class MinFilterWx1basic {

	public:
		MinFilterWx1basic(
			const I4 & _filterWidth
		)
			:filterWidth(_filterWidth)	
			,xOffset( (_filterWidth - 1) / 2 )
		{
		};
		MinFilterWx1basic(
			const I4 & _filterWidth,
			const I4 & _xOffset
		)
			:filterWidth(_filterWidth)
			,xOffset(_xOffset)
		{
		};

		FINLINE const I4 & getWidth()   const {return filterWidth;}
		FINLINE const I4 & getXoffset() const {return xOffset;}

		void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const ;

	private:
		const I4 filterWidth;
		const I4 xOffset;

};

}

#endif
