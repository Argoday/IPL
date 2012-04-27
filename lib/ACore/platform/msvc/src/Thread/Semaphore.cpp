
#include "Semaphore.h"

#include <concurrent_queue.h>

namespace Thread {

class Semaphore::Semaphore_d {
	public:
		volatile I8 count;

		Concurrency::concurrent_queue<Concurrency::Context*> waitingContexts;
		Concurrency::critical_section criticalSection;
};


Semaphore::Semaphore(I8 capacity)
	:_this(new Semaphore_d)
{
	_this->count = capacity;
}

Semaphore::~Semaphore(){
	delete _this;
}

void Semaphore::acquire(){
	I8 tempCount;
	{
		Concurrency::critical_section::scoped_lock lock(_this->criticalSection);
		--_this->count;
		tempCount = _this->count;
	}
	if(tempCount < 0){
		_this->waitingContexts.push(Concurrency::Context::CurrentContext());
		Concurrency::Context::Block();
	}
}

void Semaphore::release(){
	I8 tempCount;
	{
		Concurrency::critical_section::scoped_lock lock(_this->criticalSection);
		++_this->count;
		tempCount = _this->count;
	}
	if(tempCount <= 0){
		Concurrency::Context * waiting = nullptr;
		for(;;){
			if(_this->waitingContexts.try_pop(waiting)==true){
				waiting->Unblock();
				break;
			}
			Concurrency::Context::Yield();
		}
	}
}

}
