
#include "ReaderAgent.h"
#include "Image/Image_Qt.h"

#include <QtMultimedia/QtMultimedia>

namespace Video {

namespace Queue {


void AML_QT_DLL_EXPORT ReaderAgent::registerVideoSurface(QAbstractVideoSurface * const & _surface){
	surface=_surface;
}

void AML_QT_DLL_EXPORT ReaderAgent::run(){
	for(;;){
		Video::Queue::DataPacket videoPacket;
		videoPacket = Concurrency::receive(dataQueue);
		videoPipe.releaseData();
		//TODO: BUG: Add a wait event for surface!=nullptr
		
		Video::Queue::DataMessageImageParameter<Pixel::PixelRGBi1u> * imageParameter = nullptr;
		QImage qimage;
		QVideoFrame frame;
		QVideoSurfaceFormat currentFormat;
		QVideoSurfaceFormat format;

		switch(videoPacket.getMessageType()){
			case Video::Queue::DataMessageType::image :
				
				imageParameter = reinterpret_cast<Video::Queue::DataMessageImageParameter<Pixel::PixelRGBi1u> *>(videoPacket.getParameter());
				qimage = Image::Convert::toQt<Pixel::PixelRGBi1u>(*imageParameter->getImage());
				videoPacket.releasePacket();

				frame = qimage;
				
				if (!frame.isValid()){
					done();
					return;
				}

				currentFormat = surface->surfaceFormat();

				if (frame.pixelFormat() != currentFormat.pixelFormat() || frame.size() != currentFormat.frameSize()) {
					format = QVideoSurfaceFormat(frame.size(), frame.pixelFormat());
					if (!surface->start(format)){
						done();
						return;
					}
				}

				if(QMetaObject::invokeMethod(surface, "renderFrame", Qt::AutoConnection, Q_ARG(QVideoFrame, frame))==false){
					surface->stop();
					done();
					return;
				}
			break;
			case Video::Queue::DataMessageType::quit :
				done();
				return;
			break;
		}
	}
	done();
}

}

}
