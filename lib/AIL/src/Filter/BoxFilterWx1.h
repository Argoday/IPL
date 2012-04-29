
#ifndef FILTER__BoxFilterWx1basic_H
#define FILTER__BoxFilterWx1basic_H

#include "BaseBoxFilter.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT BoxFilterWx1
	: public BaseBoxFilter<PixelType>
{

	public:
		BoxFilterWx1(
			const I4 & _filterWidth
		)
			:filterWidth(_filterWidth)	
			,xOffset( (_filterWidth - 1) / 2 )
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
