
#ifndef FILTER__BoxFilter1xH_H
#define FILTER__BoxFilter1xH_H

#include "BaseBoxFilter.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT BoxFilter1xH
	: public BaseBoxFilter<PixelType>
{

	public:
		BoxFilter1xH(
			const I4 & _filterHeight
		)
			:filterHeight(_filterHeight)	
			,yOffset( (_filterHeight - 1) / 2 )
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
