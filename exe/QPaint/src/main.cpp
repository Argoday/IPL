
#include "ImageWindow.h"
#include <QtGui/QApplication>

#include <Data/DataManager.h>

int main(int argc, char *argv[]){

	Data::DataManager dataManager;

	QApplication a(argc, argv);
	ImageWindow w(&dataManager);
	w.show();
	return a.exec();
}
