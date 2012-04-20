
#ifndef FILTER__MinFilter1xHbasic_H
#define FILTER__MinFilter1xHbasic_H

#include "BaseMinFilter.h"

namespace Filter {

template <
	typename PixelType = Image::ImageBase::DefaultPixelType
> class MinFilter1xHbasic {

	public:
		MinFilter1xHbasic(
			const I4 & _filterHeight
		)
			:filterHeight(_filterHeight)	
			,yOffset( (_filterHeight - 1) / 2 )
		{
		};
		MinFilter1xHbasic(
			const I4 & _filterHeight,
			const I4 & _yOffset
		)
			:filterHeight(_filterHeight)
			,yOffset(_yOffset)
		{
		};

		__forceinline const I4 & getHeight()  const {return filterHeight;}
		__forceinline const I4 & getYoffset() const {return yOffset;}

		void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const ;

	private:
		const I4 filterHeight;
		const I4 yOffset;

};

}

#endif
