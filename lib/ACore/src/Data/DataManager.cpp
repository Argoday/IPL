
#include "DataManager.h"
#include "DataChunk.h"
#include <vector> //TODO: Remove usage of std::vector , it adds too much to the binary for what it is worth
#include <map> //TODO: Remove usage of std::map , it adds too much to the binary for what it is worth
#include <stdlib.h> //For: _aligned_malloc() , _aligned_free()

#pragma warning( disable : 4267 ) //Note: Disable warning for possible conversion loss from size_t to long

namespace Data {

class DataManagerHelper;

class DataManager::DataManager_d {
	public:
		std::map<size_t,DataManagerHelper> dataMap;
};

void * const DataManager::getMemory(const size_t & numBytes){
	return _aligned_malloc(numBytes,4096);
}
void * const DataManager::getMemory(const long & numBytes){
	return _aligned_malloc(numBytes,4096);
}
void * const DataManager::getMemory(const unsigned long & numBytes){
	return _aligned_malloc(numBytes,4096);
}
void DataManager::release(const void * const dataPtr){
	_aligned_free(const_cast<void * const>(dataPtr));
}

class DataManagerHelper {
		friend DataManager;
	public:
		DataManagerHelper()
			:head(nullptr)
			,numBytes(0)
		{
		}
	private:
		DataManagerHelper(const size_t &_numBytes)
			:head(nullptr)
			,numBytes(_numBytes)
		{
		}

		size_t numBytes;
		DataChunk *head;
		std::vector<DataChunk> dataList;

		void * const getMemory(){
			if(head!=nullptr){
				void * const headDataPtr = head->getDataPtr();
				head->Lock();
				head = head->getNextPtr();
				return headDataPtr;
			}

			// TODO: Remove this redundant check
			std::vector<DataChunk>::iterator dataListIter = dataList.begin();
			for(;dataListIter!=dataList.end();++dataListIter){
				if(dataListIter->isLocked()==false){
					// TODO: Report an Error !
					dataListIter->Lock();
					return (*dataListIter).getDataPtr();
				}
			}

			if(numBytes==0){ // TODO: Check to see if this check can be removed
				// TODO: Report an error!
				return nullptr;
			}

			//Add one more DataChunk because all of them are locked at the moment
			dataList.push_back(DataChunk(numBytes,nullptr));

			dataList.back().Lock();
			return dataList.back().getDataPtr();
		}

		bool release(const void * const dataPtr){
			std::vector<DataChunk>::iterator dataListIter = dataList.begin();
			for(;dataListIter!=dataList.end();++dataListIter){
				if(dataListIter->getDataPtr()==dataPtr){
					dataListIter->Unlock();
					DataChunk * oldHead = head;
					head = &(*dataListIter);
					head->setNextPtr(oldHead);
					return true;
				}
			}
			return false;
		}
};


DataManager::DataManager(){
	_this = new DataManager_d();
}

DataManager::~DataManager(){
	delete _this;
}

void * const DataManager::getMemoryFromPool(const size_t &_numBytes){
	std::map<size_t,DataManagerHelper>::iterator dataMapIter = _this->dataMap.find(_numBytes);
	if(dataMapIter!=_this->dataMap.end()){
		return dataMapIter->second.getMemory();
	}
	_this->dataMap.insert(std::pair<size_t,DataManagerHelper>(_numBytes,DataManagerHelper(_numBytes)));
	return _this->dataMap[_numBytes].getMemory();
}
void * const DataManager::getMemoryFromPool(const long &_numBytes){
	return getMemoryFromPool(static_cast<size_t>(_numBytes));
}
void * const DataManager::getMemoryFromPool(const unsigned long &_numBytes){
	return getMemoryFromPool(static_cast<size_t>(_numBytes));
}

bool DataManager::releaseFromPool(const void * const dataPtr){
	std::map<size_t,DataManagerHelper>::iterator dataMapIter = _this->dataMap.begin();
	for(;dataMapIter!=_this->dataMap.end();++dataMapIter){
		if(dataMapIter->second.release(dataPtr)==true){
			return true;
		}
	}
	// TODO: Error!
	return false;
}
bool DataManager::releaseFromPool(const void * const dataPtr,const long &numBytes){
	return _this->dataMap[numBytes].release(dataPtr);
}

}
