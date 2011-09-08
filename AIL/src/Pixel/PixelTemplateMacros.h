
#ifndef PIXEL__PixelTemplateMacros_H
#define PIXEL__PixelTemplateMacros_H

#include "PixelGRAY.h"
#include "PixelRGB.h"
#include "PixelYUV.h"

#define PIXEL_TYPE_1 Pixel::PixelGRAYb
#define PIXEL_TYPE_2 Pixel::PixelRGBf8
#define PIXEL_TYPE_3 Pixel::PixelYUVf8

#define PIXEL_TYPE_F_1 Pixel::PixelRGBf8
#define PIXEL_TYPE_F_2 Pixel::PixelYUVf8


#define CREATE_PIXEL_TEMPLATE_CALLS(x) \
	template class x<Pixel::PixelGRAYb>; \
	\
	template class x<Pixel::PixelRGBf8>; \
	\
	template class x<Pixel::PixelYUVf8>;

#define CREATE_PIXEL_TEMPLATE_CALLS_F(x) \
	template class x<Pixel::PixelRGBf8>; \
	\
	template class x<Pixel::PixelYUVf8>;


#define TEMPLATE_PIXEL_TYPE_2_DEF_0(x,y) \
	x Pixel::PixelGRAYb y ; \
	\
	x Pixel::PixelRGBf8 y ; \
	\
	x Pixel::PixelYUVf8 y ;

#define TEMPLATE_PIXEL_TYPE_2_DEF_0_F(x,y) \
	x Pixel::PixelRGBf8 y ; \
	\
	x Pixel::PixelYUVf8 y ;


#define TEMPLATE_PIXEL_TYPE_2_DEF_1(x,y,z,a) \
	x ( y Pixel::PixelGRAYb z ) a ; \
	\
	x ( y Pixel::PixelRGBf8 z ) a ; \
	\
	x ( y Pixel::PixelYUVf8 z ) a ;

#define TEMPLATE_PIXEL_TYPE_2_DEF_1_F(x,y,z,a) \
	x ( y Pixel::PixelGRAYb z ) a ; \
	\
	x ( y Pixel::PixelRGBf8 z ) a ; \
	\
	x ( y Pixel::PixelYUVf8 z ) a ;


#endif
