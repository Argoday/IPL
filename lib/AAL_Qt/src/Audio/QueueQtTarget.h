
#ifndef AUDIO__QUEUE__QtTarget_H
#define AUDIO__QUEUE__QtTarget_H

#include "AAL_Qt.h"

#include <Thread/QueueReaderAgentTarget.h>
#include <Audio/Frame.h>
#include <Audio/Config.h>
#include "AudioQtDevice.h"

namespace Audio {

namespace Queue {

class AAL_QT_DLL_EXPORT QtTarget : public Thread::Queue::ReaderAgentTarget {
	public:
		QtTarget(AudioQtDevice * _device):device(_device){}

		void init();
		void release(void * data);
		void send(void * data);
		void config(void * data);

		void start();
		void stop();
	private:
		void release(Audio::Frame  * data);
		void release(Audio::Config * data);
		AudioQtDevice * device;
};


}

}

#endif 
