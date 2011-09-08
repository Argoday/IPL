
#ifndef IMAGE__BasicWx1baseAlgorithmParametersType_H
#define IMAGE__BasicWx1baseAlgorithmParametersType_H

namespace Algorithm {

class BasicWx1baseAlgorithmParametersType {
	public:

		BasicWx1baseAlgorithmParametersType(
			const long &_xOffset,
			const long &_filterWidth
		)
			:xOffset(_xOffset)
			,filterWidth(_filterWidth)
			,borderXLeft(xOffset)
			,borderXRight(filterWidth - xOffset - 1)
		{
		}

		BasicWx1baseAlgorithmParametersType(
			const BasicWx1baseAlgorithmParametersType &_other
		)
			:xOffset(_other.xOffset)
			,filterWidth(_other.filterWidth)
			,borderXLeft(_other.borderXLeft)
			,borderXRight(_other.borderXRight)
		{
		}

		const long xOffset;
		const long filterWidth;

		const long borderXLeft;
		const long borderXRight;

};

}

#endif
