
#ifndef IMAGE__BASE_ALGORITHM_1xH_PARAMETERS_TYPE_H
#define IMAGE__BASE_ALGORITHM_1xH_PARAMETERS_TYPE_H

namespace Image {

class BaseAlgorithm1xHparametersType{
	public:

		BaseAlgorithm1xHparametersType(
			const long &_borderYBottom,
			const long &_borderYTop)
			:borderYBottom(_borderYBottom)
			,borderYTop(_borderYTop)
		{
		}
		BaseAlgorithm1xHparametersType(const BaseAlgorithm1xHparametersType &_other)
			:borderYBottom(_other.borderYBottom)
			,borderYTop(_other.borderYTop)
		{
		}

		const long borderYBottom;
		const long borderYTop;
};

}

#endif
