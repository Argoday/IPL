
#ifndef MediaPlayer_H
#define MediaPlayer_H

#include <QMainWindow>

#include <Image/Image.h>
#include <Pixel/PixelRGB.h>
#include <Data/DataManager.h>
#include <Media/PlayerControl.h>
#include <Video/ReaderAgent.h>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QLabel;
class QScrollArea;
class QAbstractVideoSurface;
QT_END_NAMESPACE

class MediaPlayer : public QMainWindow {
	Q_OBJECT

	public:
		MediaPlayer(Data::DataManager * const _dataManager,Media::Player::Control * const _mediaControl,Video::Queue::ReaderAgent * const readerAgent);
		~MediaPlayer();

	private slots:
		void open();
		void exit();

	private:
		void createActions();
		void createMenus();

	//File
		QAction * openAct;
		QAction * exitAct;

	//Menus
		QMenu *fileMenu;
	
		QAbstractVideoSurface * surface;

		typedef Pixel::PixelRGBi1u PixelType;
		Data::DataManager * const dataManager;
		Media::Player::Control * const mediaControl;

};


#endif
