
#ifndef PIXEL__PIXEL_CAST_H
#define PIXEL__PIXEL_CAST_H

#include "PixelGRAY.h"
#include "PixelRGB.h"
//#include "PixelRGBA.h"
#include "PixelYUV.h"

namespace Pixel {

// TODO: split these into seperate header files
template <typename PixelType> __forceinline PixelType pixel_cast(const PixelGRAYb &color);
//template <typename PixelType> __forceinline PixelType pixel_cast(const PixelGRAYi &color);
//template <typename PixelType> __forceinline PixelType pixel_cast(const PixelGRAYd &color);
/*
template <typename PixelType> __forceinline PixelType pixel_cast(const PixelRGBi1u  &color);
template <typename PixelType> __forceinline PixelType pixel_cast(const PixelRGBi4_1 &color);
template <typename PixelType> __forceinline PixelType pixel_cast(const PixelRGBi4_2 &color);
template <typename PixelType> __forceinline PixelType pixel_cast(const PixelRGBf4   &color);*/
template <typename PixelType> __forceinline PixelType pixel_cast(const PixelRGBf8   &color);

/*template <typename PixelType> __forceinline PixelType pixel_cast(const PixelRGBAi &color);
template <typename PixelType> __forceinline PixelType pixel_cast(const PixelRGBAd &color);*/

//template <typename PixelType> __forceinline PixelType pixel_cast(const PixelYUVf8   &color);

template <typename PixelType> __forceinline PixelType pixel_cast(const PixelYUVf8   &color);

/*
template <> __forceinline QRgb pixel_cast<QRgb>(const WPixelRGBi &_color){
	return qRgba(_color.x,_color.y,_color.z,255);
}
template <> __forceinline WPixelRGBi pixel_cast<WPixelRGBi>(const QRgb &_color){
	WPixelRGBi color;
	color.x = qRed  (_color);
	color.y = qGreen(_color);
	color.z = qBlue (_color);
	return color;
}

template <> __forceinline QRgb pixel_cast<QRgb>(const WPixelRGBuc &_color){
	return qRgba(_color.x,_color.y,_color.z,255);
}
template <> __forceinline WPixelRGBuc pixel_cast<WPixelRGBuc>(const QRgb &_color){
	WPixelRGBuc color;
	color.x = qRed  (_color);
	color.y = qGreen(_color);
	color.z = qBlue (_color);
	return color;
}

template <> __forceinline QRgb pixel_cast<QRgb>(const WPixelRGBf &_color){
	return qRgba(_color.x*255.0f,_color.y*255.0f,_color.z*255.0f,255);
}
template <> __forceinline WPixelRGBf pixel_cast<WPixelRGBf>(const QRgb &_color){
	WPixelRGBf color;
	color.x = ((float)qRed  (_color))/255.0f;
	color.y = ((float)qGreen(_color))/255.0f;
	color.z = ((float)qBlue (_color))/255.0f;
	return color;
}
*/
template <> __forceinline PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelGRAYb &_color){
	if(_color==true){
		return PixelRGBf8::RangeType::maxPixel;
	}
	return PixelRGBf8::RangeType::minPixel;
}
/*template <> __forceinline PixelGRAYb pixel_cast<PixelGRAYb>(const WPixelGRAYi &_color){
	if(_color.x>128){
		return PixelGRAYb(true);
	}
	return PixelGRAYb(false);
}//*/
/*
template <> __forceinline QRgb pixel_cast<QRgb>(const WPixelGRAYi &_color){
	return qRgba(_color.x,_color.x,_color.x,255); // TODO: check the asm generated for this line
}
template <> __forceinline WPixelGRAYi pixel_cast<WPixelGRAYi>(const QRgb &_color){
	return WPixelGRAYi(qRed  (_color)*0.299 + qGreen(_color)*0.587 + qBlue (_color)*0.114);
}//*/
/*template <> __forceinline PixelGRAYi pixel_cast<WPixelGRAYi>(const WPixelYUVd &_color){
	return WPixelGRAYi(_color.y*255.0);
}
template <> __forceinline WPixelYUVd pixel_cast<WPixelYUVd>(const WPixelGRAYi &_color){
	return WPixelYUVd(((double)_color.x)/255.0,0.0,0.0);
}//*/
/*template <> __forceinline WPixelRGBd pixel_cast<WPixelRGBd>(const WPixelGRAYi &_color){
	return WPixelRGBd(static_cast<double>(_color.x)/255.0);
}
template <> __forceinline WPixelGRAYi pixel_cast<WPixelGRAYi>(const WPixelRGBd &_color){
	return WPixelGRAYi(_color.getR()*0.299 + _color.getG()*0.587 + _color.getB()*0.114);
}/*
template <> __forceinline WPixelGRAYi pixel_cast<WPixelGRAYi>(const WPixelGRAYd &_color){
	return WPixelGRAYi(_color.x*255.0);
}*/
/*template <> __forceinline WPixelGRAYi pixel_cast<WPixelGRAYi>(const PixelGRAYb &_color){
	if(_color==true){
		return WPixelGRAYi::maxPixel;
	}
	return WPixelGRAYi::minPixel;
}
template <> __forceinline WPixelGRAYi pixel_cast<WPixelGRAYi>(const WPixelGRAYi &_color){
	return _color;
}//*/
template <> __forceinline PixelGRAYb pixel_cast<PixelGRAYb>(const PixelRGBf8 &_color){
	double tempY;
	tempY = _color.getR()*0.299; // TODO: Check the asm generated for this line
	tempY+= _color.getG()*0.587;
	tempY+= _color.getB()*0.114;
	if(tempY>0.5){
		return PixelGRAYb(true);
	}
	return PixelGRAYb(false);
}
/*
template <> __forceinline WPixelGRAYd pixel_cast<WPixelGRAYd>(const WPixelGRAYi &_color){
	return WPixelGRAYd(_color.x/255);
}

template <> __forceinline QRgb pixel_cast<QRgb>(const WPixelGRAYd &_color){
	return qRgba(_color.x*255.0,_color.x*255.0,_color.x*255.0,255); // TODO: check the asm generated for this line
}
template <> __forceinline WPixelGRAYd pixel_cast<WPixelGRAYd>(const QRgb &_color){
	WPixelGRAYd color;
	color.x = qRed  (_color)*0.299; // TODO: check the asm generated for this line
	color.x+= qGreen(_color)*0.587;
	color.x+= qBlue (_color)*0.114;
	color.x/=255.0;
	return color;
}
template <> __forceinline QRgb pixel_cast<QRgb>(const WPixelYUVd &_color){
	double red   = _color.y +                      +  1.39652344*_color.b; // See Poynton Eq 25.13 Page 310
	double green = _color.y + -0.34279297*_color.a + -0.71134766*_color.b;
	double blue  = _color.y +  1.76507813*_color.a;
	return qRgba(red*255.0,green*255.0,blue*255.0,255); // TODO: check the asm generated for this line
}
template <> __forceinline WPixelYUVd pixel_cast<WPixelYUVd>(const QRgb &_color){
	WPixelYUVd color;
	double red   = qRed(_color);
	double green = qGreen(_color);
	double blue  = qBlue(_color);
	color.y =  0.299     *red +  0.587     *green +  0.114     *blue; // See Poynton Eq 25.12 Page 310
	color.a = -0.16807422*red + -0.32996484*green +  0.49803906*blue;
	color.b =  0.49803906*red + -0.41704688*green + -0.08099219*blue;
	color.y/=255.0;color.a/=255.0;color.b/=255.0;
	return color;
}
template <> __forceinline WPixelGRAYd pixel_cast<WPixelGRAYd>(const WPixelYUVd &_color){
	return WPixelGRAYd(_color.y);
}
template <> __forceinline WPixelYUVd pixel_cast<WPixelYUVd>(const WPixelGRAYd &_color){
	return WPixelYUVd(_color.x,0.0,0.0);
}
template <> __forceinline WPixelYUVd pixel_cast<WPixelYUVd>(const WPixelRGBd &_color){
	WPixelYUVd color;
	color.y =  0.299     *_color.x +  0.587     *_color.y +  0.114     *_color.z; // See Poynton Eq 25.12 Page 310
	color.a = -0.16807422*_color.x + -0.32996484*_color.y +  0.49803906*_color.z;
	color.b =  0.49803906*_color.x + -0.41704687*_color.y + -0.08099219*_color.z;
	return color;
}
template <> __forceinline WPixelRGBd pixel_cast<WPixelRGBd>(const WPixelYUVd &_color){
	WPixelRGBd color;
	color.x = _color.y +                      +  1.39652344*_color.b; // See Poynton Eq 25.13 Page 310
	color.y = _color.y + -0.34279297*_color.a + -0.71134766*_color.b;
	color.z = _color.y +  1.76507813*_color.a;
	return color;
}
template <> __forceinline WPixelYUVd pixel_cast<WPixelYUVd>(const WPixelYUVd &_color){
	return _color;
}
template <> __forceinline WPixelRGBd pixel_cast<WPixelRGBd>(const WPixelGRAYd &_color){
	return WPixelRGBd(_color.x,_color.x,_color.x);
}
template <> __forceinline WPixelGRAYd pixel_cast<WPixelGRAYd>(const WPixelRGBd &_color){
	WPixelGRAYd color;
	color.x = _color.x*0.299; // TODO: Check the asm generated for this line
	color.x+= _color.y*0.587;
	color.x+= _color.z*0.114;
	return color;
}*/
template <> __forceinline PixelGRAYb pixel_cast<PixelGRAYb>(const PixelGRAYb &_color){
	return _color;
}
template <> __forceinline PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelRGBf8 &_color){
	return _color;
}/*
template <> __forceinline WPixelGRAYd pixel_cast<WPixelGRAYd>(const WPixelGRAYd &_color){
	return _color;
}

template <> __forceinline QRgb pixel_cast<QRgb>(const WPixelRGBAi &_color){
	return qRgba(_color.x,_color.y,_color.z,_color.w);
}
template <> __forceinline WPixelRGBAi pixel_cast<WPixelRGBAi>(const QRgb &_color){
	WPixelRGBAi color;
	color.x = qRed  (_color);
	color.y = qGreen(_color);
	color.z = qBlue (_color);
	color.w = qAlpha(_color);
	return color;
}

template <> __forceinline QRgb pixel_cast<QRgb>(const WPixelRGBAd &_color){
	return qRgba(_color.x*255.0,_color.y*255.0,_color.z*255.0,_color.w*255.0);
}
template <> __forceinline WPixelRGBAd pixel_cast<WPixelRGBAd>(const QRgb &_color){
	WPixelRGBAd color;
	color.x = ((double)qRed  (_color))/255.0;
	color.y = ((double)qGreen(_color))/255.0;
	color.z = ((double)qBlue (_color))/255.0;
	color.w = ((double)qAlpha(_color))/255.0;
	return color;
}
*/
};

#endif
