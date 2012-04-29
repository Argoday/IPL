
#ifndef IMAGE__ImageKernel_H
#define IMAGE__ImageKernel_H

#include "Image.h"
#include <Pixel/PixelY.h>

namespace Image {

template <
	typename PixelType,
	typename InclusionTestType
> class AIL_DLL_EXPORT ImageKernel {
	public:

		ImageKernel(Image<PixelType> && _kernel);
		ImageKernel(Image<PixelType> && _kernel,const I4 & _parentImageWidth);

		Image<PixelType> & getKernel() {return kernel;} //If this is used calculateKernelSize() must be called by the callee after the kernel is manipulated
		const Image<PixelType> & getKernel() const {return kernel;}

		const I4 * const & getKernelSkipDataPtr()    const {return kernelSkipDataPtr   ;}
		const I4 * const & getKernelSkipDataPtrEnd() const {return kernelSkipDataPtrEnd;}

		void calculateKernelSkipData(const I4 & _parentImageWidth);

		virtual ~ImageKernel();

	private:
		
		static I4 calculateKernelSize(const Image<PixelType> & image);

		Image<PixelType> kernel;
		const I4 * kernelSkipDataPtr;
		const I4 * kernelSkipDataPtrEnd;
		I4 kernelSize;
		I4 parentImageWidth;
};

}

#endif
