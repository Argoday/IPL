
#ifndef IMAGE__ImageBase_H
#define IMAGE__ImageBase_H

#include <AIL.h>
#include <Pixel/PixelRGB.h>

namespace Image {

class AIL_DLL_EXPORT ImageBase {
	public:
		typedef Pixel::PixelRGBi1u DefaultPixelType;

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
