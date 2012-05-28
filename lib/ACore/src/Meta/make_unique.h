
#ifndef META__make_unique_H
#define META__make_unique_H

#include "ACore.h"

#include <Meta/Forward.h>

namespace Meta {

	template <
		typename Type
	> std::unique_ptr<Type> make_unique(){
		return std::unique_ptr<Type>(new Type());
	}
	template <
		typename Type,
		typename Parameter1
	> std::unique_ptr<Type> make_unique(Parameter1 && parameter1){
		return std::unique_ptr<Type>(new Type(Meta::forward(parameter1)));
	}
	template <
		typename Type,
		typename Parameter1,
		typename Parameter2
	> std::unique_ptr<Type> make_unique(Parameter1 && parameter1,Parameter1 && parameter2){
		return std::unique_ptr<Type>(new Type(Meta::forward(parameter1),Meta::forward(parameter2)));
	}
	template <
		typename Type,
		typename Parameter1,
		typename Parameter2,
		typename Parameter3,
		typename Parameter4
	> std::unique_ptr<Type> make_unique(Parameter1 && parameter1,Parameter2 && parameter2,Parameter3 && parameter3){
		return std::unique_ptr<Type>(new Type(Meta::forward(parameter1),Meta::forward(parameter2),Meta::forward(parameter3)));
	}
	template <
		typename Type,
		typename Parameter1,
		typename Parameter2,
		typename Parameter3,
		typename Parameter4
	> std::unique_ptr<Type> make_unique(Parameter1 && parameter1,Parameter2 && parameter2,Parameter3 && parameter3,Parameter4 && parameter4){
		return std::unique_ptr<Type>(new Type(Meta::forward(parameter1),Meta::forward(parameter2),Meta::forward(parameter3),Meta::forward(parameter4)));
	}
}

#endif
