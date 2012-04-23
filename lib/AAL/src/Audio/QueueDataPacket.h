
#ifndef AUDIO__QUEUE_DataPacket_H
#define AUDIO__QUEUE_DataPacket_H

#include "AAL.h"

#include "QueueDataMessage.h"

namespace Audio {

namespace Queue {

class AAL_DLL_EXPORT DataPacket {
	public:
		typedef DataPacket ThisType;

		ThisType():messageType(DataMessageType::none),parameter(nullptr){}

		ThisType(const DataMessageType & _messageType):messageType(_messageType),parameter(nullptr){}
		ThisType(const DataMessageType & _messageType, DataMessageParameter * const & _parameter):messageType(_messageType),parameter(_parameter){}

		ThisType(const ThisType & _other):messageType(_other.messageType),parameter(_other.parameter){}

		void releasePacket(){parameter->releaseParameter();delete parameter;parameter=nullptr;}

		DataMessageType        & getMessageType() {return messageType;}
		DataMessageParameter * & getParameter()   {return parameter  ;}

	private:

		DataMessageType messageType;
		DataMessageParameter * parameter;

};

}

}

#endif 
