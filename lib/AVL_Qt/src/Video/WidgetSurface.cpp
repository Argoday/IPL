
#include "WidgetSurface.h"

#include <QtMultimedia/QtMultimedia>

namespace Video {

AVL_QT_DLL_EXPORT WidgetSurface::WidgetSurface(QWidget *widget, QObject *parent)
	:QAbstractVideoSurface(parent)
	,widget(widget)
	,currentFrame(nullptr)
{
}
AVL_QT_DLL_EXPORT WidgetSurface::~WidgetSurface(){
	if(currentFrame!=nullptr){delete currentFrame;currentFrame = nullptr;}
}
QList<QVideoFrame::PixelFormat> AVL_QT_DLL_EXPORT WidgetSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const {
	return QList<QVideoFrame::PixelFormat>();
}

bool AVL_QT_DLL_EXPORT WidgetSurface::isFormatSupported(const QVideoSurfaceFormat & format, QVideoSurfaceFormat * similar) const {
	Q_UNUSED(similar);

	const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
	const QSize size = format.frameSize();

	return imageFormat != QImage::Format_Invalid
		&& !size.isEmpty()
		&& format.handleType() == QAbstractVideoBuffer::NoHandle;
}

bool AVL_QT_DLL_EXPORT WidgetSurface::start(const QVideoSurfaceFormat & format){
	const QSize size = format.frameSize();

	if (size.isEmpty()==false) {
		imageSize.set(size.width(),size.height());
		sourceRect = format.viewport();

		QAbstractVideoSurface::start(format);

		widget->updateGeometry();
		updateVideoRect();

		return true;
	}else{
		return false;
	}
}
void AVL_QT_DLL_EXPORT WidgetSurface::updateVideoRect(){
	QSize videoSize  = surfaceFormat().sizeHint();
	QSize widgetSize = widget->size();

	QSize targetSize = videoSize;
	targetSize.scale(widgetSize, Qt::KeepAspectRatio);

	targetRect = QRect(QPoint(0, 0), targetSize);
	targetRect.moveCenter(widget->rect().center());
}

bool AVL_QT_DLL_EXPORT WidgetSurface::present(const QVideoFrame & frame){
	return false;
}
void AVL_QT_DLL_EXPORT WidgetSurface::config(const I8u & durationFrames){
	emit durationFramesChanged(durationFrames);
}
void AVL_QT_DLL_EXPORT WidgetSurface::renderFrame(Image::Image<Pixel::PixelRGBi1u> * frame,const I8u & frameIndex){
	if(currentFrame!=nullptr){delete currentFrame;}
	currentFrame = frame;
	currentQFrame = QImage(static_cast<uchar*>(static_cast<void*>(currentFrame->getDataPtr())),currentFrame->getWidth(),currentFrame->getHeight(),currentFrame->getWidth()*3,QImage::Format_RGB888);
	if (imageSize != frame->getSize()) {
		if(start(QVideoSurfaceFormat(QSize(frame->getWidth(),frame->getHeight()), QVideoFrame::pixelFormatFromImageFormat(QImage::Format_RGB888)))==false){
			//TODO: ERROR
			return;
		}
		widget->repaint();
	}else{
		widget->repaint(targetRect);
	}
	emit frameChanged(frameIndex);
}

void AVL_QT_DLL_EXPORT WidgetSurface::paint(QPainter *painter){
	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	painter->drawImage(targetRect, currentQFrame, sourceRect);
}

void AVL_QT_DLL_EXPORT WidgetSurface::stop(){
	if(currentFrame!=nullptr){delete currentFrame;currentFrame = nullptr;}
	currentQFrame = QImage(0,0,QImage::Format_RGB888);
	targetRect = QRect();
	imageSize = Image::ImageSize(0,0);

	QAbstractVideoSurface::stop();

	widget->update();
}

}
