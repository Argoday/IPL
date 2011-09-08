
#ifndef FILTER__OpenFilter_H
#define FILTER__OpenFilter_H

#include "AIL.h"
#include "ImageOperation.h"
#include "MorphKernelType.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT OpenFilter
	: public ImageOperation<PixelType>
{

	public:
		OpenFilter():iterations(3),type(MorphKernelType::getSquare()){};
		OpenFilter(const long &_iterations):iterations(_iterations),type(MorphKernelType::getSquare()){};
		OpenFilter(const long &_iterations,const MorphKernelType &_type):iterations(_iterations),type(_type){};

		void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;

	private:
		long iterations;
		MorphKernelType type;

};

}

#endif
