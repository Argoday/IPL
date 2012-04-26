
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
	
	B1 playing = false;
	B1  dataFlushActive = false;
	I8u dataFlushID = 0;

	Thread::Queue::ControlPacket controlPacket;
	Thread::Queue::DataPacket    dataPacket;

	for(;;){
		Concurrency::Context::Yield();
		B1 gotControlPacket = false;
		if(playing==false){
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
									playing = false;
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
					playing = false;
				break;
				case Thread::Queue::ControlPacket::MessageType::start :
					playing = true;
				break;
				case Thread::Queue::ControlPacket::MessageType::quit :
					done();
					return;
				break;
			}
		}
		if((playing==true)&&(dataFlushActive==false)){
			if(sourcePipe.areadData(dataPacket)==true){
				//Video::Queue::DataMessageImageParameter<Pixel::PixelRGBi1u> * imageParameter = nullptr;
				//Image::Image<Pixel::PixelRGBi1u> * image = nullptr;
				//int frameIndex=0;

				switch(dataPacket.getMessageType()){
					case Thread::Queue::DataPacket::MessageType::data :
						target->send(dataPacket.takeData());


						//imageParameter = reinterpret_cast<Video::Queue::DataMessageImageParameter<Pixel::PixelRGBi1u> * >(videoPacket.getParameter());
						//image = imageParameter->takeImage();
						//frameIndex = imageParameter->getFrameIndex();

						//TODO: Self throttle to prevent filling the Qt Event queue with images
						//if(QMetaObject::invokeMethod(surface, "renderFrame", Qt::QueuedConnection, Q_ARG(Image::Image<Pixel::PixelRGBi1u> *, image), Q_ARG(I8u, frameIndex))==false){
						//	//TODO: ERROR
						//	return;
						//}
					break;
					case Thread::Queue::DataPacket::MessageType::flush :
						dataFlushActive = true;
						playing = false;
						dataFlushID = dataPacket.getFlushID();
					break;
					case Thread::Queue::DataPacket::MessageType::quit :
						target->release(dataPacket.takeData());
						done();
						return;
					break;
				}
				target->release(dataPacket.takeData());
			}else{
				Concurrency::Context::Yield();
			}
		}
	}
	done();
}

}

}

