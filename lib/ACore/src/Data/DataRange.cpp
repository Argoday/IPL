
#include "DataRange.h"

namespace Data {

const B1  DataRange_B1::min = false;
const B1  DataRange_B1::max =  true;

const I1  DataRange_I1::min = -128;
const I1  DataRange_I1::max =  127i8;

const I1u DataRange_I1u::min = 0x00ui8;
const I1u DataRange_I1u::max = 0xFFui8;

const I2  DataRange_I2::min = -32768;
const I2  DataRange_I2::max =  32767i16;

const I2u DataRange_I2u::min = 0x0000ui16;
const I2u DataRange_I2u::max = 0xFFFFui16;

const I4  DataRange_I4::min = -2147483648i32;
const I4  DataRange_I4::max =  2147483647i32;

const I4u DataRange_I4u::min = 0x00000000ui32;
const I4u DataRange_I4u::max = 0xFFFFFFFFui32;

const I2  DataRange_I2_I1u::min = 0x00ui16;
const I2  DataRange_I2_I1u::max = 0xFFui16;

const I2  DataRange_I2_I1::min = -128i16;
const I2  DataRange_I2_I1::max =  127i16;

const I2u DataRange_I2u_I1u::min = 0x00ui16;
const I2u DataRange_I2u_I1u::max = 0xFFui16;

const I4  DataRange_I4_I1::min = -128i32;
const I4  DataRange_I4_I1::max =  127i32;

const I4  DataRange_I4_I1u::min = 0x00i32;
const I4  DataRange_I4_I1u::max = 0xFFi32;

const I4u DataRange_I4u_I1u::min = 0x00ui32;
const I4u DataRange_I4u_I1u::max = 0xFFui32;

const I4  DataRange_I4_I2u::min = 0x0000i32;
const I4  DataRange_I4_I2u::max = 0xFFFFi32;

const I4  DataRange_I4_I2::min = -32768;
const I4  DataRange_I4_I2::max =  32767i16;

const I4u DataRange_I4u_I2u::min = 0x0000ui32;
const I4u DataRange_I4u_I2u::max = 0xFFFFui32;

const F4  DataRange_F4_1::min = 0.0f;
const F4  DataRange_F4_1::max = 1.0f;

const F8  DataRange_F8_1::min = 0.0;
const F8  DataRange_F8_1::max = 1.0;

}
