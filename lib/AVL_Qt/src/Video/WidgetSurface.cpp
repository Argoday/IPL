
#include "WidgetSurface.h"

#include <QtMultimedia/QtMultimedia>

namespace Video {

AVL_QT_DLL_EXPORT WidgetSurface::WidgetSurface(QWidget *widget, QObject *parent)
	:QAbstractVideoSurface(parent)
	,widget(widget)
	,imageFormat(QImage::Format_Invalid)
{
}
QList<QVideoFrame::PixelFormat> AVL_QT_DLL_EXPORT WidgetSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const {
	if (handleType == QAbstractVideoBuffer::NoHandle) {
		return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB32;
	} else {
		return QList<QVideoFrame::PixelFormat>();
	}
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
	const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
	const QSize size = format.frameSize();

	if (imageFormat != QImage::Format_Invalid && !size.isEmpty()) {
		this->imageFormat = imageFormat;
		imageSize = size;
		sourceRect = format.viewport();

		QAbstractVideoSurface::start(format);

		widget->updateGeometry();
		updateVideoRect();

		return true;
	} else {
		return false;
	}
}
void AVL_QT_DLL_EXPORT WidgetSurface::updateVideoRect(){
	QSize size = surfaceFormat().sizeHint();
	size.scale(widget->size().boundedTo(size), Qt::KeepAspectRatio);

	targetRect = QRect(QPoint(0, 0), size);
	targetRect.moveCenter(widget->rect().center());
}

bool AVL_QT_DLL_EXPORT WidgetSurface::present(const QVideoFrame & frame){
	return false;
}
void AVL_QT_DLL_EXPORT WidgetSurface::renderFrame(const QVideoFrame & frame,const int & frameIndex){
	if (surfaceFormat().pixelFormat() != frame.pixelFormat() || surfaceFormat().frameSize() != frame.size()) {
		setError(IncorrectFormatError);
		stop();
	} else {
		currentFrame = frame;
		widget->repaint(targetRect);
	}
	emit frameChanged(frameIndex);
}

void AVL_QT_DLL_EXPORT WidgetSurface::paint(QPainter *painter){
	if (currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {
		const QTransform oldTransform = painter->transform();

		if (surfaceFormat().scanLineDirection() == QVideoSurfaceFormat::BottomToTop) {
			painter->scale(1, -1);
			painter->translate(0, -widget->height());
		}

		QImage image(
				currentFrame.bits(),
				currentFrame.width(),
				currentFrame.height(),
				currentFrame.bytesPerLine(),
				imageFormat);

		painter->drawImage(targetRect, image, sourceRect);

		painter->setTransform(oldTransform);

		currentFrame.unmap();
	}
}

void AVL_QT_DLL_EXPORT WidgetSurface::stop(){
	currentFrame = QVideoFrame();
	targetRect = QRect();

	QAbstractVideoSurface::stop();

	widget->update();
}

}
