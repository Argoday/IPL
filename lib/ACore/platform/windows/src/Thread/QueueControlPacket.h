
#ifndef VIDEO__QUEUE_ControlPacket_H
#define VIDEO__QUEUE_ControlPacket_H

#include "AVL.h"

#include "QueueControlMessage.h"

namespace Video {

namespace Queue {

class AVL_DLL_EXPORT ControlPacket {
	public:
		typedef ControlPacket ThisType;

		ThisType():messageType(ControlMessageType::none),parameter(nullptr){}

		ThisType(const ControlMessageType & _messageType):messageType(_messageType),parameter(nullptr){}
		ThisType(const ControlMessageType & _messageType, ControlMessageParameter * const & _parameter):messageType(_messageType),parameter(_parameter){}

		ThisType(const ThisType & _other):messageType(_other.messageType),parameter(_other.parameter){}

		void releasePacket(){if(parameter!=nullptr){parameter->releaseParameter();delete parameter;parameter=nullptr;}}

		ControlMessageType        & getMessageType() {return messageType;}
		ControlMessageParameter * & getParameter()   {return parameter  ;}

	private:

		ControlMessageType messageType;
		ControlMessageParameter * parameter;

};

}

}

#endif 
