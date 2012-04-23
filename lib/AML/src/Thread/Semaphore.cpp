
#include "Semaphore.h"

namespace Thread {

Semaphore::Semaphore(I8 capacity)
	:count(capacity)
{
}


void Semaphore::acquire(){
	{
		Concurrency::critical_section::scoped_lock lock(criticalSection);
		--count;
	}
	if(count < 0){
		waitingContexts.push(Concurrency::Context::CurrentContext());
		Concurrency::Context::Block();
	}
}

void Semaphore::release(){
	{
		Concurrency::critical_section::scoped_lock lock(criticalSection);
		++count;
	}
	if(count <= 0){
		Concurrency::Context * waiting = nullptr;
		if (!waitingContexts.try_pop(waiting)){
			Concurrency::Context::Yield();
		}
		waiting->Unblock();
	}
}

}
