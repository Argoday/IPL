
#ifndef AUDIO__QUEUE__Pipe_H
#define AUDIO__QUEUE__Pipe_H

#include "AAL.h"
#include "QueueControlPacket.h"
#include "QueueDataPacket.h"
#include <Data/DataTypes.h>
#include <Thread/Semaphore.h>

#include "agents.h"

namespace Audio {

namespace Queue {

class AAL_DLL_EXPORT Pipe {
	public:
		Pipe(I8 _capacity):dataCapacity(_capacity){};

		void aboutToSendData(){dataCapacity.acquire();}
		void releaseData(){dataCapacity.release();}

		Concurrency::unbounded_buffer<Audio::Queue::DataPacket>    & getDataQueue()   {return dataQueue;}
		Concurrency::unbounded_buffer<Audio::Queue::ControlPacket> & getControlQueue(){return controlQueue;}

	private:
		Thread::Semaphore dataCapacity;
		Concurrency::unbounded_buffer<Audio::Queue::DataPacket>    dataQueue;
		Concurrency::unbounded_buffer<Audio::Queue::ControlPacket> controlQueue;
};

}

}

#endif 
