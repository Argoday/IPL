
#ifndef IMAGECONVERT__MainObject_H
#define IMAGECONVERT__MainObject_H

#include <qobject.h>
#include <qcoreapplication.h>
#include <qstringlist.h>

void realMain(const QStringList &args,const QString & filePath);

class MainObject : public QObject {
	Q_OBJECT
	public:
		explicit MainObject(QObject *parent = 0) : QObject(parent) {}
 
	signals:

	public slots:
		void startApplication() {
			realMain(QCoreApplication::arguments(),QCoreApplication::applicationDirPath());
			QCoreApplication::quit();
		}
};

#endif
