
#ifndef FILTER__MorphKernelType_H
#define FILTER__MorphKernelType_H

#include "AIL.h"

namespace Filter {

// Emulate a strong enum
class AIL_DLL_EXPORT MorphKernelType {
	public:
		MorphKernelType(const MorphKernelType &other){type=other.type;}

		bool operator ==(const MorphKernelType &other) const {return type==other.type;}

		static const MorphKernelType getNone   (){return MorphKernelType(0);}

		static const MorphKernelType getCross  (){return MorphKernelType(1);}
		static const MorphKernelType getSquare (){return MorphKernelType(2);}
		static const MorphKernelType getCircle (){return MorphKernelType(3);}
		static const MorphKernelType getDiamond(){return MorphKernelType(4);}

	private:

		MorphKernelType(const I4 & _type){type=_type;}

		I4 type;
};

};

#endif
