
#ifndef META__Assign_H
#define META__Assign_H

#include "ACore.h"

namespace Meta {

//NOTE: This wacky construct lets you override const and assign to a const member variable of a class outside of it's constructor (see Image::Image::dataNumBytes for usage)
template <typename Type1, typename Type2> FINLINE void assign(Type1 & value1,const Type2 & value2){
	value1=value2;
}

}

#endif
