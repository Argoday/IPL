
#ifndef PIXEL__PixelTypeID_H
#define PIXEL__PixelTypeID_H

#include <string>

namespace Pixel {

enum class PixelTypeID {

		Yb,

		Yi1u,
		Yi4,
		Yf4,
		Yf8,

		RGBi1u,
		RGBi4,
		RGBf4,
		RGBf8,

		BGRi1u,
		BGRi4,
		BGRf4,
		BGRf8,

		YUVi1u,
		YUVi4,
		YUVf4,
		YUVf8,

		YIQi1u,
		YIQi4,
		YIQf4,
		YIQf8,

		LABi1u,
		LABi4,
		LABf4,
		LABf8,

		HSVi1u,
		HSVi4,
		HSVf4,
		HSVf8,

		RGBAi1u,
		RGBAi4,
		RGBAf4,
		RGBAf8,

};

std::string getTypeName(const PixelTypeID & typeID);

};

#endif
