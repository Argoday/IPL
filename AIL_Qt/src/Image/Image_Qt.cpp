
#include "Image_Qt.h"

#include <QImage.h>
#include <QColor>
#include <Image/Image.h>

#include <Pixel/pixel_cast_Qt.h>

namespace Image {

namespace Convert {

// --- TypeCast ---
template<typename PixelType> AIL_QT_DLL_EXPORT QImage convertToQt(const Image<PixelType> &image) {
	if((image.getDataPtr()==nullptr)||(image.getWidth()<=0)||(image.getHeight()<=0)){
		return 	QImage(10,10,QImage::Format_ARGB32);
	}
	QImage qImage(image.getSize().getWidth(),image.getSize().getHeight(),QImage::Format_ARGB32);
	const PixelType *imageDataPtr = image.getDataPtr();
	for (long y=0; y<image.getHeight(); ++y){ // TODO: Move this to Algorithm and make a straight copy when in the right color space
		for (long x=0; x<image.getWidth(); ++x){
			qImage.setPixel(x,y,Pixel::pixel_cast<QRgb>(*imageDataPtr));
			++imageDataPtr;
		}
	}
	return qImage;
}

template<typename PixelType> AIL_QT_DLL_EXPORT Image<PixelType> convertFromQt(const QImage &image){
	Image<PixelType> ailImage(ImageSize(image.width(),image.height()));
	PixelType *imageDataPtr = ailImage.getDataPtr();
	for (long y=0; y<ailImage.getHeight(); ++y){ // TODO: Move this to Algorithm and make a straight copy when in the right color space
		for (long x=0; x<ailImage.getWidth(); ++x){
			(*imageDataPtr)=Pixel::pixel_cast<PixelType>(image.pixel(x, y));
			++imageDataPtr;
		}
	}
	return ailImage;
}

template<typename PixelType> AIL_QT_DLL_EXPORT Image<PixelType> convertFromQt(const QImage &image,Data::DataManager * const dataManager){
	Image<PixelType> ailImage(ImageSize(image.width(),image.height()),dataManager);
	PixelType *imageDataPtr = ailImage.getDataPtr();
	for (long y=0; y<ailImage.getHeight(); ++y){ // TODO: Move this to Algorithm and make a straight copy when in the right color space
		for (long x=0; x<ailImage.getWidth(); ++x){
			(*imageDataPtr)=Pixel::pixel_cast<PixelType>(image.pixel(x, y));
			++imageDataPtr;
		}
	}
	return ailImage;
}

}

}

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_RETURN
#define FUNCTION_RETURN AIL_QT_DLL_EXPORT Image::Image
#define FUNCTION_NAME Image::Convert::convertFromQt
#define FUNCTION_SIGNATURE (const QImage &image)

#include <Pixel/PixelFunctionTemplateMacro.h>

#undef FUNCTION_TEMPLATE_RETURN
#undef FUNCTION_RETURN
#undef FUNCTION_NAME
#undef FUNCTION_SIGNATURE
//-------------------------------------------------------

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_ARGUMENT_1
#define FUNCTION_RETURN AIL_QT_DLL_EXPORT QImage
#define FUNCTION_NAME Image::Convert::convertToQt
#define FUNCTION_SIGNATURE_1 (const Image
#define FUNCTION_SIGNATURE_2 &image)

#include <Pixel/PixelFunctionTemplateMacro.h>

#undef FUNCTION_TEMPLATE_RETURN
#undef FUNCTION_TEMPLATE_ARGUMENT_1
#undef FUNCTION_RETURN
#undef FUNCTION_NAME
#undef FUNCTION_SIGNATURE
//-------------------------------------------------------

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_RETURN
#define FUNCTION_RETURN AIL_QT_DLL_EXPORT Image::Image
#define FUNCTION_NAME Image::Convert::convertFromQt
#define FUNCTION_SIGNATURE (const QImage &image,Data::DataManager * const dataManager)

#include <Pixel/PixelFunctionTemplateMacro.h>

#undef FUNCTION_TEMPLATE_RETURN
#undef FUNCTION_RETURN
#undef FUNCTION_NAME
#undef FUNCTION_SIGNATURE
//-------------------------------------------------------