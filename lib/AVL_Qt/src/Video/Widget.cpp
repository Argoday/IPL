 
#include "Widget.h"
#include "WidgetSurface.h"

#include <QtMultimedia/QtMultimedia>

namespace Video {

Widget::Widget(QWidget *parent)
	:QWidget(parent)
	,surface(0)
{
	setAutoFillBackground(false);
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_OpaquePaintEvent, true);
	setAttribute(Qt::WA_PaintUnclipped, true);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Background, Qt::black);
	setPalette(palette);

	//setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	surface = new WidgetSurface(this);
}

Widget::~Widget(){
	delete surface;
}

QSize Widget::sizeHint() const {
	return surface->surfaceFormat().sizeHint();
}

QSize Widget::minimumSizeHint() const {
	return QSize(10,10);
}

void Widget::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	if (surface->isActive()) {
		const QRect videoRect = surface->videoRect();

		if (!videoRect.contains(event->rect())) {
			QRegion region = event->region();
			region.subtract(videoRect);

			QBrush brush = palette().background();

			foreach (const QRect &rect, region.rects()){
				painter.fillRect(rect, brush);
			}
		}

		surface->paint(&painter);
	}else{
		painter.fillRect(event->rect(), palette().background());
	}
}

void Widget::resizeEvent(QResizeEvent *event){
	QWidget::resizeEvent(event);
	surface->updateVideoRect();
}

}
