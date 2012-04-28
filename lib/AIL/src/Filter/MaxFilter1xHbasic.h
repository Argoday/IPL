
#ifndef FILTER__MaxFilter1xHbasic_H
#define FILTER__MaxFilter1xHbasic_H

#include "BaseMaxFilter.h"

namespace Filter {

template <
	typename PixelType
> class MaxFilter1xHbasic {

	public:
		MaxFilter1xHbasic(
			const I4 & _filterHeight
		)
			:filterHeight(_filterHeight)	
			,yOffset( (_filterHeight - 1) / 2 )
		{
		};
		MaxFilter1xHbasic(
			const I4 & _filterHeight,
			const I4 & _yOffset
		)
			:filterHeight(_filterHeight)
			,yOffset(_yOffset)
		{
		};

		FINLINE const I4 & getHeight()  const {return filterHeight;}
		FINLINE const I4 & getYoffset() const {return yOffset;}

		void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const ;

	private:
		const I4 filterHeight;
		const I4 yOffset;

};

}

#endif
