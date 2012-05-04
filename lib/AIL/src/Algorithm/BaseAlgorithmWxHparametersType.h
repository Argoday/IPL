
#ifndef IMAGE__BaseAlgorithmWxHparametersType_H
#define IMAGE__BaseAlgorithmWxHparametersType_H

#include "AIL.h"

namespace Image {

class AIL_DLL_EXPORT BaseAlgorithmWxHparametersType {
	public:

		BaseAlgorithmWxHparametersType(
			const I4 & _xOffset,
			const I4 & _yOffset,
			const I4 & _filterWidth,
			const I4 & _filterHeight)
			:xOffset(_xOffset)
			,yOffset(_yOffset)
			,filterWidth(_filterWidth)
			,filterHeight(_filterHeight)
		{
		}
		BaseAlgorithmWxHparametersType(const BaseAlgorithmWxHparametersType & _other)
			:xOffset(_other.xOffset)
			,yOffset(_other.yOffset)
			,filterWidth(_other.filterWidth)
			,filterHeight(_other.filterHeight)
		{
		}

		const I4 xOffset;
		const I4 yOffset;

		const I4 filterWidth;
		const I4 filterHeight;

};

}

#endif
