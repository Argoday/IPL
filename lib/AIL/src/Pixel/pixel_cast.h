
#ifndef PIXEL__pixel_cast_H
#define PIXEL__pixel_cast_H

#include "PixelY.h"
#include "PixelRGB.h"
#include "PixelRGBA.h"
#include "PixelYUV.h"

namespace Pixel {

template <
	typename DstPixelType,
	typename SrcPixelType
> class pixel_cast_alg {
	public:
		static FINLINE void process(DstPixelType * const & dstPixel,const SrcPixelType * const & srcPixel){
			(*dstPixel) = pixel_cast<DstPixelType>(*srcPixel);
		}
};

// TODO: split these into seperate header files
template <typename DstPixelType,typename SrcPixelType> FINLINE DstPixelType pixel_cast(const SrcPixelType & color);

template <> FINLINE PixelYb1 pixel_cast<PixelYb1>(const PixelYi1u & _color){
	if(_color.getY()>128){return PixelYb1(true);}return PixelYb1(false);
}
template <> FINLINE PixelYb1 pixel_cast<PixelYb1>(const PixelYi4 & _color){
	if(_color.getY()>128){return PixelYb1(true);}return PixelYb1(false);
}
template <> FINLINE PixelYb1 pixel_cast<PixelYb1>(const PixelRGBi1u & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	if(tempY>127500){return PixelYb1(true);}return PixelYb1(false); // 127500 = 0.5 * 255 * 1000
}
template <> FINLINE PixelYb1 pixel_cast<PixelYb1>(const PixelRGBi4 & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	if(tempY>127500){return PixelYb1(true);}return PixelYb1(false); // 127500 = 0.5 * 255 * 1000
}
template <> FINLINE PixelYb1 pixel_cast<PixelYb1>(const PixelRGBf8 & _color){
	F8 tempY;
	tempY = _color.getR()*0.299; // TODO: Check the asm generated for this line
	tempY+= _color.getG()*0.587;
	tempY+= _color.getB()*0.114;
	if(tempY>0.5){return PixelYb1(true);}return PixelYb1(false);
}
template <> FINLINE PixelYb1 pixel_cast<PixelYb1>(const PixelARGBi1u & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	if(tempY>127500){return PixelYb1(true);}return PixelYb1(false); // 127500 = 0.5 * 255 * 1000
}
template <> FINLINE PixelYb1 pixel_cast<PixelYb1>(const PixelARGBi4 & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	if(tempY>127500){return PixelYb1(true);}return PixelYb1(false); // 127500 = 0.5 * 255 * 1000
}
template <> FINLINE PixelYb1 pixel_cast<PixelYb1>(const PixelYUVf8 & _color){
	if(_color.getY()>0.5){return PixelYb1(true);}return PixelYb1(false);
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> FINLINE PixelYi1u pixel_cast<PixelYi1u>(const PixelYb1 & _color){
	if(_color.getY()==true){return PixelYi1u::RangeType::maxPixel;}return PixelYi1u::RangeType::minPixel;
}
template <> FINLINE PixelYi1u pixel_cast<PixelYi1u>(const PixelYi4 & _color){return PixelYi1u(_color.getY());}
template <> FINLINE PixelYi1u pixel_cast<PixelYi1u>(const PixelRGBi4 & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	return PixelYi1u(static_cast<I1u>(tempY/1000));//TODO: Redo the calculation so that this can be a shift (aka /1024)
}
template <> FINLINE PixelYi1u pixel_cast<PixelYi1u>(const PixelRGBi1u & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	return PixelYi1u(static_cast<I1u>(tempY/1000));//TODO: Redo the calculation so that this can be a shift (aka /1024)
}
template <> FINLINE PixelYi1u pixel_cast<PixelYi1u>(const PixelRGBf8 & _color){
	F8 tempY;
	tempY = _color.getR()*0.299; // TODO: Check the asm generated for this line
	tempY+= _color.getG()*0.587;
	tempY+= _color.getB()*0.114;
	return PixelYi1u(static_cast<I1u>(tempY*255.0));
}
template <> FINLINE PixelYi1u pixel_cast<PixelYi1u>(const PixelARGBi1u & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	return PixelYi1u(static_cast<I1u>(tempY/1000));//TODO: Redo the calculation so that this can be a shift (aka /1024)
}
template <> FINLINE PixelYi1u pixel_cast<PixelYi1u>(const PixelARGBi4 & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	return PixelYi1u(static_cast<I1u>(tempY/1000));//TODO: Redo the calculation so that this can be a shift (aka /1024)
}
template <> FINLINE PixelYi1u pixel_cast<PixelYi1u>(const PixelYUVf8 & _color){
	return PixelYi1u(static_cast<I1u>(_color.getY()));
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> FINLINE PixelYi4 pixel_cast<PixelYi4>(const PixelYb1 & _color){
	if(_color.getY()==true){return PixelYi4::RangeType::maxPixel;}return PixelYi4::RangeType::minPixel;
}
template <> FINLINE PixelYi4 pixel_cast<PixelYi4>(const PixelYi1u & _color){
	return PixelYi4(_color.getY());
}
template <> FINLINE PixelYi4 pixel_cast<PixelYi4>(const PixelRGBi4 & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	return PixelYi4(static_cast<I4>(tempY/1000));//TODO: Redo the calculation so that this can be a shift (aka /1024)
}
template <> FINLINE PixelYi4 pixel_cast<PixelYi4>(const PixelRGBi1u & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	return PixelYi4(static_cast<I4>(tempY/1000));//TODO: Redo the calculation so that this can be a shift (aka /1024)
}
template <> FINLINE PixelYi4 pixel_cast<PixelYi4>(const PixelRGBf8 & _color){
	F8 tempY;
	tempY = _color.getR()*0.299; // TODO: Check the asm generated for this line
	tempY+= _color.getG()*0.587;
	tempY+= _color.getB()*0.114;
	return PixelYi4(static_cast<I4>(tempY*255.0));
}
template <> FINLINE PixelYi4 pixel_cast<PixelYi4>(const PixelARGBi1u & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	return PixelYi4(static_cast<I4>(tempY/1000));//TODO: Redo the calculation so that this can be a shift (aka /1024)
}
template <> FINLINE PixelYi4 pixel_cast<PixelYi4>(const PixelARGBi4 & _color){
	I8 tempY;
	tempY = static_cast<I8>(_color.getR())*299; // TODO: Check the asm generated for this line
	tempY+= static_cast<I8>(_color.getG())*587;
	tempY+= static_cast<I8>(_color.getB())*114;
	return PixelYi4(static_cast<I4>(tempY/1000));//TODO: Redo the calculation so that this can be a shift (aka /1024)
}
template <> FINLINE PixelYi4 pixel_cast<PixelYi4>(const PixelYUVf8 & _color){
	return PixelYi4(static_cast<I4>(_color.getY()));
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> FINLINE PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelYb1 & _color){
	if(_color.getY()==true){return PixelRGBi1u::RangeType::maxPixel;}return PixelRGBi1u::RangeType::minPixel;
}
template <> FINLINE PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelYi1u & _color){
	return PixelRGBi1u(_color.getY());
}
template <> FINLINE PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelYi4 & _color){
	return PixelRGBi1u(_color.getY());
}
template <> FINLINE PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelRGBf8 & _color){
	return PixelRGBi1u(
		static_cast<I1u>((_color.getR()*255.0)),
		static_cast<I1u>((_color.getG()*255.0)),
		static_cast<I1u>((_color.getB()*255.0)))
	;
}
template <> FINLINE PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelRGBi4   & _color){return PixelRGBi1u(_color.getR(),_color.getG(),_color.getB());}
template <> FINLINE PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelARGBi1u & _color){return PixelRGBi1u(_color.getR(),_color.getG(),_color.getB());}
template <> FINLINE PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelARGBi4  & _color){return PixelRGBi1u(_color.getR(),_color.getG(),_color.getB());}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> FINLINE PixelRGBi4 pixel_cast<PixelRGBi4>(const PixelYb1 & _color){
	if(_color.getY()==true){return PixelRGBi4::RangeType::maxPixel;}return PixelRGBi4::RangeType::minPixel;
}
template <> FINLINE PixelRGBi4 pixel_cast<PixelRGBi4>(const PixelYi1u & _color){
	return PixelRGBi4(_color.getY());
}
template <> FINLINE PixelRGBi4 pixel_cast<PixelRGBi4>(const PixelYi4 & _color){
	return PixelRGBi4(_color.getY());
}
template <> FINLINE PixelRGBi4 pixel_cast<PixelRGBi4>(const PixelRGBf8 & _color){
	return PixelRGBi4(
		static_cast<I1u>((_color.getR()*255.0)),
		static_cast<I1u>((_color.getG()*255.0)),
		static_cast<I1u>((_color.getB()*255.0)))
	;
}
template <> FINLINE PixelRGBi4 pixel_cast<PixelRGBi4>(const PixelRGBi1u  & _color){return PixelRGBi4(_color.getR(),_color.getG(),_color.getB());}
template <> FINLINE PixelRGBi4 pixel_cast<PixelRGBi4>(const PixelARGBi1u & _color){return PixelRGBi4(_color.getR(),_color.getG(),_color.getB());}
template <> FINLINE PixelRGBi4 pixel_cast<PixelRGBi4>(const PixelARGBi4  & _color){return PixelRGBi4(_color.getR(),_color.getG(),_color.getB());}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> FINLINE PixelARGBi1u pixel_cast<PixelARGBi1u>(const PixelYb1 & _color){
	if(_color.getY()==true){return PixelARGBi1u::RangeType::maxPixel;}return PixelARGBi1u(0,0,0,0xff);
}
template <> FINLINE PixelARGBi1u pixel_cast<PixelARGBi1u>(const PixelYi1u & _color){return PixelARGBi1u(_color.getY(),_color.getY(),_color.getY(),0xff);}
template <> FINLINE PixelARGBi1u pixel_cast<PixelARGBi1u>(const PixelYi4  & _color){return PixelARGBi1u(_color.getY(),_color.getY(),_color.getY(),0xff);}

