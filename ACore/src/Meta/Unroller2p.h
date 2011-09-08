
#ifndef META__UNROLLER_2p_H
#define META__UNROLLER_2p_H

namespace Meta {

template <
	typename PixelType,
	typename AlgorithmType,
	typename ParameterType,
	int length
> class Unroller2p {
	private:
		enum { halfLength = length / 2 };
	public:
		__forceinline static void process(
			PixelType * &imageDataPtr,
			const PixelType * &parameterDataPtr,
			const ParameterType &parameter)
		{
			Unroller2p<PixelType,AlgorithmType,ParameterType,halfLength>::process(imageDataPtr,parameterDataPtr,parameter);
			Unroller2p<PixelType,AlgorithmType,ParameterType,halfLength>::process(imageDataPtr,parameterDataPtr,parameter);
		}
};

template <
	typename PixelType,
	typename AlgorithmType,
	typename ParameterType
> class Unroller2p<PixelType,AlgorithmType,ParameterType,1> {
	public:
		__forceinline static void process(PixelType * &imageDataPtr,const PixelType * &parameterDataPtr,const ParameterType &parameter){
			AlgorithmType::process(imageDataPtr,parameterDataPtr,parameter);
			++imageDataPtr;
			++parameterDataPtr;
		}
};

}

#endif
