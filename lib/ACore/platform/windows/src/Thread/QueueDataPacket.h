
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
			data,  // void * data
			flush, // I8u flushID
			quit
		};
		typedef DataPacket ThisType;

		ThisType():messageType(MessageType::none),flushID(0),data(nullptr){}

		ThisType(const MessageType & _messageType):messageType(_messageType),flushID(0),data(nullptr){}
		ThisType(const MessageType & _messageType, const I8u & _flushID):messageType(_messageType),flushID(_flushID),data(nullptr){}
		ThisType(const MessageType & _messageType, void * _data):messageType(_messageType),data(_data){}

		ThisType(const ThisType & _other):messageType(_other.messageType),flushID(_other.flushID),data(_other.data){}

		void * takeData(){auto tempData = data;data = nullptr;return tempData;}

		const MessageType & getMessageType() const {return messageType;}
		const I8u         & getFlushID()     const {return flushID    ;}

	private:

		MessageType messageType;
		I8u flushID;
		void * data;

};

}

}

#endif 
