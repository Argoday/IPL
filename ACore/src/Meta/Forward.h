
#ifndef META__Forward_H
#define META__Forward_H

namespace Meta {

template <typename Type> __forceinline Type &&forward(Type & value){
	return static_cast<Type&&>(value);
}

}

#endif
