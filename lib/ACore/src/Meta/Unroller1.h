
#ifndef META__UNROLLER_1_H
#define META__UNROLLER_1_H

namespace Meta {

template <
	typename DataType,
	typename AlgorithmType,
	int length
> class Unroller1 {
	private:
		enum { halfLength = length / 2 };
	public:
		__forceinline static void process(DataType * & dataPtr){
			Unroller1<DataType,AlgorithmType,halfLength>::process(dataPtr);
			Unroller1<DataType,AlgorithmType,halfLength>::process(dataPtr);
		}
};

template <
	typename DataType,
	typename AlgorithmType
> class Unroller1<DataType,AlgorithmType,1> {
	public:
		__forceinline static void process(DataType * & dataPtr){
			AlgorithmType::process(dataPtr);
			++dataPtr;
		}
};

}

#endif
