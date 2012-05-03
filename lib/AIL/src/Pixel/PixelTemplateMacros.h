
#ifndef PIXEL__PixelTemplateMacros_H
#define PIXEL__PixelTemplateMacros_H

#include "PixelY.h"
#include "PixelRGB.h"
#include "PixelRGBA.h"
#include "PixelYUV.h"

#define PIXEL_TYPE_1 Pixel::PixelYb1
#define PIXEL_TYPE_2 Pixel::PixelYi1u
#define PIXEL_TYPE_3 Pixel::PixelYi4

#define PIXEL_TYPE_4 Pixel::PixelRGBi1u
#define PIXEL_TYPE_5 Pixel::PixelRGBi4
#define PIXEL_TYPE_6 Pixel::PixelRGBf8

#define PIXEL_TYPE_7 Pixel::PixelARGBi1u
#define PIXEL_TYPE_8 Pixel::PixelARGBi4

#define PIXEL_TYPE_9 Pixel::PixelYUVf8

#define PIXEL_TYPE_F_1 Pixel::PixelRGBf8
#define PIXEL_TYPE_F_2 Pixel::PixelYUVf8

#define CREATE_PIXELDATA_TEMPLATE_CALLS(x) \
	template class x<Pixel::PixelYb1::DataType>; \
	template class x<Pixel::PixelYi1u::DataType>; \
	template class x<Pixel::PixelYi4::DataType>; \
	\
	template class x<Pixel::PixelRGBi1u::DataType>; \
	template class x<Pixel::PixelRGBi4::DataType>; \
	template class x<Pixel::PixelRGBf8::DataType>; \
	\
	template class x<Pixel::PixelARGBi1u::DataType>; \
	template class x<Pixel::PixelARGBi4::DataType>; \
	\
	template class x<Pixel::PixelYUVf8::DataType>;

#define CREATE_PIXEL_TEMPLATE_CALLS(x) \
	template class x<Pixel::PixelYb1>; \
	template class x<Pixel::PixelYi1u>; \
	template class x<Pixel::PixelYi4>; \
	\
	template class x<Pixel::PixelRGBi1u>; \
	template class x<Pixel::PixelRGBi4>; \
	template class x<Pixel::PixelRGBf8>; \
	\
	template class x<Pixel::PixelARGBi1u>; \
	template class x<Pixel::PixelARGBi4>; \
	\
	template class x<Pixel::PixelYUVf8>;

#define CREATE_PIXEL_TEMPLATE_CALLS_2(x) \
	template class x<Pixel::PixelYb,   Pixel::PixelYb1    >; \
	template class x<Pixel::PixelYb,   Pixel::PixelYi1u   >; \
	template class x<Pixel::PixelYb,   Pixel::PixelYi4    >; \
	template class x<Pixel::PixelYb,   Pixel::PixelRGBi1u >; \
	template class x<Pixel::PixelYb,   Pixel::PixelRGBi4  >; \
	template class x<Pixel::PixelYb,   Pixel::PixelRGBf8  >; \
	template class x<Pixel::PixelYb,   Pixel::PixelARGBi1u>; \
	template class x<Pixel::PixelYb,   Pixel::PixelARGBi4 >; \
	template class x<Pixel::PixelYb,   Pixel::PixelYUVf8  >; \
	\
	template class x<Pixel::PixelRGBi1u,Pixel::PixelYb1    >; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelYi1u   >; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelYi4    >; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelRGBi1u >; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelRGBi4  >; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelRGBf8  >; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelARGBi1u>; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelARGBi4 >; \
	template class x<Pixel::PixelRGBi1u,Pixel::PixelYUVf8  >; \
	\
	template class x<Pixel::PixelRGBf8,Pixel::PixelYb1    >; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelYi1u   >; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelYi4    >; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelRGBi1u >; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelRGBi4  >; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelRGBf8  >; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelARGBi1u>; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelARGBi4 >; \
	template class x<Pixel::PixelRGBf8,Pixel::PixelYUVf8  >; \
	\
	template class x<Pixel::PixelARGBi1u,Pixel::PixelYb1    >; \
	template class x<Pixel::PixelARGBi1u,Pixel::PixelYi1u   >; \
	template class x<Pixel::PixelARGBi1u,Pixel::PixelYi4    >; \
	template class x<Pixel::PixelARGBi1u,Pixel::PixelRGBi1u >; \
	template class x<Pixel::PixelARGBi1u,Pixel::PixelRGBi4  >; \
	template class x<Pixel::PixelARGBi1u,Pixel::PixelRGBf8  >; \
	template class x<Pixel::PixelARGBi1u,Pixel::PixelARGBi1u>; \
	template class x<Pixel::PixelARGBi1u,Pixel::PixelARGBi4 >; \
	template class x<Pixel::PixelARGBi1u,Pixel::PixelYUVf8  >; \
	\
	template class x<Pixel::PixelYUVf8,Pixel::PixelYb1    >; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelYi1u   >; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelYi4    >; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelRGBi1u >; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelRGBi4  >; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelRGBf8  >; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelARGBi1u>; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelARGBi4 >; \
	template class x<Pixel::PixelYUVf8,Pixel::PixelYUVf8  >;

#define CREATE_PIXEL_TEMPLATE_CALLS_F(x) \
	template class x<Pixel::PixelRGBf8>; \
	\
	template class x<Pixel::PixelYUVf8>;


#define TEMPLATE_PIXEL_TYPE_2_DEF_0(x,y) \
	x Pixel::PixelYb1  y ; \
	x Pixel::PixelYi1u y ; \
	x Pixel::PixelYi4  y ; \
	\
	x Pixel::PixelRGBi1u y ; \
	x Pixel::PixelRGBi4  y ; \
	x Pixel::PixelRGBf8  y ; \
	\
	x Pixel::PixelARGBi1u y ; \
	x Pixel::PixelARGBi4  y ; \
	\
	x Pixel::PixelYUVf8 y ;

#define TEMPLATE_PIXEL_TYPE_2_DEF_0_F(x,y) \
	x Pixel::PixelRGBf8 y ; \
	\
	x Pixel::PixelYUVf8 y ;


#define TEMPLATE_PIXEL_TYPE_2_DEF_1(x,y,z,a) \
	x ( y Pixel::PixelYb1  z ) a ; \
	x ( y Pixel::PixelYi1u z ) a ; \
	x ( y Pixel::PixelYi4  z ) a ; \
	\
	x ( y Pixel::PixelRGBi1u z ) a ; \
	x ( y Pixel::PixelRGBi4  z ) a ; \
	x ( y Pixel::PixelRGBf8  z ) a ; \
	\
	x ( y Pixel::PixelARGBi1u z ) a ; \
	x ( y Pixel::PixelARGBi4  z ) a ; \
	\
	x ( y Pixel::PixelYUVf8   z ) a ;

#define TEMPLATE_PIXEL_TYPE_2_DEF_1_F(x,y,z,a) \
	x ( y Pixel::PixelRGBf8 z ) a ; \
	\
	x ( y Pixel::PixelYUVf8 z ) a ;


#endif
