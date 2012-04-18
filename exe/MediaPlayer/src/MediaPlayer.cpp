
#include "MediaPlayer.h"

#include <QtGui>

#include <Image/Image.h>
#include <Image/Image_Qt.h>
#include <Video/FFMPEGplayer.h>


MediaPlayer::MediaPlayer(Data::DataManager * const _dataManager)
	:dataManager(_dataManager)
{
	imageLabel = new QLabel;
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(false);

	setCentralWidget(imageLabel);

	createActions();
	createMenus();

	setWindowTitle(tr("Media Player"));
	resize(603, 625);
}

MediaPlayer::~MediaPlayer(){
	imageLabel = nullptr;
}

void MediaPlayer::open(){

	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
	if(fileName.isEmpty()==true){return;}

	//wImage = new Image::Image<PixelType>(Image::IO::read<PixelType>(dataManager,fileName.toStdString()));

	//imageLabel->setPixmap(QPixmap::fromImage(Image::Convert::toQt(*wImage)));

	//resize(wImage->getWidth()+3, wImage->getHeight()+25);
}

void MediaPlayer::exit(){
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

