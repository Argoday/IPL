
#ifndef IMAGE__Basic1xHbaseAlgorithmParametersType_H
#define IMAGE__Basic1xHbaseAlgorithmParametersType_H

namespace Algorithm {

class Basic1xHbaseAlgorithmParametersType {
	public:

		Basic1xHbaseAlgorithmParametersType(
			const long &_yOffset,
			const long &_filterHeight,
			const long &_srcImageWidth
		)
			:yOffset(_yOffset)
			,filterHeight(_filterHeight)
			,borderYBottom(_yOffset)
			,borderYTop(_filterHeight - _yOffset - 1)
			,srcImageWidth(_srcImageWidth)
			,srcImageWidth_x_filterHeight(_srcImageWidth*_filterHeight)
		{
		}

		Basic1xHbaseAlgorithmParametersType(
			const Basic1xHbaseAlgorithmParametersType &_other
		)
			:yOffset(_other.yOffset)
			,filterHeight(_other.filterHeight)
			,borderYBottom(_other.borderYBottom)
			,borderYTop(_other.borderYTop)
			,srcImageWidth(_other.srcImageWidth)
			,srcImageWidth_x_filterHeight(_other.srcImageWidth_x_filterHeight)
		{
		}

		const long yOffset;
		const long filterHeight;

		const long borderYBottom;
		const long borderYTop;

		const long srcImageWidth;
		const long srcImageWidth_x_filterHeight;

};

}

#endif
