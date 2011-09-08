
#include "PixelRGB.h"

namespace Pixel {

template class PixelRGBbaseType<I1u,PixelRange_3i1u ,2,1,0>;
template class PixelRGBbaseType<I4 ,PixelRange_3i4_1,2,1,0>;
template class PixelRGBbaseType<I4 ,PixelRange_3i4_2,2,1,0>;
template class PixelRGBbaseType<F8 ,PixelRange_3f8  ,2,1,0>;

template class PixelRGBbaseType<I1u,PixelRange_3i1u ,0,1,2>;
template class PixelRGBbaseType<I4 ,PixelRange_3i4_1,0,1,2>;
template class PixelRGBbaseType<I4 ,PixelRange_3i4_2,0,1,2>;
template class PixelRGBbaseType<F8 ,PixelRange_3f8  ,0,1,2>;

}
