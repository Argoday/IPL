
#ifndef ALGORITHM__BaseOperationTempType_H
#define ALGORITHM__BaseOperationTempType_H

namespace Algorithm {

template <
	typename PixelDataType,
	typename PixelComputationType
> class BaseOperationTempType {
	public:
		PixelDataType        resultPixel;
		PixelComputationType tempPixel;
};

}

#endif