template <> FINLINE PixelARGBi1u pixel_cast<PixelARGBi1u>(const PixelRGBf8 & _color){
	return PixelARGBi1u(
		static_cast<I1u>((_color.getR()*255.0)),
		static_cast<I1u>((_color.getG()*255.0)),
		static_cast<I1u>((_color.getB()*255.0)),
		0xff)
	;
}
template <> FINLINE PixelARGBi1u pixel_cast<PixelARGBi1u>(const PixelRGBi1u & _color){return PixelARGBi1u(_color.getR(),_color.getG(),_color.getB(),0xff);}
template <> FINLINE PixelARGBi1u pixel_cast<PixelARGBi1u>(const PixelRGBi4  & _color){return PixelARGBi1u(_color.getR(),_color.getG(),_color.getB(),0xff);}
template <> FINLINE PixelARGBi1u pixel_cast<PixelARGBi1u>(const PixelARGBi4 & _color){return PixelARGBi1u(_color.getR(),_color.getG(),_color.getB(),_color.getA());}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> FINLINE PixelARGBi4 pixel_cast<PixelARGBi4>(const PixelYb1 & _color){
	if(_color.getY()==true){return PixelARGBi4::RangeType::maxPixel;}return PixelARGBi4(0,0,0,0xff);
}
template <> FINLINE PixelARGBi4 pixel_cast<PixelARGBi4>(const PixelYi1u & _color){return PixelARGBi4(_color.getY(),_color.getY(),_color.getY(),0xff);}
template <> FINLINE PixelARGBi4 pixel_cast<PixelARGBi4>(const PixelYi4  & _color){return PixelARGBi4(_color.getY(),_color.getY(),_color.getY(),0xff);}

