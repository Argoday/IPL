
#ifndef FILTER__DilateFilter_H
#define FILTER__DilateFilter_H

#include "AIL.h"
#include "ImageOperation.h"
#include "MorphKernelType.h"

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT DilateFilter
	: public ImageOperation<PixelType>
{

	public:
		DilateFilter():iterations(3),type(MorphKernelType::getSquare()){};
		DilateFilter(const long &_iterations):iterations(_iterations),type(MorphKernelType::getSquare()){};
		DilateFilter(const long &_iterations,const MorphKernelType &_type):iterations(_iterations),type(_type){};

		void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;

	private:

		void applyToCross  (const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;
		void applyToSquare (const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;
		void applyToCircle (const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;
		void applyToDiamond(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const ;

		long iterations;
		MorphKernelType type;

};

}

#endif
