
#ifndef IMAGE__BaseAlgorithmWx1parametersType_H
#define IMAGE__BaseAlgorithmWx1parametersType_H

#include "AIL.h"

namespace Image {

class BaseAlgorithmWx1parametersType{
	public:

		BaseAlgorithmWx1parametersType(
			const I4 & _borderXLeft,
			const I4 & _borderXRight)
			:borderXLeft(_borderXLeft)
			,borderXRight(_borderXRight)
		{
		}
		BaseAlgorithmWx1parametersType(const BaseAlgorithmWx1parametersType & _other)
			:borderXLeft(_other.borderXLeft)
			,borderXRight(_other.borderXRight)
		{
		}

		const I4 borderXLeft;
		const I4 borderXRight;
};

}

#endif
