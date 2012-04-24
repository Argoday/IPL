
#include "Image_Qt.h"

#include <QImage.h>
#include <QColor>
#include <QImageWriter>
#include <Image/Image.h>

#include <Pixel/pixel_cast_Qt.h>

namespace Image {

namespace Convert {

// TODO: ? make these functional TypeCast operators ?
template<typename PixelType> AIL_QT_DLL_EXPORT QImage toQt(const Image<PixelType> &image) {
	if((image.getDataPtr()==nullptr)||(image.getWidth()<=0)||(image.getHeight()<=0)){
		//TODO: ERROR
		return 	QImage(10,10,QImage::Format_RGB32);
	}
	QImage qImage(image.getSize().getWidth(),image.getSize().getHeight(),QImage::Format_RGB32);
	auto imageDataPtr = image.getDataPtr();
	auto qData = qImage.bits();
	for (long y=0; y<image.getHeight(); ++y){ // TODO: Move this to Algorithm
		for (long x=0; x<image.getWidth(); ++x){
			(*qData) = Pixel::pixel_cast<QRgb>(*imageDataPtr);
			++imageDataPtr;
			qData+=4;
		}
	}
	return qImage;
}

template<> AIL_QT_DLL_EXPORT QImage toQt<Pixel::PixelRGBi1u>(const Image<Pixel::PixelRGBi1u> &image) {
	auto & width  = image.getSize().getWidth();
	auto & height = image.getSize().getHeight();
	if((image.getDataPtr()==nullptr)||(width<=0)||(height<=0)){
		//TODO: ERROR
		return 	QImage(10,10,QImage::Format_RGB888);
	}
	QImage qImage(width,height,QImage::Format_RGB888);
	auto imageDataPtr = image.getDataPtr();
	auto qData = qImage.bits();
	if(qImage.bytesPerLine()==width*3){
		memcpy(qData,imageDataPtr,image.getNumBytes());
	}else{
		auto linesize = qImage.bytesPerLine();
		for(int y=0; y<height; y++){
			memcpy(qData,imageDataPtr,linesize);
			imageDataPtr+=width;
			qData+=linesize;
		}
	}
	return qImage;
}

template<typename PixelType> AIL_QT_DLL_EXPORT Image<PixelType> fromQt(Data::DataManager * const dataManager,const QImage &image){
	Image<PixelType> ailImage(ImageSize(image.width(),image.height()),dataManager);
	auto imageDataPtr = ailImage.getDataPtr();
	for (long y=0; y<ailImage.getHeight(); ++y){ // TODO: Move this to Algorithm and make a straight copy when in the right color space
		for (long x=0; x<ailImage.getWidth(); ++x){
			(*imageDataPtr)=Pixel::pixel_cast<PixelType>(image.pixel(x, y));
			++imageDataPtr;
		}
	}
	return ailImage;
}

}

namespace IO {

AIL_QT_DLL_EXPORT QImage readQt(const std::string & fileName){
	QString filePathName;filePathName=filePathName.fromStdString(fileName);
	QImage image(filePathName);
	if(image.isNull()==true) {
		//TODO: ERROR: could not load image
	}
	return image;
}
AIL_QT_DLL_EXPORT void writeQt(const QImage & image,const std::string & fileName){

	QImageWriter imageWriter;
	imageWriter.setFileName(QString::fromStdString(fileName));
	if (imageWriter.canWrite() == true){
		imageWriter.write(image);
	}else{
		//TODO: ERROR: could not write Image
	}

}

}

}

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_ARGUMENT_1
#define FUNCTION_RETURN AIL_QT_DLL_EXPORT QImage
#define FUNCTION_NAME Image::Convert::toQt
#define FUNCTION_SIGNATURE_1 (const Image
#define FUNCTION_SIGNATURE_2 &image)

#define FUNCTION_IGNORE_RGBi1u

#include <Pixel/PixelFunctionTemplateMacro.h>
//-------------------------------------------------------

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_RETURN
#define FUNCTION_RETURN AIL_QT_DLL_EXPORT Image::Image
#define FUNCTION_NAME Image::Convert::fromQt
#define FUNCTION_SIGNATURE (Data::DataManager * const dataManager,const QImage &image)

#include <Pixel/PixelFunctionTemplateMacro.h>
//-------------------------------------------------------