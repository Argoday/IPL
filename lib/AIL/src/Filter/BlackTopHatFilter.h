
#ifndef FILTER__BlackTopHatFilter_H
#define FILTER__BlackTopHatFilter_H

#include "AIL.h"
#include "ImageOperation.h"
#include "MorphKernelType.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT BlackTopHatFilter
	: public ImageOperation<PixelType>
{

	public:
		BlackTopHatFilter():iterations(3),type(MorphKernelType::getSquare()){};
		BlackTopHatFilter(const long &_iterations):iterations(_iterations),type(MorphKernelType::getSquare()){};
		BlackTopHatFilter(const long &_iterations,const MorphKernelType &_type):iterations(_iterations),type(_type){};

		void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;

	private:
		long iterations;
		MorphKernelType type;

};

}

#endif
