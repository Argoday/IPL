
#ifndef IMAGE__image_cast_H
#define IMAGE__image_cast_H

#include "AIL.h"
#include "Image.h"
#include <Meta/enable_if.h>
#include <Meta/disable_if.h>
#include <Meta/is_same.h>

namespace Image {

	template<class DstPixelType,class SrcPixelType> AIL_DLL_EXPORT typename Meta::enable_if<  Meta::is_same<DstPixelType,SrcPixelType>, Image<DstPixelType> >::type image_cast(const Image<SrcPixelType> & _image);
	template<class DstPixelType,class SrcPixelType> AIL_DLL_EXPORT typename Meta::disable_if< Meta::is_same<DstPixelType,SrcPixelType>, Image<DstPixelType> >::type image_cast(const Image<SrcPixelType> & _image);

}

#endif

