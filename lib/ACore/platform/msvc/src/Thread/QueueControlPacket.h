
#ifndef THREAD__QUEUE_ControlPacket_H
#define THREAD__QUEUE_ControlPacket_H

#include "ACore.h"
#include <Data/DataTypes.h>

namespace Thread {

namespace Queue {

class ACORE_DLL_EXPORT ControlPacket {
	public:
		enum class MessageType {
			none,
			flush, // I8u flushID
			start,
			stop,
			quit
		};

		typedef ControlPacket ThisType;

		ControlPacket():messageType(MessageType::none),flushID(0){}

		ControlPacket(const MessageType & _messageType):messageType(_messageType),flushID(0){}
		ControlPacket(const MessageType & _messageType, const I8u & _flushID):messageType(_messageType),flushID(_flushID){}

		ControlPacket(const ThisType & _other):messageType(_other.messageType),flushID(_other.flushID){}

		const MessageType & getMessageType() const {return messageType;}
		const I8u         & getFlushID()     const {return flushID    ;}

	private:

		MessageType messageType;
		I8u flushID;

};

}

}

#endif 
