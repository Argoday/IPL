
#ifndef THREAD__QUEUE__Pipe_H
#define THREAD__QUEUE__Pipe_H

#include "ACore.h"
#include "QueueControlPacket.h"
#include "QueueDataPacket.h"
#include <Data/DataTypes.h>

namespace Thread {

namespace Queue {

class ACORE_DLL_EXPORT Pipe {
	public:
		Pipe(I8 _capacity);
		~Pipe();

		// Source methods
		void sendFlush();
		void sendStop();
		void sendStart();
		void sendQuit();

		void asendData(DataPacket & dataPacket);
		void  sendData(DataPacket & dataPacket);
		void asendControl(ControlPacket & controlPacket);
		void  sendControl(ControlPacket & controlPacket);


		// Target methods
		DataPacket readData();
		B1 areadData(DataPacket & dataPacket);
		ControlPacket  readControl();
		B1            areadControl(ControlPacket & controlPacket);

	private:

		void acquireData();
		void releaseData();

		class Pipe_d;
		Pipe_d * _this;

};

}

}

#endif 
