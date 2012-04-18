
#ifndef MediaPlayer_H
#define MediaPlayer_H

#include <QMainWindow>

#include <Image/Image.h>
#include <Pixel/PixelRGB.h>
#include <Data/DataManager.h>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QLabel;
class QScrollArea;
QT_END_NAMESPACE

class MediaPlayer : public QMainWindow {
	Q_OBJECT

	public:
		MediaPlayer(Data::DataManager * const _dataManager);
		~MediaPlayer();

	private slots:
		void open();
		void exit();

	private:
		void createActions();
		void createMenus();

		QLabel *imageLabel;

	//File
		QAction * openAct;
		QAction * exitAct;

	//Menus
		QMenu *fileMenu;
	
		typedef Pixel::PixelRGBi1u PixelType;
		Data::DataManager * dataManager;

};


#endif
