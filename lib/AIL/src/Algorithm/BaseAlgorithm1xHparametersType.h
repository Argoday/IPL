
#ifndef IMAGE__BaseAlgorithm1xHparametersType_H
#define IMAGE__BaseAlgorithm1xHparametersType_H

#include "AIL.h"

namespace Image {

class AIL_DLL_EXPORT BaseAlgorithm1xHparametersType {
	public:

		BaseAlgorithm1xHparametersType(
			const I4 & _borderYBottom,
			const I4 & _borderYTop)
			:borderYBottom(_borderYBottom)
			,borderYTop(_borderYTop)
		{
		}
		BaseAlgorithm1xHparametersType(const BaseAlgorithm1xHparametersType & _other)
			:borderYBottom(_other.borderYBottom)
			,borderYTop(_other.borderYTop)
		{
		}

		const I4 borderYBottom;
		const I4 borderYTop;
};

}

#endif
