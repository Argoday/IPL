

#ifndef PIXEL__pixel_cast_Qt_H
#define PIXEL__pixel_cast_Qt_H

#include "AIL_QT.h"
#include <Pixel/PixelY.h>
#include <Pixel/PixelRGB.h>
#include <Pixel/PixelYUV.h>
#include <Pixel/pixel_cast.h>
#include <QColor>

namespace Pixel {

template<typename PixelType> FINLINE PixelType pixel_cast(const QRgb &color);

template<> FINLINE PixelRGBi1u pixel_cast<PixelRGBi1u>(const QRgb &_color){
	PixelRGBi1u color; //NOTE: There is potentially a much faster way to do this
	color.setR(qRed  (_color));
	color.setG(qGreen(_color));
	color.setB(qBlue (_color));
	return color;
}

template<> FINLINE QRgb pixel_cast<QRgb>(const PixelRGBi1u &_color){
	return qRgba(_color.getR(),_color.getG(),_color.getB(),255); //NOTE: There is potentially a much faster way to do this
}

template<> FINLINE QRgb pixel_cast<QRgb>(const PixelYi1u &_color){
	return qRgba(_color.getY(),_color.getY(),_color.getY(),255);
}
template<> FINLINE PixelYi1u pixel_cast<PixelYi1u>(const QRgb &_color){
	double tempY;
	tempY = qRed  (_color)*0.299; //NOTE: Fix this so that it is faster
	tempY+= qGreen(_color)*0.587;
	tempY+= qBlue (_color)*0.114;
	return PixelYi1u(tempY);
}

template<> FINLINE QRgb pixel_cast<QRgb>(const PixelRGBf8 &_color){
	return qRgba(_color.getR()*255.0,_color.getG()*255.0,_color.getB()*255.0,255);
}
template<> FINLINE PixelRGBf8 pixel_cast<PixelRGBf8>(const QRgb &_color){
	PixelRGBf8 color(
		((double)qRed  (_color))/255.0,
		((double)qGreen(_color))/255.0,
		((double)qBlue (_color))/255.0)
	;
	return color;
}
template<> FINLINE QRgb pixel_cast<QRgb>(const PixelYb1 &_color){
	if(_color.getY()==true){// TODO: check the asm generated for this function
		return qRgba(255,255,255,255);
	}
	return qRgba(0,0,0,255);
}
template<> FINLINE PixelYb1 pixel_cast<PixelYb1>(const QRgb &_color){
	double tempY;
	tempY = qRed  (_color)*0.299; // TODO: check the asm generated for this line
	tempY+= qGreen(_color)*0.587;
	tempY+= qBlue (_color)*0.114;
	if(tempY>0.5){
		return PixelYb1(true);
	}
	return PixelYb1(false);
}

template<> FINLINE PixelYUVf8 pixel_cast<PixelYUVf8>(const QRgb &_color){
	PixelYUVf8 color;
	double red   = qRed(_color);
	double green = qGreen(_color);
	double blue  = qBlue(_color);
	/*color.getY() =  0.299     *red +  0.587     *green +  0.114     *blue; // See Poynton Eq 25.12 Page 310
	color.getU() = -0.16807422*red + -0.32996484*green +  0.49803906*blue;
	color.getV() =  0.49803906*red + -0.41704688*green + -0.08099219*blue;
	color.getY()/=255.0;
	color.getU()/=255.0;
	color.getV()/=255.0;//*/
	color.getY() =  0.299    * red +  0.587    * green +  0.114    * blue; // See Poynton YPbPr http://www.poynton.com/notes/colour_and_gamma/ColorFAQ.html#RTFToC29
	color.getU() = -0.168736 * red + -0.331264 * green +  0.5      * blue;
	color.getV() =  0.5      * red + -0.418688 * green + -0.081312 * blue;
	color.getY()/=255.0;
	color.getU()/=255.0;
	color.getV()/=255.0;
	color.getU()+=0.5;
	color.getV()+=0.5;
	return color;
}

template<> FINLINE QRgb pixel_cast<QRgb>(const PixelYUVf8   &_color){
	/*double red   = _color.getY() +                           +  1.39652344*_color.getV(); // See Poynton Eq 25.13 Page 310
	double green = _color.getY() + -0.34279297*_color.getU() + -0.71134766*_color.getV();
	double blue  = _color.getY() +  1.76507813*_color.getU();
	return qRgba(red*255.0,green*255.0,blue*255.0,255); // TODO: check the asm generated for this line//*/

	double red   = _color.getY() +                               +  1.402*(_color.getV()-0.5); // See Poynton YPbPr http://www.poynton.com/notes/colour_and_gamma/ColorFAQ.html#RTFToC29
	double green = _color.getY() + -0.344136*(_color.getU()-0.5) + -0.714136*(_color.getV()-0.5);
	double blue  = _color.getY() +  1.772*(_color.getU()-0.5);
	return qRgba(red*255.0,green*255.0,blue*255.0,255); // TODO: check the asm generated for this line
}


}

#endif
