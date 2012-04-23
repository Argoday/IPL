
#ifndef VIDEO__QUEUE__Pipe_H
#define VIDEO__QUEUE__Pipe_H

#include "AML.h"
#include "QueueControlPacket.h"
#include "QueueDataPacket.h"
#include <Data/DataTypes.h>
#include <Thread/Semaphore.h>

#include "agents.h"

namespace Video {

namespace Queue {

class AML_DLL_EXPORT Pipe {
	public:
		Pipe(I8 _capacity):dataCapacity(_capacity){};

		void aboutToSendData(){dataCapacity.acquire();}
		void releaseData(){dataCapacity.release();}

		Concurrency::unbounded_buffer<Video::Queue::DataPacket>    & getDataQueue()   {return dataQueue;}
		Concurrency::unbounded_buffer<Video::Queue::ControlPacket> & getControlQueue(){return controlQueue;}

	private:
		Thread::Semaphore dataCapacity;
		Concurrency::unbounded_buffer<Video::Queue::DataPacket>    dataQueue;
		Concurrency::unbounded_buffer<Video::Queue::ControlPacket> controlQueue;
};

}

}

#endif 
