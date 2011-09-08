
#ifndef META__Swap_H
#define META__Swap_H

#include "Forward.h"

namespace Meta {

template <typename Type> __forceinline void swap(Type & first,Type & second){
	Type temp(forward(first));first=forward(second);second=forward(temp);
}

}

#endif
