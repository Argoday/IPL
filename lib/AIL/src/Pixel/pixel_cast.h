
#ifndef PIXEL__PIXEL_CAST_H
#define PIXEL__PIXEL_CAST_H

#include "PixelGRAY.h"
#include "PixelRGB.h"
#include "PixelYUV.h"

#pragma warning( disable : 4244 ) //Note: Disable warning for possible conversion loss when going to i1u

namespace Pixel {

template <
	typename DstPixelType,
	typename SrcPixelType
> class pixel_cast_alg {
	public:
		static __forceinline void process(DstPixelType * const & dstPixel,const SrcPixelType * const & srcPixel){
			(*dstPixel) = pixel_cast<DstPixelType>(*srcPixel);
		}
};

// TODO: split these into seperate header files
template <typename DstPixelType,typename SrcPixelType> __forceinline DstPixelType pixel_cast(const SrcPixelType & color);

template <> __forceinline PixelGRAYb pixel_cast<PixelGRAYb>(const PixelGRAYi1u &_color){
	if(_color.getX()>128){return PixelGRAYb(true);}return PixelGRAYb(false);
}
template <> __forceinline PixelGRAYb pixel_cast<PixelGRAYb>(const PixelRGBi1u &_color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	if(tempY>500){return PixelGRAYb(true);}return PixelGRAYb(false);
}
template <> __forceinline PixelGRAYb pixel_cast<PixelGRAYb>(const PixelRGBf8 &_color){
	double tempY;
	tempY = _color.getR()*0.299; // TODO: Check the asm generated for this line
	tempY+= _color.getG()*0.587;
	tempY+= _color.getB()*0.114;
	if(tempY>0.5){return PixelGRAYb(true);}return PixelGRAYb(false);
}
template <> __forceinline PixelGRAYb pixel_cast<PixelGRAYb>(const PixelYUVf8 &_color){
	if(_color.getY()>0.5){return PixelGRAYb(true);}return PixelGRAYb(false);
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> __forceinline PixelGRAYi1u pixel_cast<PixelGRAYi1u>(const PixelGRAYb &_color){
	if(_color.getX()==true){return PixelGRAYi1u::RangeType::maxPixel;}return PixelGRAYi1u::RangeType::minPixel;
}
template <> __forceinline PixelGRAYi1u pixel_cast<PixelGRAYi1u>(const PixelRGBi1u &_color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	return PixelGRAYi1u(tempY/1000);//TODO: Redo the calculation so that this can be a shift (aka /1024)
}
template <> __forceinline PixelGRAYi1u pixel_cast<PixelGRAYi1u>(const PixelRGBf8 &_color){
	double tempY;
	tempY = _color.getR()*0.299; // TODO: Check the asm generated for this line
	tempY+= _color.getG()*0.587;
	tempY+= _color.getB()*0.114;
	return PixelGRAYi1u(tempY*255.0);
}
template <> __forceinline PixelGRAYi1u pixel_cast<PixelGRAYi1u>(const PixelYUVf8 &_color){
	return PixelGRAYi1u(_color.getY());
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> __forceinline PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelGRAYb &_color){
	if(_color.getX()==true){return PixelRGBi1u::RangeType::maxPixel;}return PixelRGBi1u::RangeType::minPixel;
}
template <> __forceinline PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelGRAYi1u &_color){
	return PixelRGBi1u(_color.getX());
}
template <> __forceinline PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelRGBf8 &_color){
	return PixelRGBi1u(
		(_color.getR()*255.0),
		(_color.getG()*255.0),
		(_color.getB()*255.0))
	;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> __forceinline PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelGRAYb &_color){
	if(_color.getX()==true){return PixelRGBf8::RangeType::maxPixel;}return PixelRGBf8::RangeType::minPixel;
}
template <> __forceinline PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelGRAYi1u &_color){
	return PixelRGBf8(_color.getX());
}
template <> __forceinline PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelRGBi1u &_color){
	return PixelRGBf8(
		(static_cast<double>(_color.getR()) / 255.0),
		(static_cast<double>(_color.getG()) / 255.0),
		(static_cast<double>(_color.getB()) / 255.0))
	;
}
template <> __forceinline PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelYUVf8 &_color){
	return PixelRGBf8(
		(_color.getY() +                           +  1.39652344*_color.getV() ), // See Poynton Eq 25.13 Page 310
		(_color.getY() + -0.34279297*_color.getU() + -0.71134766*_color.getV() ),
		(_color.getY() +  1.76507813*_color.getU()                             ))
	;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> __forceinline PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelGRAYb &_color){
	if(_color.getX()==true){return PixelYUVf8::RangeType::maxPixel;}return PixelYUVf8::RangeType::minPixel;
}
template <> __forceinline PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelGRAYi1u &_color){
	return PixelYUVf8(_color.getX());
}
template <> __forceinline PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelRGBf8 &_color){
	return PixelYUVf8(
		( 0.299     *_color.getR() +  0.587     *_color.getG() +  0.114     *_color.getB() ), // See Poynton Eq 25.12 Page 310
		(-0.16807422*_color.getR() + -0.32996484*_color.getG() +  0.49803906*_color.getB() ),
		( 0.49803906*_color.getR() + -0.41704687*_color.getG() + -0.08099219*_color.getB() ))
	;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> __forceinline PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelYUVf8 &_color){
	return pixel_cast<PixelRGBi1u>(pixel_cast<PixelRGBf8>(_color));//TODO: Make a direct conversion
}

template <> __forceinline PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelRGBi1u &_color){
	return pixel_cast<PixelYUVf8>(pixel_cast<PixelRGBf8>(_color));//TODO: Make a direct conversion
}

template <> __forceinline PixelGRAYb   pixel_cast<PixelGRAYb  >(const PixelGRAYb   & _color){return _color;}
template <> __forceinline PixelGRAYi1u pixel_cast<PixelGRAYi1u>(const PixelGRAYi1u & _color){return _color;}
template <> __forceinline PixelRGBi1u  pixel_cast<PixelRGBi1u >(const PixelRGBi1u  & _color){return _color;}
template <> __forceinline PixelRGBf8   pixel_cast<PixelRGBf8  >(const PixelRGBf8   & _color){return _color;}
template <> __forceinline PixelYUVf8   pixel_cast<PixelYUVf8  >(const PixelYUVf8   & _color){return _color;}

};

#endif
