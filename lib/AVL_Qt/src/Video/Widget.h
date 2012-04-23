
#ifndef VIDEO__Widget_H
#define VIDEO__Widget_H

#include "AVL_Qt.h"
#include "WidgetSurface.h"

#include <QtGui/QWidget>
class QAbstractVideoSurface;

namespace Video {

class AVL_QT_DLL_EXPORT Widget : public QWidget {
	Q_OBJECT
	public:
		Widget(QWidget * parent = 0);
		~Widget();

		QAbstractVideoSurface * videoSurface() const { return surface; }

		QSize sizeHint() const ;
		QSize minimumSizeHint() const ;

	protected:
		void paintEvent(QPaintEvent * event);
		void resizeEvent(QResizeEvent * event);

	private:
		WidgetSurface * surface;
};

}

#endif 
