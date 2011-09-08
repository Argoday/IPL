
#ifndef META__UNROLLER_2_H
#define META__UNROLLER_2_H

namespace Meta {
	
template <
	typename PixelType,
	typename AlgorithmType,
	int length
> class Unroller2 {
	private:
		enum { halfLength = length / 2 };
	public:
		__forceinline static void process(PixelType * &imageDataPtr,const PixelType * &parameterDataPtr){
			Unroller2<PixelType,AlgorithmType,halfLength>::process(imageDataPtr,parameterDataPtr);
			Unroller2<PixelType,AlgorithmType,halfLength>::process(imageDataPtr,parameterDataPtr);
		}
};

template <
	typename PixelType,
	typename AlgorithmType
> class Unroller2<PixelType,AlgorithmType,1> {
	public:
		__forceinline static void process(PixelType * &imageDataPtr,const PixelType * &parameterDataPtr){
			AlgorithmType::process(imageDataPtr,parameterDataPtr);
			++imageDataPtr;
			++parameterDataPtr;
		}
};

}

#endif
