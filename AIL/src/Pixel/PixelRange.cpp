
#include "PixelRange.h"

namespace Pixel {

const PixelDataType1b   PixelRange_1b::minPixel    = PixelDataType1b(false);
const PixelDataType1b   PixelRange_1b::maxPixel    = PixelDataType1b(true);

const PixelDataType3i1u PixelRange_3i1u::minPixel  = PixelDataType3i1u(0);
const PixelDataType3i1u PixelRange_3i1u::maxPixel  = PixelDataType3i1u(255);

const PixelDataType3i4  PixelRange_3i4_1::minPixel = PixelDataType3i4(0);
const PixelDataType3i4  PixelRange_3i4_1::maxPixel = PixelDataType3i4(255);

const PixelDataType3i4  PixelRange_3i4_2::minPixel = PixelDataType3i4(0);
const PixelDataType3i4  PixelRange_3i4_2::maxPixel = PixelDataType3i4(65535);

const PixelDataType3f4  PixelRange_3f4::minPixel   = PixelDataType3f4(0.0f);
const PixelDataType3f4  PixelRange_3f4::maxPixel   = PixelDataType3f4(1.0f);

const PixelDataType3f8  PixelRange_3f8::minPixel   = PixelDataType3f8(0.0);
const PixelDataType3f8  PixelRange_3f8::maxPixel   = PixelDataType3f8(1.0);

const PixelDataTypeY2_0f8  PixelRange_Y2_0f8::minPixel   = PixelDataTypeY2_0f8(0.0);
const PixelDataTypeY2_0f8  PixelRange_Y2_0f8::maxPixel   = PixelDataTypeY2_0f8(1.0);

}
