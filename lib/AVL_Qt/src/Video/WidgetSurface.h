
#ifndef VIDEO__WidgetSurface_H
#define VIDEO__WidgetSurface_H

#include "AVL_Qt.h"

#include <QtCore/QRect>
#include <QtGui/QImage>
#include <QtMultimedia/QAbstractVideoSurface>
#include <QtMultimedia/QVideoFrame>

namespace Video {

class AVL_QT_DLL_EXPORT WidgetSurface : public QAbstractVideoSurface {
	Q_OBJECT
	public:
		WidgetSurface(QWidget * widget, QObject * parent = 0);

		QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
		bool isFormatSupported(const QVideoSurfaceFormat & format, QVideoSurfaceFormat * similar) const;

		bool start(const QVideoSurfaceFormat & format);
		void stop();

		QRect videoRect() const { return targetRect; }
		void updateVideoRect();

		void paint(QPainter * painter);

	public slots:

		bool present(const QVideoFrame & frame);
		void renderFrame(const QVideoFrame & frame);

	private:
		QWidget * widget;
		QImage::Format imageFormat;
		QRect targetRect;
		QSize imageSize;
		QRect sourceRect;
		QVideoFrame currentFrame;
 };

 }

#endif 
