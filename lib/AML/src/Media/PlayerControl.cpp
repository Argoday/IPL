
#include "PlayerControl.h"

namespace Media {

namespace Player {

void AML_DLL_EXPORT Control::open(const std::string & fileName){
	open(fileName,true);
}
void AML_DLL_EXPORT Control::open(const std::string & fileName,const B1 & autoPlay){
	auto messageParameter = new CommandOpenParameter(fileName,autoPlay);
	auto controlPacket = ControlPacket(Command::open,messageParameter);
	Concurrency::asend(controlQueue,controlPacket);
}
void AML_DLL_EXPORT Control::close(){
	auto controlPacket = ControlPacket(Command::close);
	Concurrency::asend(controlQueue,controlPacket);
}
void AML_DLL_EXPORT Control::play(){
	auto controlPacket = ControlPacket(Command::play);
	Concurrency::asend(controlQueue,controlPacket);
}
void AML_DLL_EXPORT Control::pause(){
	auto controlPacket = ControlPacket(Command::pause);
	Concurrency::asend(controlQueue,controlPacket);
}
void AML_DLL_EXPORT Control::stop(){
	auto controlPacket = ControlPacket(Command::stop);
	Concurrency::asend(controlQueue,controlPacket);
}
void AML_DLL_EXPORT Control::playPause(){
	auto controlPacket = ControlPacket(Command::playPause);
	Concurrency::asend(controlQueue,controlPacket);
}
void AML_DLL_EXPORT Control::playPause(const B1 & state){
	auto messageParameter = new CommandPlayPauseParameter(state);
	auto controlPacket = ControlPacket(Command::playPause,messageParameter);
	Concurrency::asend(controlQueue,controlPacket);
}
void AML_DLL_EXPORT Control::seek(const I8 & videoFrameIndex){
	auto messageParameter = new CommandSeekParameter(videoFrameIndex);
	auto controlPacket = ControlPacket(Command::seek,messageParameter);
	Concurrency::asend(controlQueue,controlPacket);
}
void AML_DLL_EXPORT Control::quit(){
	auto controlPacket = ControlPacket(Command::quit);
	Concurrency::asend(controlQueue,controlPacket);
}

}

}
