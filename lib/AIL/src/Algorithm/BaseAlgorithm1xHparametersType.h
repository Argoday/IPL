
#ifndef IMAGE__BaseAlgorithm1xHparametersType_H
#define IMAGE__BaseAlgorithm1xHparametersType_H

#include "AIL.h"

namespace Image {

class AIL_DLL_EXPORT BaseAlgorithm1xHparametersType {
	public:

		BaseAlgorithm1xHparametersType(
			const I4 & _yOffset,
			const I4 & _filterHeight)
			:yOffset(_yOffset)
			,filterHeight(_filterHeight)
		{
		}
		BaseAlgorithm1xHparametersType(const BaseAlgorithm1xHparametersType & _other)
			:yOffset(_other.yOffset)
			,filterHeight(_other.filterHeight)
		{
		}

		const I4 yOffset;
		const I4 filterHeight;
};

}

#endif
