
#include "PixelRGBA.h"

namespace Pixel {

template class PixelRGBAbaseType<I1u,I4,PixelRange_AXYZi1u   ,1,2,3,0>;
template class PixelRGBAbaseType<I4 ,I4,PixelRange_AXYZi4    ,1,2,3,0>;
template class PixelRGBAbaseType<I4 ,I4,PixelRange_AXYZi4_i1u,1,2,3,0>;
template class PixelRGBAbaseType<I4 ,I4,PixelRange_AXYZi4_i2u,1,2,3,0>;
template class PixelRGBAbaseType<F8 ,F8,PixelRange_AXYZf8    ,1,2,3,0>;

template class PixelRGBAbaseType<I1u,I4,PixelRange_XYZAi1u   ,0,1,2,3>;
template class PixelRGBAbaseType<I4 ,I4,PixelRange_XYZAi4    ,0,1,2,3>;
template class PixelRGBAbaseType<I4 ,I4,PixelRange_XYZAi4_i1u,0,1,2,3>;
template class PixelRGBAbaseType<I4 ,I4,PixelRange_XYZAi4_i2u,0,1,2,3>;
template class PixelRGBAbaseType<F8 ,F8,PixelRange_XYZAf8    ,0,1,2,3>;

template class PixelRGBAbaseType<I1u,I4,PixelRange_ZYXAi1u   ,3,2,1,0>;
template class PixelRGBAbaseType<I4 ,I4,PixelRange_ZYXAi4    ,3,2,1,0>;
template class PixelRGBAbaseType<I4 ,I4,PixelRange_ZYXAi4_i1u,3,2,1,0>;
template class PixelRGBAbaseType<I4 ,I4,PixelRange_ZYXAi4_i2u,3,2,1,0>;
template class PixelRGBAbaseType<F8 ,F8,PixelRange_ZYXAf8    ,3,2,1,0>;

}
