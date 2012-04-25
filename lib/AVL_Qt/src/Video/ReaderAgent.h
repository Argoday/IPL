
#ifndef VIDEO__QUEUE__ReaderAgent_H
#define VIDEO__QUEUE__ReaderAgent_H

#include "AVL_Qt.h"
#include <Video/QueuePipe.h>

#include <QtMultimedia/QAbstractVideoSurface>

#include <agents.h>
#include <concrt.h>

namespace Video {

namespace Queue {

class AVL_QT_DLL_EXPORT ReaderAgent : public Concurrency::agent {

	public:

		typedef ReaderAgent ThisType;

		ThisType(Video::Queue::Pipe & _videoPipe)
			:dataQueue(_videoPipe.getDataQueue())
			,controlQueue(_videoPipe.getControlQueue())
			,videoPipe(_videoPipe)
			,surface(nullptr)
		{
		};

		void registerVideoSurface(QAbstractVideoSurface * const & _surface);

	protected:

		void run();

	private:

		Concurrency::event surfaceSetEvent;

		QAbstractVideoSurface * surface;

		Video::Queue::Pipe & videoPipe;
		Concurrency::ISource<Video::Queue::DataPacket>    & dataQueue;
		Concurrency::ISource<Video::Queue::ControlPacket> & controlQueue;
};

}

}

#endif 
