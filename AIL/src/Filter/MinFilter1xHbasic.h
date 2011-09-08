
#ifndef FILTER__MinFilter1xHbasic_H
#define FILTER__MinFilter1xHbasic_H

#include "BaseMinFilter.h"

namespace Filter {

template <
	typename PixelType = Image::ImageBase::DefaultPixelType
> class MinFilter1xHbasic {

	public:
		MinFilter1xHbasic(
			const long &_filterHeight
		)
			:filterHeight(_filterHeight)	
			,yOffset( (_filterHeight - 1) / 2 )
		{
		};
		MinFilter1xHbasic(
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
