
#ifndef IMAGE__BasicWx1baseAlgorithmParametersType_H
#define IMAGE__BasicWx1baseAlgorithmParametersType_H

#include "AIL.h"

namespace Algorithm {

class AIL_DLL_EXPORT BasicWx1baseAlgorithmParametersType {
	public:

		BasicWx1baseAlgorithmParametersType(
			const I4 & _xOffset,
			const I4 & _filterWidth
		)
			:xOffset(_xOffset)
			,filterWidth(_filterWidth)
			,borderXLeft(xOffset)
			,borderXRight(filterWidth - xOffset - 1)
		{
		}

		BasicWx1baseAlgorithmParametersType(
			const BasicWx1baseAlgorithmParametersType & _other
		)
			:xOffset(_other.xOffset)
			,filterWidth(_other.filterWidth)
			,borderXLeft(_other.borderXLeft)
			,borderXRight(_other.borderXRight)
		{
		}

		const I4 xOffset;
		const I4 filterWidth;

		const I4 borderXLeft;
		const I4 borderXRight;

};

}

#endif
