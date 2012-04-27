
#ifndef META__Forward_H
#define META__Forward_H

#include "ACore.h"

namespace Meta {

//NOTE: Functional version of std::forward<> which doesn't require writing out the typename each time
template <typename Type> FINLINE Type && forward(Type & value){
	return static_cast<Type&&>(value);
}

}

#endif
