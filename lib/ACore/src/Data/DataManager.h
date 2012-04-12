
#ifndef DATA__DataManager_H
#define DATA__DataManager_H

#include "ACore.h"

namespace Data {

class DataManager_d;

class ACORE_DLL_EXPORT DataManager {

	public:

		DataManager();
		~DataManager();

	//Direct Memory Access
		static void * const getMemory(const size_t &numBytes);
		static void * const getMemory(const long &numBytes);
		static void * const getMemory(const unsigned long &numBytes);
		static void release(const void * const dataPtr);

	//Memory Pool
		void * const getMemoryFromPool(const size_t &numBytes);
		void * const getMemoryFromPool(const long &numBytes);
		void * const getMemoryFromPool(const unsigned long &numBytes);
		bool releaseFromPool(const void * const dataPtr);
		bool releaseFromPool(const void * const dataPtr,const long &numBytes);
		
		// TODO: Add a method to reduce Pool size

	private:

		DataManager_d * _this;

};

}

#endif
