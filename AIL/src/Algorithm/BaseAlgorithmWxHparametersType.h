
#ifndef IMAGE__BASE_ALGORITHM_WxH_PARAMETERS_TYPE_H
#define IMAGE__BASE_ALGORITHM_WxH_PARAMETERS_TYPE_H

namespace Image {

class BaseAlgorithmWxHparametersType{
	public:

		BaseAlgorithmWxHparametersType(
			const long &_borderXLeft,
			const long &_borderXRight,
			const long &_borderYBottom,
			const long &_borderYTop)
			:borderXLeft(_borderXLeft)
			,borderXRight(_borderXRight)
			,borderYBottom(_borderYBottom)
			,borderYTop(_borderYTop)
		{
		}
		BaseAlgorithmWxHparametersType(const BaseAlgorithmWxHparametersType &_other)
			:borderXLeft(_other.borderXLeft)
			,borderXRight(_other.borderXRight)
			,borderYBottom(_other.borderYBottom)
			,borderYTop(_other.borderYTop)
		{
		}

		const long borderXLeft;
		const long borderXRight;
		const long borderYBottom;
		const long borderYTop;

};

}

#endif
