
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

	playPauseButton = new QPushButton;
	playPauseButton->setEnabled(false);
	playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	playPauseButton->setText("PlayPause");

	connect(playPauseButton, SIGNAL(clicked()),this, SLOT(playPause()));

	QSlider * positionSlider = new QSlider(Qt::Horizontal);
	positionSlider->setRange(0, 600);
	connect(positionSlider, SIGNAL(sliderMoved(int)),this, SLOT(setPosition(int)));

	connect(surface, SIGNAL(frameChanged(int)),positionSlider, SLOT(setValue(int)));

	QBoxLayout * controlLayout = new QHBoxLayout;
	controlLayout->addWidget(playPauseButton);
	controlLayout->addWidget(positionSlider);

	QBoxLayout * layout = new QVBoxLayout;
	layout->addWidget(videoWidget);
	layout->addLayout(controlLayout);

	createActions();
	createMenus();

	QWidget * window = new QWidget;
	window->setLayout(layout);
	setCentralWidget(window);

	setWindowTitle(tr("Media Player"));
	resize(600, 600);
	
}

MediaPlayer::~MediaPlayer(){
}
void MediaPlayer::setPosition(int frame){
}
void MediaPlayer::playPause(){
	mediaControl->playPause();
}
void MediaPlayer::open(){
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
	if(fileName.isEmpty()==true){return;}
	mediaControl->open(fileName.toStdString(),true);
	playPauseButton->setEnabled(true);
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

