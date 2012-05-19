
#ifndef THREAD__QUEUE_DataPacket_H
#define THREAD__QUEUE_DataPacket_H

#include "ACore.h"
#include <Data/DataTypes.h>

namespace Thread {

namespace Queue {

class ACORE_DLL_EXPORT DataPacket {
	public:
		enum class MessageType {
			none,
			data,   // void * data
			config, // void * data
			flush,  // I8u flushID
			quit
		};
		typedef DataPacket ThisType;

		DataPacket():messageType(MessageType::none),flushID(0),data(nullptr),timeStamp(0.0){}

		DataPacket(const MessageType & _messageType):messageType(_messageType),flushID(0),data(nullptr),timeStamp(0.0){}
		DataPacket(const MessageType & _messageType, const I8u & _flushID):messageType(_messageType),flushID(_flushID),data(nullptr),timeStamp(0.0){}
		DataPacket(const MessageType & _messageType, void * _data):messageType(_messageType),data(_data),timeStamp(0.0){}
		DataPacket(const MessageType & _messageType, void * _data,const F8 & _timeStamp):messageType(_messageType),data(_data),timeStamp(_timeStamp){}
		DataPacket(void * _data,const F8 & _timeStamp):messageType(MessageType::data),data(_data),timeStamp(_timeStamp){}
		DataPacket(void * _data,const F8 & _timeStamp,const int & _configFlagDummy):messageType(MessageType::config),data(_data),timeStamp(_timeStamp){}

		DataPacket(const ThisType & other):messageType(other.messageType),flushID(other.flushID),data(other.data),timeStamp(other.timeStamp){}

		void * takeData(){auto tempData = data;data = nullptr;return tempData;}

		const MessageType & getMessageType() const {return messageType;}
		const I8u         & getFlushID()     const {return flushID    ;}
		const F8          & getTimeStamp()   const {return timeStamp  ;}

	private:

		MessageType messageType;
		I8u flushID;
		void * data;
		F8 timeStamp;

};

}

}

#endif 
