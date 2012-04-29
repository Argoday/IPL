
#include "PixelRGB.h"

namespace Pixel {

template class PixelRGBbaseType<I1u,I4,PixelRange_3i1u   ,2,1,0>;
template class PixelRGBbaseType<I4 ,I4,PixelRange_3i4    ,2,1,0>;
template class PixelRGBbaseType<I4 ,I4,PixelRange_3i4_i1u,2,1,0>;
template class PixelRGBbaseType<I4 ,I4,PixelRange_3i4_i2u,2,1,0>;
template class PixelRGBbaseType<F8 ,F8,PixelRange_3f8    ,2,1,0>;

template class PixelRGBbaseType<I1u,I4,PixelRange_3i1u   ,0,1,2>;
template class PixelRGBbaseType<I4 ,I4,PixelRange_3i4    ,0,1,2>;
template class PixelRGBbaseType<I4 ,I4,PixelRange_3i4_i1u,0,1,2>;
template class PixelRGBbaseType<I4 ,I4,PixelRange_3i4_i2u,0,1,2>;
template class PixelRGBbaseType<F8 ,F8,PixelRange_3f8    ,0,1,2>;

}
