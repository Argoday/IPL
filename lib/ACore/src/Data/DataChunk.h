
#ifndef DATA__DataChunk_H
#define DATA__DataChunk_H

namespace Data {

class DataManagerHelper;

class DataChunk {

	public:

	//Contructors
		DataChunk(const DataChunk &_dataChunk);
		DataChunk(DataChunk &&_dataChunk);
	//Destructor
		~DataChunk();

	private:
		friend class DataManagerHelper; //TODO: Check if this can be removed

	//Contructors
		DataChunk(const size_t &_numBytes, DataChunk * const &_nextPtr);

	//Accessors
		__forceinline const size_t &getNumBytes() const {return numBytes;}
		__forceinline void * const &getDataPtr(){return dataPtr;}
		__forceinline const bool &isLocked() const {return locked;}
		__forceinline DataChunk * const &getNextPtr() const {return nextPtr;}

	//Mutators
		void Lock  (){locked=true ;} //TODO: make this an Atomic function call
		void Unlock(){locked=false;} //TODO: make this an Atomic function call

		__forceinline void setNextPtr(DataChunk *_nextPtr){nextPtr=_nextPtr;}

	//Member Variables
		void *dataPtr;
		size_t numBytes;

		DataChunk *nextPtr;
		bool locked;
};

}

#endif
