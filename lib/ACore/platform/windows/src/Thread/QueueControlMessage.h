
#ifndef VIDEO__QUEUE_ControlMessage_H
#define VIDEO__QUEUE_ControlMessage_H

#include "AVL.h"
#include <Image/Image.h>

namespace Video {

namespace Queue {

enum class AVL_DLL_EXPORT ControlMessageType {
	none,
	flush, // I8u flushID
	pause,
	play,
	quit
};

class AVL_DLL_EXPORT ControlMessageParameter {
	public:
		typedef ControlMessageParameter ThisType;
		virtual void releaseParameter() = 0 ;
};

class AVL_DLL_EXPORT ControlMessageDefaultParameter : public ControlMessageParameter {
	public:
		typedef ControlMessageDefaultParameter ThisType;
		ThisType(const ThisType & other){}
		ThisType(ThisType && other){}
		ThisType(){}
		void releaseParameter() {}
};
class AVL_DLL_EXPORT ControlMessageFlushParameter : public ControlMessageParameter {
	public:
		typedef ControlMessageFlushParameter ThisType;
		ThisType(const ThisType & other):flushID(other.flushID){}
		ThisType(ThisType && other){
			flushID=other.flushID;
		}
		ThisType(const I8u & _flushID):flushID(_flushID){}

		const I8u & getFlushID() const {return flushID;}

		void releaseParameter() {}
	private:
		I8u flushID;
};

}

}

#endif 
