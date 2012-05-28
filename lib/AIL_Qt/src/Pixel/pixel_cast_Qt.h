

#ifndef PIXEL__pixel_cast_Qt_H
#define PIXEL__pixel_cast_Qt_H

#include "AIL_QT.h"
#include <Pixel/PixelY.h>
#include <Pixel/PixelRGB.h>
#include <Pixel/PixelRGBA.h>
#include <Pixel/PixelYUV.h>
#include <Pixel/pixel_cast.h>
#include <QColor>

namespace Pixel {

//NOTE: After PixelBGRAi1u is fully implemented then all of these can go away and be replaced with using a static_cast<PixelBGRAi1u>(QRgb) indirection

template<typename PixelType> FINLINE PixelType pixel_cast(const QRgb & color);

template<> FINLINE PixelRGBi1u pixel_cast<PixelRGBi1u>(const QRgb & _color){
	PixelRGBi1u color; //NOTE: There is potentially a much faster way to do this
	color.setR(qRed  (_color));
	color.setG(qGreen(_color));
	color.setB(qBlue (_color));
	return color;
}
template<> FINLINE PixelARGBi1u pixel_cast<PixelARGBi1u>(const QRgb & _color){
	PixelARGBi1u color; //NOTE: There is potentially a much much faster way to do this - or for RGBA, not sure which
	color.setR(qRed  (_color));
	color.setG(qGreen(_color));
	color.setB(qBlue (_color));
	color.setA(qAlpha(_color));
	return color;
}

template<> FINLINE PixelRGBi4 pixel_cast<PixelRGBi4>(const QRgb & _color){
	PixelRGBi4 color;
	color.setR(qRed  (_color));
	color.setG(qGreen(_color));
	color.setB(qBlue (_color));
	return color;
}
template<> FINLINE PixelARGBi4 pixel_cast<PixelARGBi4>(const QRgb & _color){
	PixelARGBi4 color;
	color.setR(qRed  (_color));
	color.setG(qGreen(_color));
	color.setB(qBlue (_color));
	color.setA(qAlpha(_color));
	return color;
}
template<> FINLINE QRgb pixel_cast<QRgb>(const PixelRGBi1u & _color){
	return qRgba(_color.getR(),_color.getG(),_color.getB(),255); //NOTE: There is potentially a much faster way to do this
}
template<> FINLINE QRgb pixel_cast<QRgb>(const PixelRGBi4 & _color){
	return qRgba(_color.getR(),_color.getG(),_color.getB(),255); //NOTE: There is potentially a much faster way to do this
}

template<> FINLINE QRgb pixel_cast<QRgb>(const PixelARGBi1u & _color){
	return qRgba(_color.getR(),_color.getG(),_color.getB(),_color.getA()); //NOTE: There is potentially a much much faster way to do this - or for RGBA, not sure which
}
template<> FINLINE QRgb pixel_cast<QRgb>(const PixelARGBi4 & _color){
	return qRgba(_color.getR(),_color.getG(),_color.getB(),_color.getA());
}

template<> FINLINE QRgb pixel_cast<QRgb>(const PixelYi1u &_color){
	return qRgba(_color.getY(),_color.getY(),_color.getY(),255);
}
template<> FINLINE QRgb pixel_cast<QRgb>(const PixelYi4 &_color){
	return qRgba(_color.getY(),_color.getY(),_color.getY(),255);
}
template<> FINLINE PixelYi1u pixel_cast<PixelYi1u>(const QRgb & _color){
	F8 tempY;
	tempY = qRed  (_color)*0.299; //NOTE: Fix this so that it is faster
	tempY+= qGreen(_color)*0.587;
	tempY+= qBlue (_color)*0.114;
	return PixelYi1u(tempY);
}
template<> FINLINE PixelYi4 pixel_cast<PixelYi4>(const QRgb & _color){
	F8 tempY;
	tempY = qRed  (_color)*0.299; //NOTE: Fix this so that it is faster
	tempY+= qGreen(_color)*0.587;
	tempY+= qBlue (_color)*0.114;
	return PixelYi4(tempY);
}
template<> FINLINE QRgb pixel_cast<QRgb>(const PixelRGBf8 & _color){
	return qRgba(_color.getR()*255.0,_color.getG()*255.0,_color.getB()*255.0,255);
}
template<> FINLINE PixelRGBf8 pixel_cast<PixelRGBf8>(const QRgb & _color){
	PixelRGBf8 color(
		((F8)qRed  (_color))/255.0,
		((F8)qGreen(_color))/255.0,
		((F8)qBlue (_color))/255.0)
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
	F8 tempY;
	tempY = qRed  (_color)*0.299; // TODO: check the asm generated for this line
	tempY+= qGreen(_color)*0.587;
	tempY+= qBlue (_color)*0.114;
	if(tempY>0.5){
		return PixelYb1(true);
	}
	return PixelYb1(false);
}

template<> FINLINE PixelYUVf8 pixel_cast<PixelYUVf8>(const QRgb &_color){
	return pixel_cast<PixelYUVf8>(PixelRGBf8(qRed(_color)/255.0,qGreen(_color)/255.0,qBlue(_color)/255.0));
}

template<> FINLINE QRgb pixel_cast<QRgb>(const PixelYUVf8 & _color){
	PixelRGBf8 tempColor = pixel_cast<PixelRGBf8>(_color);
	return qRgba(tempColor.getR()*255.0,tempColor.getG()*255.0,tempColor.getB()*255.0,255);
}


}

#endif
