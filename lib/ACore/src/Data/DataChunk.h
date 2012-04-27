
#ifndef DATA__DataChunk_H
#define DATA__DataChunk_H

#include "ACore.h"
#include <Data/DataTypes.h>

namespace Data {

class DataManagerHelper;

class DataChunk {

	public:

		DataChunk(const DataChunk & _dataChunk);
		DataChunk(DataChunk && _dataChunk);

		~DataChunk();

	private:
		friend class DataManagerHelper; //TODO: Check if this can be removed

		DataChunk(const I8u & _numBytes, DataChunk * const & _nextPtr);

		FINLINE const I8u & getNumBytes() const {return numBytes;}
		FINLINE void * const & getDataPtr(){return dataPtr;}
		FINLINE const B1 & isLocked() const {return locked;}
		FINLINE DataChunk * const & getNextPtr() const {return nextPtr;}

		void Lock  (){locked=true ;}
		void Unlock(){locked=false;}

		void release();

		FINLINE void setNextPtr(DataChunk *_nextPtr){nextPtr=_nextPtr;}

		void * dataPtr;
		I8u numBytes;

		DataChunk * nextPtr;
		B1 locked;
};

}

#endif
