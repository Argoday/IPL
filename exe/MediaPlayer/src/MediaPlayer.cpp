
#include "MediaPlayer.h"

#include <QtGui>

#include <Image/Image.h>
#include <Image/Image_Qt.h>
#include <Video/Widget.h>
#include <Video/WidgetSurface.h>


MediaPlayer::MediaPlayer(Data::DataManager * const _dataManager,Media::Player::Control * const _mediaControl,Video::Queue::ReaderAgent * const readerAgent)
	:dataManager(_dataManager)
	,mediaControl(_mediaControl)
{
	Video::Widget * videoWidget = new Video::Widget();
	surface = videoWidget->videoSurface();

	readerAgent->registerVideoSurface(surface);

	createActions();
	createMenus();

	setCentralWidget(videoWidget);

	setWindowTitle(tr("Media Player"));
	resize(600, 600);
}

MediaPlayer::~MediaPlayer(){
}

void MediaPlayer::open(){
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
	if(fileName.isEmpty()==true){return;}
	mediaControl->open(fileName.toStdString(),true);
}

void MediaPlayer::exit(){
	mediaControl->quit();
	emit close();
}

void MediaPlayer::createActions(){
	openAct = new QAction(tr("&Open"), this);
	openAct->setShortcut(tr("Ctrl+O"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));

}

void MediaPlayer::createMenus(){
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addAction(exitAct);

	menuBar()->addMenu(fileMenu);
}

