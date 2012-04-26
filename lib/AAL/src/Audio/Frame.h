
#ifndef AUDIO__Frame_H
#define AUDIO__Frame_H

#include "AAL.h"
#include "AudioData.h"
#include <Data/DataTypes.h>

namespace Audio {

class AAL_DLL_EXPORT Frame {
	public:
		typedef Frame ThisType;
		ThisType(const ThisType & other):data(other.data),timeStamp(other.timeStamp),frameIndex(other.frameIndex){}
		ThisType(ThisType && other){
			data=other.data;
			timeStamp=other.timeStamp;
			frameIndex=other.frameIndex;
			other.data=nullptr;
			other.timeStamp=0;
			other.frameIndex=0;
		}
		ThisType(AudioData * const & _data,const I8u & _timeStamp,const I8u & _frameIndex):data(_data),timeStamp(_timeStamp),frameIndex(_frameIndex){}

		AudioData * takeData() {
			auto tempData = data;
			data = nullptr;
			return tempData;
		}

		const AudioData * const & getData() const {return data;}
		const I8u & getTimeStamp()  const {return timeStamp ;}
		const I8u & getFrameIndex() const {return frameIndex;}

		void release(){if(data!=nullptr){delete data;data=nullptr;}}
	private:
		AudioData * data;
		I8u timeStamp;
		I8u frameIndex;
};

}

#endif 
