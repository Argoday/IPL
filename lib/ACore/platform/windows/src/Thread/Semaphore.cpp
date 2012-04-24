
#include "Semaphore.h"

namespace Thread {

Semaphore::Semaphore(I8 capacity)
	:count(capacity)
{
}


void Semaphore::acquire(){
	I8 tempCount;
	{
		Concurrency::critical_section::scoped_lock lock(criticalSection);
		--count;
		tempCount = count;
	}
	if(tempCount < 0){
		waitingContexts.push(Concurrency::Context::CurrentContext());
		Concurrency::Context::Block();
	}
}

void Semaphore::release(){
	I8 tempCount;
	{
		Concurrency::critical_section::scoped_lock lock(criticalSection);
		++count;
		tempCount = count;
	}
	if(tempCount <= 0){
		Concurrency::Context * waiting = nullptr;
		for(;;){
			if(waitingContexts.try_pop(waiting)==true){
				waiting->Unblock();
				break;
			}
			Concurrency::Context::Yield();
		}
	}
}

}
