
#ifndef MediaPlayer_H
#define MediaPlayer_H

#include <QMainWindow>

#include <Image/Image.h>
#include <Pixel/PixelRGB.h>
#include <Data/DataManager.h>
#include <Media/PlayerControl.h>
#include <Media/FFMPEGqtPlayer.h>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QLabel;
class QScrollArea;
class QAbstractVideoSurface;
class QPushButton;
class QSlider;
QT_END_NAMESPACE

class MediaPlayer : public QMainWindow {
	Q_OBJECT

	public:
		MediaPlayer(Data::DataManager * const _dataManager);

	private slots:
		void open();
		void exit();
		void playPause();

		void sliderPressed();
		void sliderReleased();

		void sliderChanged(int sliderIndex);
		void frameChanged(I8u frameIndex);
		void durationFramesChanged(I8u durationFrames);

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

		QSlider * positionSlider;
		
		Media::Player::Control * mediaControl;
		Media::FFMPEGqtPlayer player;

};


#endif
