
#include "ReaderAgent.h"
#include "Image/Image_Qt.h"

#include <QtMultimedia/QtMultimedia>

namespace Video {

namespace Queue {

void AVL_QT_DLL_EXPORT ReaderAgent::registerVideoSurface(QAbstractVideoSurface * const & _surface){
	if(surface==nullptr){
		surface=_surface;
		surfaceSetEvent.set();
	}
}

void AVL_QT_DLL_EXPORT ReaderAgent::run(){
	surfaceSetEvent.wait();
	
	qRegisterMetaType<I8u>("I8u");
	qRegisterMetaType<Image::Image<Pixel::PixelRGBi1u> *>("Image::Image<Pixel::PixelRGBi1u> *");
	
	B1 playing = false;
	B1  dataFlushActive = false;
	I8u dataFlushID = 0;

	Video::Queue::ControlPacket controlPacket;
	Video::Queue::DataPacket videoPacket;

	for(;;){
		Concurrency::Context::Yield();
		Video::Queue::ControlMessageFlushParameter * controlFlushParameter = nullptr;
		Video::Queue::DataMessageFlushParameter    * dataFlushParameter    = nullptr;
		B1 gotControlPacket = false;
		if(playing==false){
			controlPacket = Concurrency::receive(controlQueue);
			gotControlPacket = true;
		}else if(Concurrency::try_receive(controlQueue,controlPacket)==true){
			gotControlPacket = true;
		}
		if(gotControlPacket==true){
			switch(controlPacket.getMessageType()){
				case Video::Queue::ControlMessageType::flush :
					controlFlushParameter = reinterpret_cast<Video::Queue::ControlMessageFlushParameter *>(controlPacket.getParameter());
					if(dataFlushActive==false){
						for(;;){
							videoPacket = Concurrency::receive(dataQueue);
							videoPipe.releaseData();
							if(videoPacket.getMessageType()==Video::Queue::DataMessageType::flush){
								dataFlushParameter = reinterpret_cast<Video::Queue::DataMessageFlushParameter *>(videoPacket.getParameter());
								if(controlFlushParameter->getFlushID()==dataFlushParameter->getFlushID()){
									playing = false;
									dataFlushActive=false;
									dataFlushID=0;
									break;
								}else{
									//TODO: ERROR
									done();
									return;
								}
							}else if(videoPacket.getMessageType()==Video::Queue::DataMessageType::quit){
								done();
								return;
							}
							videoPacket.releasePacket();
						}
					}else{
						if(controlFlushParameter->getFlushID()==dataFlushID){
							dataFlushActive=false;
							dataFlushID=0;
						}else{
							//TODO: ERROR
							done();
							return;
						}
					}
				break;
				case Video::Queue::ControlMessageType::pause :
					playing = false;
				break;
				case Video::Queue::ControlMessageType::play :
					playing = true;
				break;
				case Video::Queue::ControlMessageType::quit :
					done();
					return;
				break;
			}
			controlPacket.releasePacket();
		}
		if((playing==true)&&(dataFlushActive==false)){
			if(Concurrency::try_receive(dataQueue,videoPacket)==true){
				Video::Queue::DataMessageImageParameter<Pixel::PixelRGBi1u> * imageParameter = nullptr;
				Video::Queue::DataMessageFlushParameter * flushParameter = nullptr;
				Image::Image<Pixel::PixelRGBi1u> * image = nullptr;
				int frameIndex=0;

				switch(videoPacket.getMessageType()){
					case Video::Queue::DataMessageType::image :
				
						imageParameter = reinterpret_cast<Video::Queue::DataMessageImageParameter<Pixel::PixelRGBi1u> * >(videoPacket.getParameter());
						image = imageParameter->takeImage();
						frameIndex = imageParameter->getFrameIndex();

						//TODO: Self throttle to prevent filling the Qt Event queue with images
						if(QMetaObject::invokeMethod(surface, "renderFrame", Qt::QueuedConnection, Q_ARG(Image::Image<Pixel::PixelRGBi1u> *, image), Q_ARG(I8u, frameIndex))==false){
							//TODO: ERROR
							videoPacket.releasePacket();
							done();
							return;
						}
					break;
					case Video::Queue::DataMessageType::flush :
						dataFlushParameter = reinterpret_cast<Video::Queue::DataMessageFlushParameter *>(videoPacket.getParameter());
						dataFlushActive = true;
						playing = false;
						dataFlushID = dataFlushParameter->getFlushID();
					break;
					case Video::Queue::DataMessageType::quit :
						videoPacket.releasePacket();
						done();
						return;
					break;
				}
				videoPacket.releasePacket();
				videoPipe.releaseData();
			}else{
				Concurrency::Context::Yield();
			}
		}
	}
	done();
}

}

}

