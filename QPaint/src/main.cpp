
#include "ImageWindow.h"
#include <QtGui/QApplication>

#include <Data/DataManager.h>

#include <stdio.h>
#include <windows.h>
 

int main(int argc, char *argv[]){

	SYSTEM_INFO si;
	GetSystemInfo(&si);
 
	int pageSize = si.dwPageSize;

	Data::DataManager dataManager;

	QApplication a(argc, argv);
	ImageWindow w(&dataManager);     // Create an ImageWindow class,
	w.show();        // show it (by default hidden)
	return a.exec(); // begin execution state, app runs until User quits via ImageWindow
}
