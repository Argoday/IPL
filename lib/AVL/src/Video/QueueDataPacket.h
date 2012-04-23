
#ifndef VIDEO__QUEUE_DataPacket_H
#define VIDEO__QUEUE_DataPacket_H

#include "AVL.h"

#include "QueueDataMessage.h"

namespace Video {

namespace Queue {

class AVL_DLL_EXPORT DataPacket {
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
