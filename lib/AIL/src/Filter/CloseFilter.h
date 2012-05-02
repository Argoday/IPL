
#ifndef FILTER__CloseFilter_H
#define FILTER__CloseFilter_H

#include "AIL.h"
#include "ImageOperation.h"
#include "MorphKernelType.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT CloseFilter
	: public ImageOperation<PixelType>
{

	public:
		CloseFilter():iterations(3),type(MorphKernelType::square){};
		CloseFilter(const I4 & _iterations):iterations(_iterations),type(MorphKernelType::square){};
		CloseFilter(const I4 & _iterations,const MorphKernelType & _type):iterations(_iterations),type(_type){};

		void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const ;

	private:
		I4 iterations;
		MorphKernelType type;

};

}

#endif
