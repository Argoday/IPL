
#ifndef FILTER__MaxFilter1xHbasic_H
#define FILTER__MaxFilter1xHbasic_H

#include "BaseMaxFilter.h"

namespace Filter {

template <
	typename PixelType = Image::ImageBase::DefaultPixelType
> class MaxFilter1xHbasic {

	public:
		MaxFilter1xHbasic(
			const long &_filterHeight
		)
			:filterHeight(_filterHeight)	
			,yOffset( (_filterHeight - 1) / 2 )
		{
		};
		MaxFilter1xHbasic(
			const long &_filterHeight,
			const long &_yOffset
		)
			:filterHeight(_filterHeight)
			,yOffset(_yOffset)
		{
		};

		__forceinline const long & getHeight() const {return filterHeight;}
		__forceinline const long & getYoffset() const {return yOffset;}

		void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;

	private:
		const long filterHeight;
		const long yOffset;

};

}

#endif
