
#include "image_cast.h"
#include "Algorithm/Algorithm1x1.h"
#include <Pixel/pixel_cast.h>
#include <Meta/enable_if.h>
#include <Meta/disable_if.h>
#include <Meta/is_same.h>

namespace Image {

template<class DstPixelType,class SrcPixelType> AIL_DLL_EXPORT typename Meta::enable_if<  Meta::is_same<DstPixelType,SrcPixelType>, Image<DstPixelType> >::type image_cast(const Image<SrcPixelType> & _image){
	return Image<DstPixelType>(_image);
}
template<class DstPixelType,class SrcPixelType> AIL_DLL_EXPORT typename Meta::disable_if< Meta::is_same<DstPixelType,SrcPixelType>, Image<DstPixelType> >::type image_cast(const Image<SrcPixelType> & _image){
	Image<DstPixelType> image(_image.getSize(),_image.getDataManager());
	Algorithm::Algorithm1x1<
		Pixel::pixel_cast_alg<DstPixelType,SrcPixelType>,
		SrcPixelType,
		DstPixelType
	>(_image.getPixelView(),image.getPixelView());
	return image;
}

}

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_ARGUMENT_1
#define FUNCTION_TEMPLATE_RETURN
#define FUNCTION_DOUBLE_TEMPLATE
#define FUNCTION_RETURN AIL_DLL_EXPORT Image::Image
#define FUNCTION_NAME Image::image_cast
#define FUNCTION_SIGNATURE_1 (const Image
#define FUNCTION_SIGNATURE_2 & _image)

#include <Pixel/PixelFunctionTemplateMacro.h>
//-------------------------------------------------------//*/
