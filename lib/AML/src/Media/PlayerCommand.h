
#ifndef MEDIA__PLAYER__PlayerCommand_H
#define MEDIA__PLAYER__PlayerCommand_H

#include "AML.h"
#include <Data/DataTypes.h>

#include <string>

namespace Media {

namespace Player {

enum class AML_DLL_EXPORT Command {
	none,
	play,
	pause,
	stop,
	playPause, // B1 state
	seek, // I8 timeDelta
	open, // std::string fileName, B1 autoPlay
	close,
	quit
};

class AML_DLL_EXPORT CommandParameter {
	public:
		typedef CommandParameter ThisType;
		
		virtual void releaseParameter() = 0;

};

class AML_DLL_EXPORT CommandDefaultParameter : public CommandParameter {
	public:
		typedef CommandDefaultParameter ThisType;
		ThisType(const ThisType & other){}
		ThisType(){}
		void releaseParameter(){}
	private:
};
class AML_DLL_EXPORT CommandPlayPauseParameter : public CommandParameter {
	public:
		typedef CommandPlayPauseParameter ThisType;
		ThisType(const ThisType & other):state(other.state){}
		ThisType(const B1 & _state):state(_state){}
		void releaseParameter(){}
		const B1 & getState() const {return state;}
	private:
		B1 state;
};
class AML_DLL_EXPORT CommandSeekParameter : public CommandParameter {
	public:
		typedef CommandSeekParameter ThisType;
		ThisType(const ThisType & other):timeDelta(other.timeDelta){}
		ThisType(const I8 & _timeDelta):timeDelta(_timeDelta){}
		void releaseParameter(){}
		const I8 & getTimeDelta() const {return timeDelta;}
	private:
		I8 timeDelta;
};
class AML_DLL_EXPORT CommandOpenParameter : public CommandParameter {
	public:
		typedef CommandOpenParameter ThisType;
		ThisType(const ThisType & other):autoPlay(other.autoPlay),fileName(other.fileName){}
		ThisType(const std::string & _fileName,const B1 & _autoPlay):autoPlay(_autoPlay),fileName(_fileName){}
		void releaseParameter(){}
		const B1 & getAutoPlay() const {return autoPlay;}
		const std::string & getFileName() const {return fileName;}
	private:
		std::string fileName;
		B1 autoPlay;
};

}

}

#endif 
