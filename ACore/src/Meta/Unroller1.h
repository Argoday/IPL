
#ifndef META__UNROLLER_1_H
#define META__UNROLLER_1_H

namespace Meta {

template <
	typename PixelType,
	typename AlgorithmType,
	int length
> class Unroller1 {
	private:
		enum { halfLength = length / 2 };
	public:
		__forceinline static void process(PixelType * &imageDataPtr){
			Unroller1<PixelType,AlgorithmType,halfLength>::process(imageDataPtr);
			Unroller1<PixelType,AlgorithmType,halfLength>::process(imageDataPtr);
		}
};

template <
	typename PixelType,
	typename AlgorithmType
> class Unroller1<PixelType,AlgorithmType,1> {
	public:
		__forceinline static void process(PixelType * &imageDataPtr){
			AlgorithmType::process(imageDataPtr);
			++imageDataPtr;
		}
};

}

#endif
