
#ifndef META__Assign_H
#define META__Assign_H

#include "Remove_const.h"

namespace Meta {

template <typename Type1, typename Type2> __forceinline void assign(Type1 & value1,const Type2 & value2){
	value1=value2;
}

}

#endif
