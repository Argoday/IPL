
#include "PixelTypeID.h"

namespace Pixel {

std::string getTypeName(const PixelTypeID & typeID){
	switch(typeID){
		case PixelTypeID::Yb     : return "Yb"     ; break;
		case PixelTypeID::Yi1u   : return "Yi1u"   ; break;
		case PixelTypeID::Yi4    : return "Yi4"    ; break;
		case PixelTypeID::Yf4    : return "Yf4"    ; break;
		case PixelTypeID::Yf8    : return "Yf8"    ; break;
		case PixelTypeID::RGBi1u : return "RGBi1u" ; break;
		case PixelTypeID::RGBi4  : return "RGBi4"  ; break;
		case PixelTypeID::RGBf4  : return "RGBf4"  ; break;
		case PixelTypeID::RGBf8  : return "RGBf8"  ; break;
		case PixelTypeID::BGRi1u : return "BGRi1u" ; break;
		case PixelTypeID::BGRi4  : return "BGRi4"  ; break;
		case PixelTypeID::BGRf4  : return "BGRf4"  ; break;
		case PixelTypeID::BGRf8  : return "BGRf8"  ; break;
		case PixelTypeID::YUVi1u : return "YUVi1u" ; break;
		case PixelTypeID::YUVi4  : return "YUVi4"  ; break;
		case PixelTypeID::YUVf4  : return "YUVf4"  ; break;
		case PixelTypeID::YUVf8  : return "YUVf8"  ; break;
		case PixelTypeID::YIQi1u : return "YIQi1u" ; break;
		case PixelTypeID::YIQi4  : return "YIQi4"  ; break;
		case PixelTypeID::YIQf4  : return "YIQf4"  ; break;
		case PixelTypeID::YIQf8  : return "YIQf8"  ; break;
		case PixelTypeID::LABi1u : return "LABi1u" ; break;
		case PixelTypeID::LABi4  : return "LABi4"  ; break;
		case PixelTypeID::LABf4  : return "LABf4"  ; break;
		case PixelTypeID::LABf8  : return "LABf8"  ; break;
		case PixelTypeID::HSVi1u : return "HSVi1u" ; break;
		case PixelTypeID::HSVi4  : return "HSVi4"  ; break;
		case PixelTypeID::HSVf4  : return "HSVf4"  ; break;
		case PixelTypeID::HSVf8  : return "HSVf8"  ; break;
		case PixelTypeID::RGBAi1u: return "RGBAi1u"; break;
		case PixelTypeID::RGBAi4 : return "RGBAi4" ; break;
		case PixelTypeID::RGBAf4 : return "RGBAf4" ; break;
		case PixelTypeID::RGBAf8 : return "RGBAf8" ; break;
	}
	return "Error";
}

}
