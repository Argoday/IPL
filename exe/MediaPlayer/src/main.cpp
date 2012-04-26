
#include "MediaPlayer.h"

#include <QtGui/QApplication>

#include <Data/DataManager.h>

int main(int argc, char *argv[]){

	Data::DataManager dataManager;

	QApplication a(argc, argv);
	MediaPlayer w(&dataManager);

	w.show();

	I4 ret = a.exec();

	return ret;
}
