
#ifndef META__UNROLLER_1p_H
#define META__UNROLLER_1p_H

namespace Meta {

template <
	typename PixelType,
	typename AlgorithmType,
	typename ParameterType,
	int length
> class Unroller1p {
	private:
		enum { halfLength = length / 2 };
	public:
		__forceinline static void process(PixelType * &imageDataPtr,const ParameterType &parameter){
			Unroller1p<PixelType,AlgorithmType,ParameterType,halfLength>::process(imageDataPtr,parameter);
			Unroller1p<PixelType,AlgorithmType,ParameterType,halfLength>::process(imageDataPtr,parameter);
		}
};

template <
	typename PixelType,
	typename AlgorithmType,
	typename ParameterType
> class Unroller1p<PixelType,AlgorithmType,ParameterType,1> {
	public:
		__forceinline static void process(PixelType * &imageDataPtr,const ParameterType &parameter){
			AlgorithmType::process(imageDataPtr,parameter);
			++imageDataPtr;
		}
};

}

#endif
