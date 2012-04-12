
#ifndef FSWP__MainObject_H
#define FSWP__MainObject_H

#include <qobject.h>
#include <qapplication.h>

void realMain();

class MainObject : public QObject {
	Q_OBJECT
public:
	explicit MainObject(QObject *parent = 0) : QObject(parent) {}
 
signals:

public slots:
	void startApplication() {
		realMain();
		QApplication::quit();
	}
};

#endif
