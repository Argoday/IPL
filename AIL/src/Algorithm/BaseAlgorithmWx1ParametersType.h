
#ifndef IMAGE__BASE_ALGORITHM_Wx1_PARAMETERS_TYPE_H
#define IMAGE__BASE_ALGORITHM_Wx1_PARAMETERS_TYPE_H

namespace Image {

class BaseAlgorithmWx1parametersType{
	public:

		BaseAlgorithmWx1parametersType(
			const long &_borderXLeft,
			const long &_borderXRight)
			:borderXLeft(_borderXLeft)
			,borderXRight(_borderXRight)
		{
		}
		BaseAlgorithmWx1parametersType(const BaseAlgorithmWx1parametersType &_other)
			:borderXLeft(_other.borderXLeft)
			,borderXRight(_other.borderXRight)
		{
		}

		const long borderXLeft;
		const long borderXRight;
};

}

#endif
