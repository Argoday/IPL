
#ifndef DATA__Float_H
#define DATA__Float_H

#include "ACore.h"
#include <Data/DataTypes.h>

//TODO: Verify that these structures actually work
//TODO: Examine the x64 generated for accessing the struct components versus the function versions

class ACORE_DLL_EXPORT F16c { //TODO: Complete a quad precision floating point class
	public:
		union {
			struct {
				I8u u1;
				I8u u2;
			} u ;
			struct {
				I8u mantissa1 : 64; //112 mantissa bits
				I8u mantissa2 : 48;
				I8u exponent : 15;
				I8u sign : 1;
			} s ;
		};
		F16c(const I8u & _u1,const I8u & _u2){u.u1=_u1;u.u2=_u2;}

};

class ACORE_DLL_EXPORT F8c {
	public:
		union {
			I8u u;
			F8  f;
			struct {
				I8u mantissa : 52;
				I8u exponent : 11;
				I8u sign : 1;
			} s ;
		};
		__forceinline F8c(){}
		explicit __forceinline F8c(const I8u & _u,const bool & dummy):u(_u){}
		__forceinline F8c(const F8 & _f):f(_f){}
		__forceinline operator F8(){return f;}

	    __forceinline bool sign()     const { return (u >> 63) != 0; }
		__forceinline I8u  mantissa() const { return  u & ((1i64 << 52) - 1); } //TODO: Make this a static const? - or is this handled by the compiler
		__forceinline I8u  exponent() const { return (u >> 52) & 0x7FF; }

};

class ACORE_DLL_EXPORT F4c {
	public:
		union {
			I4u u;
			F4  f;
			struct {
				I4u mantissa : 23;
				I4u exponent : 8;
				I4u sign : 1;
			} s ;
		};
		__forceinline F4c(){}
		explicit __forceinline F4c(const I4u & _u,const bool & dummy):u(_u){}
		__forceinline F4c(const F4 & _f):f(_f){}
		__forceinline operator F4(){return f;}

	    __forceinline bool sign()     const { return (u >> 31) != 0; }
		__forceinline I4u  mantissa() const { return  u & ((1 << 23) - 1); } //TODO: Make this a static const? - or is this handled by the compiler
		__forceinline I4u  exponent() const { return (u >> 23) & 0xFF; }

};

//Half precision floating point based on https://gist.github.com/2156668 and http://fgiesen.wordpress.com/2012/03/28/half-to-float-done-quic/ by rygorous
//TODO: Use the SEE version of float_to_half_SSE2()
class ACORE_DLL_EXPORT F2c {
	public:
		union {
			I2u u;
			struct {
				I2u mantissa : 10;
				I2u exponent : 5;
				I2u sign : 1;
			} s ;
		};

		__forceinline bool sign() const { return (u >> 15) != 0; }
		__forceinline I2u mantissa() const { return u & ((1 << 10) - 1); } //TODO: Make this a static const? - or is this handled by the compiler
		__forceinline I2u exponent() const { return (u >> 10) & 0x1F; }

		F2c(const F4c & f){
			u=0;

			if (f.s.exponent == 255){ // Inf or NaN (all exponent bits set)
				s.exponent = 31;
				s.mantissa = f.s.mantissa ? 0x200 : 0; // NaN->qNaN and Inf->Inf
			}else{ // Normalized number
				// Exponent unbias the single, then bias the halfp
				int newexp = f.s.exponent - 127 + 15;
				if (newexp >= 31){ // Overflow, return signed infinity
					s.exponent = 31;
				}else if (newexp <= 0){ // Underflow
					if ((14 - newexp) <= 24){ // Mantissa might be non-zero
						I4u mant = f.s.mantissa | 0x800000; // Hidden 1 bit
						s.mantissa = mant >> (14 - newexp);
						if ((mant >> (13 - newexp)) & 1){ // Check for rounding
							u++; // Round, might overflow into exp bit, but this is OK
						}
					}
				}else{
					s.exponent = newexp;
					s.mantissa = f.s.mantissa >> 13;
					if (f.s.mantissa & 0x1000){ // Check for rounding
						u++; // Round, might overflow to inf, this is OK
					}
				}
			}

			s.sign = f.s.sign;
		}

		operator F4c(){
			F4c o;

			if (s.exponent == 0){ // Zero / Denormal
				o.u = magic.u + s.mantissa;
				o.f -= magic.f;
			}else{
				o.s.mantissa = s.mantissa << 13;
				if (s.exponent == 0x1f){ // Inf/NaN
					o.s.exponent = 255;
				}else{
					o.s.exponent = 127 - 15 + s.exponent;
				}
			}

			o.s.sign = s.sign;
			return o;
		}
	private:
		static const F4c magic;

};

#endif 
