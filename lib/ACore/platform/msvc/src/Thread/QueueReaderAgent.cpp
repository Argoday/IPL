
#include "QueueReaderAgent.h"
#include <System/Time.h>

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
	F8 lastTimeStamp=0.0;
	F8 lastTimeDelta=0.0;

	F8 startTimeStamp = 0.0;
	F8 startWallTime  = 0.0;
	B1 resetTime      = true;

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
									lastTimeStamp=0.0;
									lastTimeDelta=0.0;
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
							active = false;
							target->stop();
							dataFlushActive=false;
							dataFlushID=0;
							lastTimeStamp=0.0;
							lastTimeDelta=0.0;
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
					lastTimeStamp=0.0;
					lastTimeDelta=0.0;
				break;
				case Thread::Queue::ControlPacket::MessageType::start :
					active = true;
					startWallTime = Time::getTime();
					resetTime = true;
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
				F8  currentWallTime;
				F8  elapsedWallTime;
				F8  elapsedPacketTime;
				F8  timeDelta;
				I4u milliSecDelay;
				switch(dataPacket.getMessageType()){
					case Thread::Queue::DataPacket::MessageType::none :
					break;
					case Thread::Queue::DataPacket::MessageType::data :
						currentWallTime = Time::getTime();
						if(resetTime==true){
							if(dataPacket.getTimeStamp()!=std::numeric_limits<F8>::infinity()){
								startTimeStamp = dataPacket.getTimeStamp();
								lastTimeDelta=0.0;
								resetTime=false;
							}
						}else{
							if(dataPacket.getTimeStamp()!=std::numeric_limits<F8>::infinity()){
								elapsedWallTime = currentWallTime - startWallTime;
								elapsedPacketTime = dataPacket.getTimeStamp() - startTimeStamp;
								timeDelta = elapsedPacketTime - elapsedWallTime;
								if(timeDelta<-10.0){//TODO: Make tolerance configurable
									milliSecDelay = static_cast<I4u>(lastTimeDelta * 1000.0);//Guess
									Concurrency::wait(milliSecDelay);
								}else if(timeDelta<0.0){
									//Catchup - mimic a 'Dropped packet'
								}else if (timeDelta<10.0){//TODO: Make tolerance configurable
									milliSecDelay = static_cast<I4u>(timeDelta * 1000.0);
									lastTimeDelta = timeDelta;
									Concurrency::wait(milliSecDelay);
								}else{
									milliSecDelay = static_cast<I4u>(lastTimeDelta * 1000.0);//Guess
									Concurrency::wait(milliSecDelay);
								}
							}else{
								milliSecDelay = static_cast<I4u>(lastTimeDelta * 1000.0);//Guess
								Concurrency::wait(milliSecDelay);
							}
						}
						target->send(dataPacket.takeData());
					break;
					case Thread::Queue::DataPacket::MessageType::config :
						target->config(dataPacket.takeData());
					break;
					case Thread::Queue::DataPacket::MessageType::flush :
						dataFlushActive = true;
						active = false;
						target->stop();
						lastTimeStamp=0.0;
						lastTimeDelta=0.0;
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

