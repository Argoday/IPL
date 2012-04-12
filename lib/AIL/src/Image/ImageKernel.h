
#ifndef IMAGE__ImageKernel_H
#define IMAGE__ImageKernel_H

#include "Image.h"
#include <Pixel/PixelGRAY.h>

namespace Image {

template <
	typename PixelType,
	typename InclusionTestType
> class ImageKernel {
	public:

		ImageKernel(Image<PixelType> &&_kernel);
		ImageKernel(Image<PixelType> &&_kernel,const long &_parentImageWidth);

		Image<PixelType> &getKernel() {return kernel;} //If this is used calculateKernelSize() must be called by the callee after the kernel is manipulated
		const Image<PixelType> &getKernel() const {return kernel;}

		const long * const & getKernelSkipDataPtr()    const {return kernelSkipDataPtr   ;}
		const long * const & getKernelSkipDataPtrEnd() const {return kernelSkipDataPtrEnd;}

		void calculateKernelSkipData(const long & _parentImageWidth);

		virtual ~ImageKernel();

	private:
		
		static long calculateKernelSize(const Image<PixelType> &image);

		Image<PixelType> kernel;
		const long * kernelSkipDataPtr;
		const long * kernelSkipDataPtrEnd;
		long kernelSize;
		long parentImageWidth;
};

}

#endif
