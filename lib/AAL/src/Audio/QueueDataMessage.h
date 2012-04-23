
#ifndef AUDIO__QUEUE_Message_H
#define AUDIO__QUEUE_Message_H

#include "AAL.h"
#include <Data/DataTypes.h>

namespace Audio {

namespace Queue {

enum class AAL_DLL_EXPORT DataMessageType {
	none,
	sound, // ??? , I8u timeStamp
	flush, // I8u flushID
	quit
};

class AAL_DLL_EXPORT DataMessageParameter {
	public:
		typedef DataMessageParameter ThisType;
		virtual void releaseParameter() = 0 ;
};

class AAL_DLL_EXPORT MessageDefaultParameter : public DataMessageParameter {
	public:
		typedef MessageDefaultParameter ThisType;
		ThisType(const ThisType & other){}
		ThisType(ThisType && other){}
		ThisType(){}
		void releaseParameter() {}
};
class AAL_DLL_EXPORT DataMessageFlushParameter : public DataMessageParameter {
	public:
		typedef DataMessageFlushParameter ThisType;
		ThisType(const ThisType & other):flushID(other.flushID){}
		ThisType(ThisType && other){
			flushID=other.flushID;
		}
		ThisType(const I8u & _flushID):flushID(_flushID){}

		const I8u & getFlushID() const {return flushID;}

		void releaseParameter() {}
	private:
		I8u flushID;
};
class AAL_DLL_EXPORT DataMessageSoundParameter : public DataMessageParameter {
	public:
		typedef DataMessageSoundParameter ThisType;
		ThisType(const ThisType & other):timeStamp(other.timeStamp){}
		ThisType(ThisType && other){
			timeStamp=other.timeStamp;
		}
		ThisType(const I8u & _timeStamp):timeStamp(_timeStamp){}

		const I8u & getTimeStamp() const {return timeStamp;}

		void releaseParameter() {}
	private:
		I8u timeStamp;
};

}

}

#endif 
