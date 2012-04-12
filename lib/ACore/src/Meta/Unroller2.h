
#ifndef META__UNROLLER_2_H
#define META__UNROLLER_2_H

namespace Meta {
	
template <
	typename DataType,
	typename ParameterDataType,
	typename AlgorithmType,
	int length
> class Unroller2 {
	private:
		enum { halfLength = length / 2 };
	public:
		__forceinline static void process(DataType * & dataPtr,const ParameterDataType * & parameterDataPtr){
			Unroller2<DataType,ParameterDataType,AlgorithmType,halfLength>::process(dataPtr,parameterDataPtr);
			Unroller2<DataType,ParameterDataType,AlgorithmType,halfLength>::process(dataPtr,parameterDataPtr);
		}
};

template <
	typename DataType,
	typename ParameterDataType,
	typename AlgorithmType
> class Unroller2<DataType,ParameterDataType,AlgorithmType,1> {
	public:
		__forceinline static void process(DataType * & dataPtr,const ParameterDataType * & parameterDataPtr){
			AlgorithmType::process(dataPtr,parameterDataPtr);
			++dataPtr;
			++parameterDataPtr;
		}
};

}

#endif
