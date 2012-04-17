
#ifndef PIXEL__PixelTemplateMacros_H
#define PIXEL__PixelTemplateMacros_H

#include "PixelY.h"
#include "PixelRGB.h"
#include "PixelYUV.h"

#define PIXEL_TYPE_1 Pixel::PixelYb
#define PIXEL_TYPE_2 Pixel::PixelYi1u
#define PIXEL_TYPE_3 Pixel::PixelRGBi1u
#define PIXEL_TYPE_4 Pixel::PixelRGBf8
#define PIXEL_TYPE_5 Pixel::PixelYUVf8

#define PIXEL_TYPE_F_1 Pixel::PixelRGBf8
#define PIXEL_TYPE_F_2 Pixel::PixelYUVf8


#define CREATE_PIXEL_TEMPLATE_CALLS(x) \
	template class x<Pixel::PixelYb>; \
	template class x<Pixel::PixelYi1u>; \
	\
	template class x<Pixel::PixelRGBi1u>; \
	template class x<Pixel::PixelRGBf8>; \
	\
	template class x<Pixel::PixelYUVf8>;

#define CREATE_PIXEL_TEMPLATE_CALLS_2(x) \
	template class x<Pixel::PixelYb,   Pixel::PixelYb  >; \
	template class x<Pixel::PixelYb,   Pixel::PixelYi1u>; \
	template class x<Pixel::PixelYb,   Pixel::PixelRGBi1u >; \
	template class x<Pixel::PixelYb,   Pixel::PixelRGBf8  >; \
	template class x<Pixel::PixelYb,   Pixel::PixelYUVf8  >; \
	\
	template class x<Pixel::PixelRGBi1u,Pixel::PixelYb  >; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelYi1u>; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelRGBi1u >; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelRGBf8  >; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelYUVf8  >; \
	\
	template class x<Pixel::PixelRGBf8,Pixel::PixelYb  >; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelYi1u>; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelRGBi1u >; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelRGBf8  >; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelYUVf8  >; \
	\
	template class x<Pixel::PixelYUVf8,Pixel::PixelYb  >; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelYi1u>; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelRGBi1u >; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelRGBf8  >; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelYUVf8  >;

#define CREATE_PIXEL_TEMPLATE_CALLS_F(x) \
	template class x<Pixel::PixelRGBf8>; \
	\
	template class x<Pixel::PixelYUVf8>;


#define TEMPLATE_PIXEL_TYPE_2_DEF_0(x,y) \
	x Pixel::PixelYb  y ; \
	x Pixel::PixelYi1u  y ; \
	\
	x Pixel::PixelRGBi1u y ; \
	x Pixel::PixelRGBf8  y ; \
	\
	x Pixel::PixelYUVf8  y ;

#define TEMPLATE_PIXEL_TYPE_2_DEF_0_F(x,y) \
	x Pixel::PixelRGBf8 y ; \
	\
	x Pixel::PixelYUVf8 y ;


#define TEMPLATE_PIXEL_TYPE_2_DEF_1(x,y,z,a) \
	x ( y Pixel::PixelYb   z ) a ; \
	x ( y Pixel::PixelYi1u z ) a ; \
	\
	x ( y Pixel::PixelRGBi1u  z ) a ; \
	x ( y Pixel::PixelRGBf8   z ) a ; \
	\
	x ( y Pixel::PixelYUVf8   z ) a ;

#define TEMPLATE_PIXEL_TYPE_2_DEF_1_F(x,y,z,a) \
	x ( y Pixel::PixelRGBf8 z ) a ; \
	\
	x ( y Pixel::PixelYUVf8 z ) a ;


#endif
