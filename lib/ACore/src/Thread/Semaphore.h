
#ifndef THREAD_Semaphore_H
#define THREAD_Semaphore_H

#include "ACore.h"
#include <Data/DataTypes.h>

#include <concurrent_queue.h>

namespace Thread {

class ACORE_DLL_EXPORT Semaphore {
	public:
	   explicit Semaphore(I8 capacity);

	   void acquire();
	   void release();

	private:

	   I8 count;
	   
	   Concurrency::concurrent_queue<Concurrency::Context*> waitingContexts;
	   Concurrency::critical_section criticalSection;
};

}

#endif 