template <> FINLINE PixelARGBi4 pixel_cast<PixelARGBi4>(const PixelRGBf8 & _color){
	return PixelARGBi4(
		static_cast<I1u>((_color.getR()*255.0)),
		static_cast<I1u>((_color.getG()*255.0)),
		static_cast<I1u>((_color.getB()*255.0)),
		0xff)
	;
}
template <> FINLINE PixelARGBi4 pixel_cast<PixelARGBi4>(const PixelRGBi1u  & _color){return PixelARGBi4(_color.getR(),_color.getG(),_color.getB(),0xff);}
template <> FINLINE PixelARGBi4 pixel_cast<PixelARGBi4>(const PixelRGBi4   & _color){return PixelARGBi4(_color.getR(),_color.getG(),_color.getB(),0xff);}
template <> FINLINE PixelARGBi4 pixel_cast<PixelARGBi4>(const PixelARGBi1u & _color){return PixelARGBi4(_color.getR(),_color.getG(),_color.getB(),_color.getA());}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> FINLINE PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelYb1 & _color){
	if(_color.getY()==true){return PixelRGBf8::RangeType::maxPixel;}return PixelRGBf8::RangeType::minPixel;
}
template <> FINLINE PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelYi1u & _color){return PixelRGBf8(_color.getY());}
template <> FINLINE PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelYi4  & _color){return PixelRGBf8(_color.getY());}
template <> FINLINE PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelRGBi1u & _color){
	return PixelRGBf8(
		(static_cast<F8>(_color.getR()) / 255.0),
		(static_cast<F8>(_color.getG()) / 255.0),
		(static_cast<F8>(_color.getB()) / 255.0))
	;
}
template <> FINLINE PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelRGBi4 & _color){
	return PixelRGBf8(
		(static_cast<F8>(_color.getR()) / 255.0),
		(static_cast<F8>(_color.getG()) / 255.0),
		(static_cast<F8>(_color.getB()) / 255.0))
	;
}
template <> FINLINE PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelARGBi1u & _color){
	return PixelRGBf8(
		(static_cast<F8>(_color.getR()) / 255.0),
		(static_cast<F8>(_color.getG()) / 255.0),
		(static_cast<F8>(_color.getB()) / 255.0))
	;
}
template <> FINLINE PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelARGBi4 & _color){
	return PixelRGBf8(
		(static_cast<F8>(_color.getR()) / 255.0),
		(static_cast<F8>(_color.getG()) / 255.0),
		(static_cast<F8>(_color.getB()) / 255.0))
	;
}
template <> FINLINE PixelRGBf8 pixel_cast<PixelRGBf8>(const PixelYUVf8 & _color){
	return PixelRGBf8(
		(_color.getY() +                         +  1.402   *_color.getV()), // See Poynton Y`PbPr http://www.poynton.com/notes/colour_and_gamma/ColorFAQ.html#RTFToC28
		(_color.getY() + -0.344136*_color.getU() + -0.714136*_color.getV()),
		(_color.getY() +  1.772   *_color.getU()                          ))
	;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> FINLINE PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelYb1 & _color){
	if(_color.getY()==true){return PixelYUVf8::RangeType::maxPixel;}return PixelYUVf8::RangeType::minPixel;
}
template <> FINLINE PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelYi1u & _color){return PixelYUVf8(_color.getY());}
template <> FINLINE PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelYi4  & _color){return PixelYUVf8(_color.getY());}
template <> FINLINE PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelRGBf8 & _color){
	PixelYUVf8 newPixel;
	newPixel.getY() =  0.299    * _color.getR() +  0.587    * _color.getG() +  0.114    * _color.getB(); // See Poynton Y`PbPr http://www.poynton.com/notes/colour_and_gamma/ColorFAQ.html#RTFToC28
	newPixel.getU() = -0.168736 * _color.getR() + -0.331264 * _color.getG() +  0.5      * _color.getB();
	newPixel.getV() =  0.5      * _color.getR() + -0.418688 * _color.getG() + -0.081312 * _color.getB();
	return newPixel;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
template <> FINLINE PixelRGBi1u pixel_cast<PixelRGBi1u>(const PixelYUVf8 & _color){
	return pixel_cast<PixelRGBi1u>(pixel_cast<PixelRGBf8>(_color));//TODO: Make a direct conversion
}
template <> FINLINE PixelARGBi1u pixel_cast<PixelARGBi1u>(const PixelYUVf8 & _color){
	return pixel_cast<PixelARGBi1u>(pixel_cast<PixelRGBf8>(_color));//TODO: Make a direct conversion
}
template <> FINLINE PixelRGBi4 pixel_cast<PixelRGBi4>(const PixelYUVf8 & _color){
	return pixel_cast<PixelRGBi4>(pixel_cast<PixelRGBf8>(_color));//TODO: Make a direct conversion
}
template <> FINLINE PixelARGBi4 pixel_cast<PixelARGBi4>(const PixelYUVf8 & _color){
	return pixel_cast<PixelARGBi4>(pixel_cast<PixelRGBf8>(_color));//TODO: Make a direct conversion
}

template <> FINLINE PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelRGBi1u & _color){
	return pixel_cast<PixelYUVf8>(pixel_cast<PixelRGBf8>(_color));//TODO: Make a direct conversion
}
template <> FINLINE PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelARGBi1u & _color){
	return pixel_cast<PixelYUVf8>(pixel_cast<PixelRGBf8>(_color));//TODO: Make a direct conversion
}
template <> FINLINE PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelRGBi4 & _color){
	return pixel_cast<PixelYUVf8>(pixel_cast<PixelRGBf8>(_color));//TODO: Make a direct conversion
}
template <> FINLINE PixelYUVf8 pixel_cast<PixelYUVf8>(const PixelARGBi4 & _color){
	return pixel_cast<PixelYUVf8>(pixel_cast<PixelRGBf8>(_color));//TODO: Make a direct conversion
}

template <> FINLINE PixelYb1     pixel_cast<PixelYb1    >(const PixelYb1     & _color){return _color;}
template <> FINLINE PixelYi1u    pixel_cast<PixelYi1u   >(const PixelYi1u    & _color){return _color;}
template <> FINLINE PixelYi4     pixel_cast<PixelYi4    >(const PixelYi4     & _color){return _color;}
template <> FINLINE PixelRGBi1u  pixel_cast<PixelRGBi1u >(const PixelRGBi1u  & _color){return _color;}
template <> FINLINE PixelRGBi4   pixel_cast<PixelRGBi4  >(const PixelRGBi4   & _color){return _color;}
template <> FINLINE PixelRGBf8   pixel_cast<PixelRGBf8  >(const PixelRGBf8   & _color){return _color;}
template <> FINLINE PixelARGBi1u pixel_cast<PixelARGBi1u>(const PixelARGBi1u & _color){return _color;}
template <> FINLINE PixelARGBi4  pixel_cast<PixelARGBi4 >(const PixelARGBi4  & _color){return _color;}
template <> FINLINE PixelYUVf8   pixel_cast<PixelYUVf8  >(const PixelYUVf8   & _color){return _color;}

};

#endif
