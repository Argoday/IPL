
#ifndef META__UNROLLER_2p_H
#define META__UNROLLER_2p_H

namespace Meta {

template <
	typename DataType,
	typename ParameterDataType,
	typename AlgorithmType,
	typename ParameterType,
	int length
> class Unroller2p {
	private:
		enum { halfLength = length / 2 };
	public:
		__forceinline static void process(
			DataType * &dataPtr,
			const ParameterDataType * &parameterDataPtr,
			const ParameterType &parameter)
		{
			Unroller2p<PixelType,AlgorithmType,ParameterType,halfLength>::process(dataPtr,parameterDataPtr,parameter);
			Unroller2p<PixelType,AlgorithmType,ParameterType,halfLength>::process(dataPtr,parameterDataPtr,parameter);
		}
};

template <
	typename DataType,
	typename ParameterDataType,
	typename AlgorithmType,
	typename ParameterType
> class Unroller2p<PixelType,AlgorithmType,ParameterType,1> {
	public:
		__forceinline static void process(
			DataType * & dataPtr,
			const ParameterDataType * & parameterDataPtr,
			const ParameterType &parameter)
		{
			AlgorithmType::process(dataPtr,parameterDataPtr,parameter);
			++dataPtr;
			++parameterDataPtr;
		}
};

}

#endif
