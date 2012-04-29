
#ifndef IMAGE__Basic1xHbaseAlgorithmParametersType_H
#define IMAGE__Basic1xHbaseAlgorithmParametersType_H

namespace Algorithm {

class AIL_DLL_EXPORT Basic1xHbaseAlgorithmParametersType {
	public:

		Basic1xHbaseAlgorithmParametersType(
			const I4 & _yOffset,
			const I4 & _filterHeight,
			const I4 & _srcImageWidth
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
			const Basic1xHbaseAlgorithmParametersType & _other
		)
			:yOffset(_other.yOffset)
			,filterHeight(_other.filterHeight)
			,borderYBottom(_other.borderYBottom)
			,borderYTop(_other.borderYTop)
			,srcImageWidth(_other.srcImageWidth)
			,srcImageWidth_x_filterHeight(_other.srcImageWidth_x_filterHeight)
		{
		}

		const I4 yOffset;
		const I4 filterHeight;

		const I4 borderYBottom;
		const I4 borderYTop;

		const I4 srcImageWidth;
		const I4 srcImageWidth_x_filterHeight;

};

}

#endif
