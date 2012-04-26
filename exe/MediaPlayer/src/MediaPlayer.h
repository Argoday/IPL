
#ifndef MediaPlayer_H
#define MediaPlayer_H

#include <QMainWindow>

#include <Image/Image.h>
#include <Pixel/PixelRGB.h>
#include <Data/DataManager.h>
#include <Media/PlayerControl.h>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QLabel;
class QScrollArea;
class QAbstractVideoSurface;
class QPushButton;
QT_END_NAMESPACE

class FFMPEGqtPlayer;

class MediaPlayer : public QMainWindow {
	Q_OBJECT

	public:
		MediaPlayer(Data::DataManager * const _dataManager);
		~MediaPlayer();

	private slots:
		void open();
		void exit();
		void playPause();

		void sliderChanged(int sliderIndex);
		void frameChanged(I8u frameIndex);

	signals:

		void setSlider(int sliderIndex);

	private:
		void createActions();
		void createMenus();

	//File
		QAction * openAct;
		QAction * exitAct;

		QPushButton * playPauseButton;

	//Menus
		QMenu *fileMenu;
	
		typedef Pixel::PixelRGBi1u PixelType;
		Data::DataManager * const dataManager;
		
		Media::Player::Control * mediaControl;
		FFMPEGqtPlayer * player;

};


#endif
