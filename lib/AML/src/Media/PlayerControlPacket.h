
#ifndef MEDIA__PLAYER__ControlPacket_H
#define MEDIA__PLAYER__ControlPacket_H

#include "AML.h"
#include "PlayerCommand.h"

namespace Media {

namespace Player {

class AML_DLL_EXPORT ControlPacket {
	public:
		typedef ControlPacket ThisType;

		ThisType():command(Command::none),parameter(nullptr){}
		
		ThisType(const Command & _command):command(_command),parameter(nullptr){}
		ThisType(const Command & _command, CommandParameter * const & _parameter):command(_command),parameter(_parameter){}

		ThisType(const ThisType & _other):command(_other.command),parameter(_other.parameter){}

		void releasePacket(){if(parameter!=nullptr){parameter->releaseParameter();delete parameter;parameter=nullptr;}}

		Command            & getCommand()   {return command  ;}
		CommandParameter * & getParameter() {return parameter;}

	private:

		Command command;
		CommandParameter * parameter;

};

}

}

#endif 
