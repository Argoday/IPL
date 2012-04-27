
#ifndef META__UNROLLER_1p_H
#define META__UNROLLER_1p_H

namespace Meta {

template <
	typename DataType,
	typename AlgorithmType,
	typename ParameterType,
	int length
> class Unroller1p {
	private:
		enum { halfLength = length / 2 };
	public:
		FINLINE static void process(DataType * & dataPtr,const ParameterType &parameter){
			Unroller1p<DataType,AlgorithmType,ParameterType,halfLength>::process(dataPtr,parameter);
			Unroller1p<DataType,AlgorithmType,ParameterType,halfLength>::process(dataPtr,parameter);
		}
};

template <
	typename DataType,
	typename AlgorithmType,
	typename ParameterType
> class Unroller1p<DataType,AlgorithmType,ParameterType,1> {
	public:
		FINLINE static void process(DataType * & dataPtr,const ParameterType &parameter){
			AlgorithmType::process(dataPtr,parameter);
			++dataPtr;
		}
};

}

#endif
