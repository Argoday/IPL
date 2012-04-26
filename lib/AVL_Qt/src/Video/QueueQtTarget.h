
#ifndef VIDEO__QUEUE__QtTarget_H
#define VIDEO__QUEUE__QtTarget_H

#include "AVL_Qt.h"

#include <Thread/QueueReaderAgentTarget.h>
#include <Video/Frame.h>
#include <QtMultimedia/QtMultimedia>

namespace Video {

namespace Queue {

class AVL_QT_DLL_EXPORT QtTarget : public Thread::Queue::ReaderAgentTarget {
	public:
		QtTarget(QAbstractVideoSurface * _surface):surface(_surface){}

		void init();
		void release(void * data);
		void send(void * data);
		void config(void * data){};

		void start(){};
		void stop() {};
	private:
		void release(Video::Frame<Pixel::PixelRGBi1u> * data);
		QAbstractVideoSurface * surface;
};


}

}

#endif 
