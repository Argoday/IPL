
#ifndef IMAGE__BaseAlgorithmWx1parametersType_H
#define IMAGE__BaseAlgorithmWx1parametersType_H

#include "AIL.h"

namespace Image {

class AIL_DLL_EXPORT BaseAlgorithmWx1parametersType {
	public:

		BaseAlgorithmWx1parametersType(
			const I4 & _xOffset,
			const I4 & _filterWidth)
			:xOffset(_xOffset)
			,filterWidth(_filterWidth)
		{
		}
		BaseAlgorithmWx1parametersType(const BaseAlgorithmWx1parametersType & _other)
			:xOffset(_other.xOffset)
			,filterWidth(_other.filterWidth)
		{
		}

		const I4 xOffset;
		const I4 filterWidth;
};

}

#endif
