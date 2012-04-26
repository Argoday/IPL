
#include "QueueReaderAgent.h"

namespace Thread {

namespace Queue {

void ACORE_DLL_EXPORT ReaderAgent::registerTarget(ReaderAgentTarget * const & _target){
	if(target==nullptr){
		target=_target;
		targetSetEvent.set();
	}
}

void ACORE_DLL_EXPORT ReaderAgent::run(){
	targetSetEvent.wait();
	target->init();
	
	B1  active = false;
	B1  dataFlushActive = false;
	I8u dataFlushID = 0;

	Thread::Queue::ControlPacket controlPacket;
	Thread::Queue::DataPacket    dataPacket;

	for(;;){
		Concurrency::Context::Yield();
		B1 gotControlPacket = false;
		if(active==false){
			controlPacket = sourcePipe.readControl();
			gotControlPacket = true;
		}else if(sourcePipe.areadControl(controlPacket)==true){
			gotControlPacket = true;
		}
		if(gotControlPacket==true){
			switch(controlPacket.getMessageType()){
				case Thread::Queue::ControlPacket::MessageType::flush :
					if(dataFlushActive==false){
						for(;;){
							dataPacket = sourcePipe.readData();
							if(dataPacket.getMessageType()==Thread::Queue::DataPacket::MessageType::flush){
								if(dataPacket.getFlushID()==controlPacket.getFlushID()){
									active = false;
									target->stop();
									dataFlushActive=false;
									dataFlushID=0;
									break;
								}else{
									//TODO: ERROR
									done();
									return;
								}
							}else if(dataPacket.getMessageType()==Thread::Queue::DataPacket::MessageType::quit){
								done();
								return;
							}
							target->release(dataPacket.takeData());
						}
					}else{
						if(controlPacket.getFlushID()==dataFlushID){
							dataFlushActive=false;
							dataFlushID=0;
						}else{
							//TODO: ERROR
							done();
							return;
						}
					}
				break;
				case Thread::Queue::ControlPacket::MessageType::stop :
					active = false;
					target->stop();
				break;
				case Thread::Queue::ControlPacket::MessageType::start :
					active = true;
					target->start();
				break;
				case Thread::Queue::ControlPacket::MessageType::quit :
					done();
					return;
				break;
			}
		}
		if((active==true)&&(dataFlushActive==false)){
			if(sourcePipe.areadData(dataPacket)==true){
				switch(dataPacket.getMessageType()){
					case Thread::Queue::DataPacket::MessageType::none :
					break;
					case Thread::Queue::DataPacket::MessageType::data :
						target->send(dataPacket.takeData());
					break;
					case Thread::Queue::DataPacket::MessageType::config :
						target->config(dataPacket.takeData());
					break;
					case Thread::Queue::DataPacket::MessageType::flush :
						dataFlushActive = true;
						active = false;
						target->stop();
						dataFlushID = dataPacket.getFlushID();
						target->release(dataPacket.takeData());
					break;
					case Thread::Queue::DataPacket::MessageType::quit :
						target->release(dataPacket.takeData());
						done();
						return;
					break;
				}
			}else{
				Concurrency::Context::Yield();
			}
		}
	}
	done();
}

}

}

