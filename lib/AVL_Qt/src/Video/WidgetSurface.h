
#ifndef VIDEO__WidgetSurface_H
#define VIDEO__WidgetSurface_H

#include "AVL_Qt.h"

#include <Data/DataTypes.h>
#include <Image/Image.h>

#include <QtCore/QRect>
#include <QtGui/QImage>
#include <QtMultimedia/QAbstractVideoSurface>
#include <QtMultimedia/QVideoFrame>

namespace Video {

class AVL_QT_DLL_EXPORT WidgetSurface : public QAbstractVideoSurface {
	Q_OBJECT
	public:
		WidgetSurface(QWidget * widget, QObject * parent = 0);

		~WidgetSurface();

		QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
		bool isFormatSupported(const QVideoSurfaceFormat & format, QVideoSurfaceFormat * similar) const;

		bool start(const QVideoSurfaceFormat & format);
		void stop();

		QRect videoRect() const { return targetRect; }
		void updateVideoRect();

		void paint(QPainter * painter);

	signals:

		void frameChanged(I8u frame);
		void durationFramesChanged(const I8u & durationFrames);

	public slots:

		bool present(const QVideoFrame & frame);

		void config(const I8u & durationFrames);
		void renderFrame(Image::Image<Pixel::PixelRGBi1u> * frame,const I8u & frameIndex);

	private:
		QWidget * widget;
		QRect targetRect;
		Image::ImageSize imageSize;
		QRect sourceRect;
		Image::Image<Pixel::PixelRGBi1u> * currentFrame;
		QImage currentQFrame;
};

}

#endif 
