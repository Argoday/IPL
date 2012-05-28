
#ifndef DATA__DataTypes_H
#define DATA__DataTypes_H

#include "ACore.h"

///////////////////////////////////////////////

typedef bool B1n;

#include <Meta/Boolean.h>
//NOTE: This is required to break an include cycle
#ifdef META__Boolean_H_END

typedef Meta::Boolean B1c; //bool

typedef B1c B1;

///////////////////////////////////////////////

typedef 		 char      I1n ; //char
typedef unsigned char      I1un;
typedef 		 short     I2n ; //short
typedef unsigned short     I2un;
typedef 		 int       I4n ; //int or long
typedef unsigned int       I4un;
typedef 		 long long I8n ; //long long
typedef unsigned long long I8un;

//TODO: Create structures for Ix types

typedef I1n  I1 ;
typedef I1un I1u;
typedef I2n  I2 ;
typedef I2un I2u;
typedef I4n  I4 ;
typedef I4un I4u;
typedef I8n  I8 ;
typedef I8un I8u;

///////////////////////////////////////////////

typedef float  F4n;
typedef double F8n; //double or long double

#include <Data/Float.h>
//NOTE: This is required to break an include cycle
#ifdef DATA__Float_H_END

//TODO: Enhance F4c and F8c to serve as default floating-point types
typedef F4n F4;
typedef F8n F8;

///////////////////////////////////////////////


#endif 

#endif 

#endif 
