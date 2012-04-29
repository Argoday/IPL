
#ifndef IMAGE__ImageBase_H
#define IMAGE__ImageBase_H

#include <AIL.h>
#include <Pixel/PixelY.h>
#include <Pixel/PixelRGB.h>
#include <Pixel/PixelRGBA.h>
#include <Pixel/PixelYUV.h>

namespace Image {

class AIL_DLL_EXPORT ImageBase {
	public:

		const I4 & getImageId() const {return imageId;}

	protected:
		I4 imageId;

		static I4 nextImageId;

		FINLINE ImageBase()
			:imageId(nextImageId)
		{
			++nextImageId;
		}
};

}

#endif
