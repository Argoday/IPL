
#include "QueuePipe.h"

#include <Thread/Semaphore.h>

#include "agents.h"
namespace Thread {

namespace Queue {

class Pipe::Pipe_d {
	public:
		Pipe_d(I8 _capacity)
			:dataCapacity(_capacity)
			,flushID(0)
			,dataQueueSource(dataQueue)
			,dataQueueTarget(dataQueue)
			,controlQueueSource(controlQueue)
			,controlQueueTarget(controlQueue)
		{
		}
		Thread::Semaphore dataCapacity;

		Concurrency::unbounded_buffer<Thread::Queue::DataPacket> dataQueue;
		Concurrency::ISource<Thread::Queue::DataPacket> & dataQueueSource;
		Concurrency::ITarget<Thread::Queue::DataPacket> & dataQueueTarget;

		Concurrency::unbounded_buffer<Thread::Queue::ControlPacket> controlQueue;
		Concurrency::ISource<Thread::Queue::ControlPacket> & controlQueueSource;
		Concurrency::ITarget<Thread::Queue::ControlPacket> & controlQueueTarget;

		I8u flushID;
};

ACORE_DLL_EXPORT Pipe::Pipe(I8 _capacity)
	:_this(new Pipe_d(_capacity))
{
}
ACORE_DLL_EXPORT Pipe::~Pipe(){
	delete _this;
}
void ACORE_DLL_EXPORT Pipe::sendFlush(){
	++_this->flushID;
	auto dataPacket = Thread::Queue::DataPacket(Thread::Queue::DataPacket::MessageType::flush,_this->flushID);
	asendData(dataPacket);

	auto controlPacket = Thread::Queue::ControlPacket(Thread::Queue::ControlPacket::MessageType::flush,_this->flushID);
	asendControl(controlPacket);
}
void ACORE_DLL_EXPORT Pipe::sendStart(){
	auto controlPacket = Thread::Queue::ControlPacket(Thread::Queue::ControlPacket::MessageType::start);
	asendControl(controlPacket);
}
void ACORE_DLL_EXPORT Pipe::sendStop(){
	auto controlPacket = Thread::Queue::ControlPacket(Thread::Queue::ControlPacket::MessageType::stop);
	asendControl(controlPacket);
}
void ACORE_DLL_EXPORT Pipe::sendQuit(){
	auto dataPacket = Thread::Queue::DataPacket(Thread::Queue::DataPacket::MessageType::quit);
	asendData(dataPacket);

	auto controlPacket = Thread::Queue::ControlPacket(Thread::Queue::ControlPacket::MessageType::quit);
	asendControl(controlPacket);
}
void ACORE_DLL_EXPORT Pipe::asendData(DataPacket & dataPacket){
	acquireData();
	Concurrency::asend(_this->dataQueueTarget,dataPacket);
}
void ACORE_DLL_EXPORT Pipe::sendData(DataPacket & dataPacket){
	acquireData();
	Concurrency::send(_this->dataQueueTarget,dataPacket);
}
void ACORE_DLL_EXPORT Pipe::asendControl(ControlPacket & controlPacket){
	Concurrency::asend(_this->controlQueueTarget,controlPacket);
}
void ACORE_DLL_EXPORT Pipe::sendControl(ControlPacket & controlPacket){
	Concurrency::send(_this->controlQueueTarget,controlPacket);
}

DataPacket ACORE_DLL_EXPORT Pipe::readData(){
	auto ret = Concurrency::receive(_this->dataQueueSource);
	releaseData();
	return ret;
}
B1 ACORE_DLL_EXPORT Pipe::areadData(DataPacket & dataPacket){
	auto ret = Concurrency::try_receive(_this->dataQueueSource,dataPacket);
	if(ret==true){releaseData();}
	return ret;
}
ControlPacket ACORE_DLL_EXPORT Pipe::readControl(){
	return Concurrency::receive(_this->controlQueueSource);
}
B1 ACORE_DLL_EXPORT Pipe::areadControl(ControlPacket & controlPacket){
	return Concurrency::try_receive(_this->controlQueueSource,controlPacket);
}

void ACORE_DLL_EXPORT Pipe::acquireData(){_this->dataCapacity.acquire();}
void ACORE_DLL_EXPORT Pipe::releaseData(){_this->dataCapacity.release();}


}

}
