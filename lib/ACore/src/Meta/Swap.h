
#ifndef META__Swap_H
#define META__Swap_H

#include "ACore.h"
#include "Forward.h"

namespace Meta {

//NOTE: Functional version of std::swap<> which doesn't require writing out the typename each time
template <typename Type> FINLINE void swap(Type & first,Type & second){
	Type temp(forward(first));first=forward(second);second=forward(temp);
}

}

#endif
