
#ifndef THREAD_Semaphore_H
#define THREAD_Semaphore_H

#include "ACore.h"
#include <Data/DataTypes.h>

namespace Thread {

class ACORE_DLL_EXPORT Semaphore {
	public:
	   explicit Semaphore(const I8 & capacity);

	   ~Semaphore();

	   void acquire();
	   void release();

	private:
		class Semaphore_d;
		Semaphore_d * const _this;
};

}

#endif 
