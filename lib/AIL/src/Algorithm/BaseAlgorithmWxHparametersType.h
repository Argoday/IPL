
#ifndef IMAGE__BaseAlgorithmWxHparametersType_H
#define IMAGE__BaseAlgorithmWxHparametersType_H

#include "AIL.h"

namespace Image {

class AIL_DLL_EXPORT BaseAlgorithmWxHparametersType {
	public:

		BaseAlgorithmWxHparametersType(
			const I4 & _borderXLeft,
			const I4 & _borderXRight,
			const I4 & _borderYBottom,
			const I4 & _borderYTop)
			:borderXLeft(_borderXLeft)
			,borderXRight(_borderXRight)
			,borderYBottom(_borderYBottom)
			,borderYTop(_borderYTop)
		{
		}
		BaseAlgorithmWxHparametersType(const BaseAlgorithmWxHparametersType & _other)
			:borderXLeft(_other.borderXLeft)
			,borderXRight(_other.borderXRight)
			,borderYBottom(_other.borderYBottom)
			,borderYTop(_other.borderYTop)
		{
		}

		const I4 borderXLeft;
		const I4 borderXRight;
		const I4 borderYBottom;
		const I4 borderYTop;

};

}

#endif
