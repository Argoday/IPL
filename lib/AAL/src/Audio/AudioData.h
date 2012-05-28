
#ifndef AUDIO__AudioData_H
#define AUDIO__AudioData_H

#include "AAL.h"
#include <Data/DataTypes.h>
#include <Data/DataManager.h>

namespace Audio {

class AAL_DLL_EXPORT AudioData {
	public:
		typedef AudioData ThisType;
		AudioData(Data::DataManager * const _dataManager,const I8u & _numBytes):dataManager(_dataManager),numBytes(_numBytes){
			data = reinterpret_cast<I1u*>(_dataManager->getMemoryFromPool(_numBytes));
		}
		AudioData(ThisType && other)
			:dataManager(other.dataManager)
		{
			data = other.data;
			numBytes = other.numBytes;
			other.data = nullptr;
			other.numBytes = 0;
		}
		~AudioData(){
			dataManager->releaseFromPool(data,numBytes);
		}

		const I1u * getData() const {return data;}
		      I1u * getData()       {return data;}
		
		const I8u & getNumBytes() const {return numBytes;}
	private:
		Data::DataManager * const dataManager;
		I1u * data;
		I8u numBytes;
};

}

#endif 
