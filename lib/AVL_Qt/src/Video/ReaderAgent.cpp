
#include "ReaderAgent.h"
#include "Image/Image_Qt.h"

#include <QtMultimedia/QtMultimedia>

namespace Video {

namespace Queue {


void AVL_QT_DLL_EXPORT ReaderAgent::registerVideoSurface(QAbstractVideoSurface * const & _surface){
	surface=_surface;
}

void AVL_QT_DLL_EXPORT ReaderAgent::run(){
	//TODO: BUG: Add a wait event for surface!=nullptr
	
	qRegisterMetaType<QVideoFrame>("QVideoFrame");

	B1 playing = false;
	B1  dataFlushActive = false;
	I8u dataFlushID = 0;

	Video::Queue::ControlPacket controlPacket;
	Video::Queue::DataPacket videoPacket;

	for(;;){
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
		}
		if((playing==true)&&(dataFlushActive==false)){
			if(Concurrency::try_receive(dataQueue,videoPacket)==true){
				videoPipe.releaseData();
		
				Video::Queue::DataMessageImageParameter<Pixel::PixelRGBi1u> * imageParameter = nullptr;
				Video::Queue::DataMessageFlushParameter * flushParameter = nullptr;
				QImage qimage;
				QVideoFrame frame;
				QVideoSurfaceFormat currentFormat;
				QVideoSurfaceFormat format;
				int frameIndex=0;

				switch(videoPacket.getMessageType()){
					case Video::Queue::DataMessageType::image :
				
						imageParameter = reinterpret_cast<Video::Queue::DataMessageImageParameter<Pixel::PixelRGBi1u> *>(videoPacket.getParameter());
						qimage = Image::Convert::toQt<Pixel::PixelRGBi1u>(*imageParameter->getImage());
						frameIndex = imageParameter->getFrameIndex();
						videoPacket.releasePacket();

						frame = qimage;
						if (!frame.isValid()){
							//TODO: ERROR
							done();
							return;
						}

						currentFormat = surface->surfaceFormat();

						if (frame.pixelFormat() != currentFormat.pixelFormat() || frame.size() != currentFormat.frameSize()) {
							format = QVideoSurfaceFormat(frame.size(), frame.pixelFormat());
							if (!surface->start(format)){
								//TODO: ERROR
								done();
								return;
							}
						}

						if(QMetaObject::invokeMethod(surface, "renderFrame", Qt::AutoConnection, Q_ARG(QVideoFrame, frame), Q_ARG(int, frameIndex))==false){
							//TODO: ERROR
							done();
							return;
						}
					break;
					case Video::Queue::DataMessageType::flush :
						dataFlushParameter = reinterpret_cast<Video::Queue::DataMessageFlushParameter *>(videoPacket.getParameter());
						dataFlushActive = true;
						playing = false;
						dataFlushID = dataFlushParameter->getFlushID();
						videoPacket.releasePacket();
					case Video::Queue::DataMessageType::quit :
						done();
						return;
					break;
				}
			}
		}
	}
	done();
}

}

}
