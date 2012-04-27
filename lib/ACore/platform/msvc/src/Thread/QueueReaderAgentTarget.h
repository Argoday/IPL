
#ifndef THREAD__QUEUE__ReaderAgentTarget_H
#define THREAD__QUEUE__ReaderAgentTarget_H

#include "ACore.h"

namespace Thread {

namespace Queue {

class ReaderAgentTarget {
	public:
		virtual void init() = 0 ;
		virtual void release(void * data) = 0 ;
		virtual void send(void * data) = 0 ;
		virtual void config(void * data) = 0 ;

		virtual void start() = 0 ;
		virtual void stop()  = 0 ;
};

}

}

#endif 
