
#include "PixelRange.h"

namespace Pixel {


///////////////////////////////////////////////////////////////////

const PixelDataType1b1  PixelRange_1b1::minPixel   = PixelDataType1b1(false);
const PixelDataType1b1  PixelRange_1b1::maxPixel   = PixelDataType1b1(true);
const B1                PixelRange_1b1::minValue   = B1(false);
const B1                PixelRange_1b1::maxValue   = B1(true);

const PixelDataType1i1u PixelRange_1i1u::minPixel  = PixelDataType1i1u(0x00);
const PixelDataType1i1u PixelRange_1i1u::maxPixel  = PixelDataType1i1u(0xff);
const I1u               PixelRange_1i1u::minValue  = I1u(0x00);
const I1u               PixelRange_1i1u::maxValue  = I1u(0xff);

const PixelDataType1i4  PixelRange_1i4::minPixel   = PixelDataType1i4(0x00);
const PixelDataType1i4  PixelRange_1i4::maxPixel   = PixelDataType1i4(0xff);
const I4                PixelRange_1i4::minValue   = I4(0x00);
const I4                PixelRange_1i4::maxValue   = I4(0xff);

const PixelDataType1i4  PixelRange_1i4_i1u::minPixel   = PixelDataType1i4(0x00);
const PixelDataType1i4  PixelRange_1i4_i1u::maxPixel   = PixelDataType1i4(0xff);
const I4                PixelRange_1i4_i1u::minValue   = I4(0x00);
const I4                PixelRange_1i4_i1u::maxValue   = I4(0xff);

///////////////////////////////////////////////////////////////////

const PixelDataType3i1u PixelRange_3i1u::minPixel  = PixelDataType3i1u(0x00);
const PixelDataType3i1u PixelRange_3i1u::maxPixel  = PixelDataType3i1u(0xff);
const I1u               PixelRange_3i1u::minValue  = I1u(0x00);
const I1u               PixelRange_3i1u::maxValue  = I1u(0xff);

const PixelDataType3i4  PixelRange_3i4::minPixel   = PixelDataType3i4(0x00);
const PixelDataType3i4  PixelRange_3i4::maxPixel   = PixelDataType3i4(0xff);
const I4                PixelRange_3i4::minValue   = I4(0x00);
const I4                PixelRange_3i4::maxValue   = I4(0xff);

const PixelDataType3i4  PixelRange_3i4_i1u::minPixel = PixelDataType3i4(0x00);
const PixelDataType3i4  PixelRange_3i4_i1u::maxPixel = PixelDataType3i4(0xff);
const I4                PixelRange_3i4_i1u::minValue = I4(0x00);
const I4                PixelRange_3i4_i1u::maxValue = I4(0xff);

const PixelDataType3i4  PixelRange_3i4_i2u::minPixel = PixelDataType3i4(0x0000);
const PixelDataType3i4  PixelRange_3i4_i2u::maxPixel = PixelDataType3i4(0xffff);
const I4                PixelRange_3i4_i2u::minValue = I4(0x0000);
const I4                PixelRange_3i4_i2u::maxValue = I4(0xffff);

const PixelDataType3f4  PixelRange_3f4::minPixel   = PixelDataType3f4(0.0f);
const PixelDataType3f4  PixelRange_3f4::maxPixel   = PixelDataType3f4(1.0f);
const F4                PixelRange_3f4::minValue   = F4(0.0f);
const F4                PixelRange_3f4::maxValue   = F4(1.0f);

const PixelDataType3f8  PixelRange_3f8::minPixel   = PixelDataType3f8(0.0);
const PixelDataType3f8  PixelRange_3f8::maxPixel   = PixelDataType3f8(1.0);
const F8                PixelRange_3f8::minValue   = F8(0.0);
const F8                PixelRange_3f8::maxValue   = F8(1.0);

///////////////////////////////////////////////////////////////////

const PixelDataTypeXYZAi1u PixelRange_XYZAi1u::minPixel  = PixelDataTypeXYZAi1u(0x00);
const PixelDataTypeXYZAi1u PixelRange_XYZAi1u::maxPixel  = PixelDataTypeXYZAi1u(0xff);
const I1u                  PixelRange_XYZAi1u::minValue  = I1u(0x00);
const I1u                  PixelRange_XYZAi1u::maxValue  = I1u(0xff);

const PixelDataTypeXYZAi4 PixelRange_XYZAi4::minPixel   = PixelDataTypeXYZAi4(0x00);
const PixelDataTypeXYZAi4 PixelRange_XYZAi4::maxPixel   = PixelDataTypeXYZAi4(0xff);
const I4                  PixelRange_XYZAi4::minValue   = I4(0x00);
const I4                  PixelRange_XYZAi4::maxValue   = I4(0xff);

const PixelDataTypeXYZAi4 PixelRange_XYZAi4_i1u::minPixel = PixelDataTypeXYZAi4(0x00);
const PixelDataTypeXYZAi4 PixelRange_XYZAi4_i1u::maxPixel = PixelDataTypeXYZAi4(0xff);
const I4                  PixelRange_XYZAi4_i1u::minValue = I4(0x00);
const I4                  PixelRange_XYZAi4_i1u::maxValue = I4(0xff);

const PixelDataTypeXYZAi4 PixelRange_XYZAi4_i2u::minPixel = PixelDataTypeXYZAi4(0x0000);
const PixelDataTypeXYZAi4 PixelRange_XYZAi4_i2u::maxPixel = PixelDataTypeXYZAi4(0xffff);
const I4                  PixelRange_XYZAi4_i2u::minValue = I4(0x0000);
const I4                  PixelRange_XYZAi4_i2u::maxValue = I4(0xffff);

const PixelDataTypeXYZAf4 PixelRange_XYZAf4::minPixel   = PixelDataTypeXYZAf4(0.0f);
const PixelDataTypeXYZAf4 PixelRange_XYZAf4::maxPixel   = PixelDataTypeXYZAf4(1.0f);
const F4                  PixelRange_XYZAf4::minValue   = F4(0.0f);
const F4                  PixelRange_XYZAf4::maxValue   = F4(1.0f);

const PixelDataTypeXYZAf8 PixelRange_XYZAf8::minPixel   = PixelDataTypeXYZAf8(0.0);
const PixelDataTypeXYZAf8 PixelRange_XYZAf8::maxPixel   = PixelDataTypeXYZAf8(1.0);
const F8                  PixelRange_XYZAf8::minValue   = F8(0.0);
const F8                  PixelRange_XYZAf8::maxValue   = F8(1.0);

///////////////////////////////////////////////////////////////////

const PixelDataTypeAXYZi1u PixelRange_AXYZi1u::minPixel  = PixelDataTypeAXYZi1u(0x00);
const PixelDataTypeAXYZi1u PixelRange_AXYZi1u::maxPixel  = PixelDataTypeAXYZi1u(0xff);
const I1u                  PixelRange_AXYZi1u::minValue  = I1u(0x00);
const I1u                  PixelRange_AXYZi1u::maxValue  = I1u(0xff);

const PixelDataTypeAXYZi4 PixelRange_AXYZi4::minPixel   = PixelDataTypeAXYZi4(0x00);
const PixelDataTypeAXYZi4 PixelRange_AXYZi4::maxPixel   = PixelDataTypeAXYZi4(0xff);
const I4                  PixelRange_AXYZi4::minValue   = I4(0x00);
const I4                  PixelRange_AXYZi4::maxValue   = I4(0xff);

const PixelDataTypeAXYZi4 PixelRange_AXYZi4_i1u::minPixel = PixelDataTypeAXYZi4(0x00);
const PixelDataTypeAXYZi4 PixelRange_AXYZi4_i1u::maxPixel = PixelDataTypeAXYZi4(0xff);
const I4                  PixelRange_AXYZi4_i1u::minValue = I4(0x00);
const I4                  PixelRange_AXYZi4_i1u::maxValue = I4(0xff);

const PixelDataTypeAXYZi4 PixelRange_AXYZi4_i2u::minPixel = PixelDataTypeAXYZi4(0x0000);
const PixelDataTypeAXYZi4 PixelRange_AXYZi4_i2u::maxPixel = PixelDataTypeAXYZi4(0xffff);
const I4                  PixelRange_AXYZi4_i2u::minValue = I4(0x0000);
const I4                  PixelRange_AXYZi4_i2u::maxValue = I4(0xffff);

const PixelDataTypeAXYZf4 PixelRange_AXYZf4::minPixel   = PixelDataTypeAXYZf4(0.0f);
const PixelDataTypeAXYZf4 PixelRange_AXYZf4::maxPixel   = PixelDataTypeAXYZf4(1.0f);
const F4                  PixelRange_AXYZf4::minValue   = F4(0.0f);
const F4                  PixelRange_AXYZf4::maxValue   = F4(1.0f);

const PixelDataTypeAXYZf8 PixelRange_AXYZf8::minPixel   = PixelDataTypeAXYZf8(0.0);
const PixelDataTypeAXYZf8 PixelRange_AXYZf8::maxPixel   = PixelDataTypeAXYZf8(1.0);
const F8                  PixelRange_AXYZf8::minValue   = F8(0.0);
const F8                  PixelRange_AXYZf8::maxValue   = F8(1.0);

///////////////////////////////////////////////////////////////////

const PixelDataTypeZYXAi1u PixelRange_ZYXAi1u::minPixel  = PixelDataTypeZYXAi1u(0x00);
const PixelDataTypeZYXAi1u PixelRange_ZYXAi1u::maxPixel  = PixelDataTypeZYXAi1u(0xff);
const I1u                  PixelRange_ZYXAi1u::minValue  = I1u(0x00);
const I1u                  PixelRange_ZYXAi1u::maxValue  = I1u(0xff);

const PixelDataTypeZYXAi4 PixelRange_ZYXAi4::minPixel   = PixelDataTypeZYXAi4(0x00);
const PixelDataTypeZYXAi4 PixelRange_ZYXAi4::maxPixel   = PixelDataTypeZYXAi4(0xff);
const I4                  PixelRange_ZYXAi4::minValue   = I4(0x00);
const I4                  PixelRange_ZYXAi4::maxValue   = I4(0xff);

const PixelDataTypeZYXAi4 PixelRange_ZYXAi4_i1u::minPixel = PixelDataTypeZYXAi4(0x00);
const PixelDataTypeZYXAi4 PixelRange_ZYXAi4_i1u::maxPixel = PixelDataTypeZYXAi4(0xff);
const I4                  PixelRange_ZYXAi4_i1u::minValue = I4(0x00);
const I4                  PixelRange_ZYXAi4_i1u::maxValue = I4(0xff);

const PixelDataTypeZYXAi4 PixelRange_ZYXAi4_i2u::minPixel = PixelDataTypeZYXAi4(0x0000);
const PixelDataTypeZYXAi4 PixelRange_ZYXAi4_i2u::maxPixel = PixelDataTypeZYXAi4(0xffff);
const I4                  PixelRange_ZYXAi4_i2u::minValue = I4(0x0000);
const I4                  PixelRange_ZYXAi4_i2u::maxValue = I4(0xffff);

const PixelDataTypeZYXAf4 PixelRange_ZYXAf4::minPixel   = PixelDataTypeZYXAf4(0.0f);
const PixelDataTypeZYXAf4 PixelRange_ZYXAf4::maxPixel   = PixelDataTypeZYXAf4(1.0f);
const F4                  PixelRange_ZYXAf4::minValue   = F4(0.0f);
const F4                  PixelRange_ZYXAf4::maxValue   = F4(1.0f);

const PixelDataTypeZYXAf8 PixelRange_ZYXAf8::minPixel   = PixelDataTypeZYXAf8(0.0);
const PixelDataTypeZYXAf8 PixelRange_ZYXAf8::maxPixel   = PixelDataTypeZYXAf8(1.0);
const F8                  PixelRange_ZYXAf8::minValue   = F8(0.0);
const F8                  PixelRange_ZYXAf8::maxValue   = F8(1.0);

///////////////////////////////////////////////////////////////////

const PixelDataTypeY2_0i2  PixelRange_Y2_0i2_i1u::minPixel = PixelDataTypeY2_0i2(0x00);
const PixelDataTypeY2_0i2  PixelRange_Y2_0i2_i1u::maxPixel = PixelDataTypeY2_0i2(0xff);
const I2                   PixelRange_Y2_0i2_i1u::minValue = I2(0x00);
const I2                   PixelRange_Y2_0i2_i1u::maxValue = I2(0xff);

const PixelDataTypeY2_0i2  PixelRange_Y2_0i2::minPixel = PixelDataTypeY2_0i2(0x0000);
const PixelDataTypeY2_0i2  PixelRange_Y2_0i2::maxPixel = PixelDataTypeY2_0i2(0x7fff);
const I2                   PixelRange_Y2_0i2::minValue = I2(0x0000);
const I2                   PixelRange_Y2_0i2::maxValue = I2(0xffff);

const PixelDataTypeY2_0i4  PixelRange_Y2_0i4::minPixel = PixelDataTypeY2_0i4(0x00);
const PixelDataTypeY2_0i4  PixelRange_Y2_0i4::maxPixel = PixelDataTypeY2_0i4(0xff);
const I4                   PixelRange_Y2_0i4::minValue = I4(0x00);
const I4                   PixelRange_Y2_0i4::maxValue = I4(0xff);

const PixelDataTypeY2_0i4  PixelRange_Y2_0i4_i1u::minPixel = PixelDataTypeY2_0i4(0x00);
const PixelDataTypeY2_0i4  PixelRange_Y2_0i4_i1u::maxPixel = PixelDataTypeY2_0i4(0xff);
const I4                   PixelRange_Y2_0i4_i1u::minValue = I4(0x00);
const I4                   PixelRange_Y2_0i4_i1u::maxValue = I4(0xff);

const PixelDataTypeY2_0i4  PixelRange_Y2_0i4_i2u::minPixel = PixelDataTypeY2_0i4(0x0000);
const PixelDataTypeY2_0i4  PixelRange_Y2_0i4_i2u::maxPixel = PixelDataTypeY2_0i4(0xffff);
const I4                   PixelRange_Y2_0i4_i2u::minValue = I4(0x0000);
const I4                   PixelRange_Y2_0i4_i2u::maxValue = I4(0xffff);

const PixelDataTypeY2_0f4  PixelRange_Y2_0f4::minPixel = PixelDataTypeY2_0f4(0.0f);
const PixelDataTypeY2_0f4  PixelRange_Y2_0f4::maxPixel = PixelDataTypeY2_0f4(1.0f);
const F4                   PixelRange_Y2_0f4::minValue = F4(0.0f);
const F4                   PixelRange_Y2_0f4::maxValue = F4(1.0f);

const PixelDataTypeY2_0f8  PixelRange_Y2_0f8::minPixel = PixelDataTypeY2_0f8(0.0);
const PixelDataTypeY2_0f8  PixelRange_Y2_0f8::maxPixel = PixelDataTypeY2_0f8(1.0);
const F8                   PixelRange_Y2_0f8::minValue = F8(0.0);
const F8                   PixelRange_Y2_0f8::maxValue = F8(1.0);

}
