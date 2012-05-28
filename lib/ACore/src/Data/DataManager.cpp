
#include "DataManager.h"
#include "DataChunk.h"

#include <vector>
#include <map>

#include <stdlib.h> //For: _aligned_malloc() , _aligned_free()
#include <mutex> //For: std::mutex , std::lock_guard<std::mutex>

namespace Data {

class DataManagerHelper;

class DataManager::DataManager_d {
	public:
		std::map<I8u,DataManagerHelper> dataMap;
		std::mutex criticalSection;
};

void * const DataManager::getMemory(const I4  & numBytes){
	return _aligned_malloc(numBytes,4096); //TODO: Allow for different alignments for smaller allocations
}
void * const DataManager::getMemory(const I4u & numBytes){
	return _aligned_malloc(numBytes,4096); //TODO: Allow for different alignments for smaller allocations
}
void * const DataManager::getMemory(const I8u & numBytes){
	return _aligned_malloc(numBytes,4096); //TODO: Allow for different alignments for smaller allocations
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
		~DataManagerHelper(){
			auto dataListIter = dataList.begin();
			for(;dataListIter!=dataList.end();++dataListIter){
				dataListIter->release();
			}
		}
	private:
		DataManagerHelper(const I8u &_numBytes)
			:head(nullptr)
			,numBytes(_numBytes)
		{
		}

		I8u numBytes;
		DataChunk * head;
		std::vector<DataChunk> dataList;

		I8u cleanupFree(){
			I8u amountFreed=0;
			std::vector<DataChunk> newDataList;
			auto dataListIter = dataList.begin();
			for(;dataListIter!=dataList.end();++dataListIter){
				if(dataListIter->isLocked()==true){
					newDataList.push_back(*dataListIter);
				}else{
					dataListIter->release();
					amountFreed+=numBytes;
				}
			}
			head=nullptr;
			dataList = newDataList;
			return amountFreed;
		}

		void * const getMemory(){
			if(head!=nullptr){
				void * const headDataPtr = head->getDataPtr();
				head->Lock();
				head = head->getNextPtr();
				return headDataPtr;
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

		B1 release(const void * const dataPtr){
			auto dataListIter = dataList.begin();
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

DataManager::DataManager(){
	_this = new DataManager_d();
}
DataManager::~DataManager(){
	delete _this;
}

void * const DataManager::getMemoryFromPool(const I4  &_numBytes){
	return getMemoryFromPool(static_cast<I8u>(_numBytes));
}
void * const DataManager::getMemoryFromPool(const I4u &_numBytes){
	return getMemoryFromPool(static_cast<I8u>(_numBytes));
}
void * const DataManager::getMemoryFromPool(const I8u &_numBytes){
	std::lock_guard<std::mutex> lock(_this->criticalSection);
	auto dataMapIter = _this->dataMap.find(_numBytes);
	if(dataMapIter!=_this->dataMap.end()){
		return dataMapIter->second.getMemory();
	}
	_this->dataMap.insert(std::pair<size_t,DataManagerHelper>(_numBytes,DataManagerHelper(_numBytes)));
	return _this->dataMap[_numBytes].getMemory();
}

B1 DataManager::releaseFromPool(const void * const dataPtr){
	if(dataPtr==nullptr){return false;}
	std::lock_guard<std::mutex> lock(_this->criticalSection);
	auto dataMapIter = _this->dataMap.begin();
	for(;dataMapIter!=_this->dataMap.end();++dataMapIter){
		if(dataMapIter->second.release(dataPtr)==true){
			return true;
		}
	}
	// TODO: Error!
	return false;
}
B1 DataManager::releaseFromPool(const void * const dataPtr,const I4  & numBytes){
	if(dataPtr==nullptr){return false;}
	std::lock_guard<std::mutex> lock(_this->criticalSection);
	return _this->dataMap[numBytes].release(dataPtr);
}
B1 DataManager::releaseFromPool(const void * const dataPtr,const I4u & numBytes){
	if(dataPtr==nullptr){return false;}
	std::lock_guard<std::mutex> lock(_this->criticalSection);
	return _this->dataMap[numBytes].release(dataPtr);
}
B1 DataManager::releaseFromPool(const void * const dataPtr,const I8u & numBytes){
	if(dataPtr==nullptr){return false;}
	std::lock_guard<std::mutex> lock(_this->criticalSection);
	return _this->dataMap[numBytes].release(dataPtr);
}

I8u DataManager::releaseFreeFromPool(){
	std::lock_guard<std::mutex> lock(_this->criticalSection);
	I8u amountFreed = 0;
	auto dataMapIter = _this->dataMap.begin();
	for(;dataMapIter!=_this->dataMap.end();++dataMapIter){
		amountFreed+=dataMapIter->second.cleanupFree();
	}
	return amountFreed;
}

}
