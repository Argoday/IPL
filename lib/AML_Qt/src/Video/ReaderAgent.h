
#ifndef VIDEO__QUEUE__ReaderAgent_H
#define VIDEO__QUEUE__ReaderAgent_H

#include "AML_Qt.h"
#include <Video/QueuePipe.h>

#include <QtMultimedia/QAbstractVideoSurface>

#include <agents.h>

namespace Video {

namespace Queue {

class AML_QT_DLL_EXPORT ReaderAgent : public Concurrency::agent {

	public:

		typedef ReaderAgent ThisType;

		ThisType(Video::Queue::Pipe & _videoPipe):dataQueue(_videoPipe.getDataQueue()),videoPipe(_videoPipe),surface(nullptr){};

		void registerVideoSurface(QAbstractVideoSurface * const & _surface);

	protected:

		void run();

	private:

		QAbstractVideoSurface * surface;

		Video::Queue::Pipe & videoPipe;
		Concurrency::ISource<Video::Queue::DataPacket> & dataQueue;
};

}

}

#endif 
