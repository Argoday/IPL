
#ifndef IMAGE__ImageBase_H
#define IMAGE__ImageBase_H

#include <AIL.h>
#include <Pixel/PixelRGB.h>

namespace Image {

class AIL_DLL_EXPORT ImageBase {
	public:
		typedef Pixel::PixelRGBf8 DefaultPixelType;

		const long &getImageId() const {return imageId;}

	protected:
		long imageId;

		static long nextImageId;

		__forceinline ImageBase()
			:imageId(nextImageId)
		{
			++nextImageId;
		}
};

}

#endif
