
#include "PixelRange.h"

namespace Pixel {

const PixelDataType1b1  PixelRange_1b1::minPixel   = PixelDataType1b1(false);
const PixelDataType1b1  PixelRange_1b1::maxPixel   = PixelDataType1b1(true);

const PixelDataType1i1u PixelRange_1i1u::minPixel   = PixelDataType1i1u(0x00);
const PixelDataType1i1u PixelRange_1i1u::maxPixel   = PixelDataType1i1u(0xff);

const PixelDataType3i1u PixelRange_3i1u::minPixel  = PixelDataType3i1u(0x00);
const PixelDataType3i1u PixelRange_3i1u::maxPixel  = PixelDataType3i1u(0xff);

const PixelDataType3i4  PixelRange_3i4_i1u::minPixel = PixelDataType3i4(0x00);
const PixelDataType3i4  PixelRange_3i4_i1u::maxPixel = PixelDataType3i4(0xff);

const PixelDataType3i4  PixelRange_3i4_i2u::minPixel = PixelDataType3i4(0x0000);
const PixelDataType3i4  PixelRange_3i4_i2u::maxPixel = PixelDataType3i4(0xffff);

const PixelDataType3f4  PixelRange_3f4::minPixel   = PixelDataType3f4(0.0f);
const PixelDataType3f4  PixelRange_3f4::maxPixel   = PixelDataType3f4(1.0f);

const PixelDataType3f8  PixelRange_3f8::minPixel   = PixelDataType3f8(0.0);
const PixelDataType3f8  PixelRange_3f8::maxPixel   = PixelDataType3f8(1.0);

const PixelDataTypeY2_0f8  PixelRange_Y2_0f8::minPixel   = PixelDataTypeY2_0f8(0.0);
const PixelDataTypeY2_0f8  PixelRange_Y2_0f8::maxPixel   = PixelDataTypeY2_0f8(1.0);

}
