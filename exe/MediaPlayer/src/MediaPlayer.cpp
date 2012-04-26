
#include "MediaPlayer.h"

#include <QtGui>

#include <Video/Widget.h>
#include <Video/WidgetSurface.h>
#include <Video/QueueQtTarget.h>

#include <Media/FFMPEGmediaPlayerAgent.h>
#include <Thread/QueuePipe.h>
#include <Thread/QueueReaderAgent.h>


class FFMPEGqtPlayer {
	public:
		FFMPEGqtPlayer(Data::DataManager * const _dataManager,QAbstractVideoSurface * surface)
			:dataManager(_dataManager)
		{
			videoPipe = new Thread::Queue::Pipe(60);
			audioPipe = new Thread::Queue::Pipe(6000);

			mediaControl = new Media::Player::Control(controlQueue);

			videoReaderAgent = new Thread::Queue::ReaderAgent(*videoPipe);
			qtTarget = new Video::Queue::QtTarget(surface);
			videoReaderAgent->registerTarget(qtTarget);

			mediaPlayerAgent = new Media::FFMPEGmediaPlayerAgent(dataManager,controlQueue,*videoPipe,*audioPipe);

			mediaPlayerAgent->start();
			videoReaderAgent->start();
		}
		Media::Player::Control * getMediaControl(){return mediaControl;}
		~FFMPEGqtPlayer(){
			mediaControl->quit();
			Concurrency::agent::wait(mediaPlayerAgent);
			Concurrency::agent::wait(videoReaderAgent);

			delete videoPipe;
			delete audioPipe;
			delete qtTarget;
			delete mediaControl;
			delete videoReaderAgent;
			delete mediaPlayerAgent;
		}
	private:
		Data::DataManager * const dataManager;

		Concurrency::unbounded_buffer<Media::Player::ControlPacket> controlQueue;
		Thread::Queue::Pipe * videoPipe;
		Thread::Queue::Pipe * audioPipe;
		Video::Queue::QtTarget * qtTarget;
		Media::Player::Control * mediaControl;
		Thread::Queue::ReaderAgent * videoReaderAgent;
		Media::FFMPEGmediaPlayerAgent * mediaPlayerAgent;

};

MediaPlayer::MediaPlayer(Data::DataManager * const _dataManager)
	:dataManager(_dataManager)
{
	auto videoWidget = new Video::Widget();
	auto surface = videoWidget->videoSurface();

	player = new FFMPEGqtPlayer(dataManager,surface);
	mediaControl = player->getMediaControl();

	playPauseButton = new QPushButton;
	playPauseButton->setEnabled(false);
	playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	playPauseButton->setText("PlayPause");

	connect(playPauseButton, SIGNAL(clicked()),this, SLOT(playPause()));

	auto positionSlider = new QSlider(Qt::Horizontal);
	positionSlider->setRange(0, 10000);
	connect(positionSlider, SIGNAL(sliderMoved(int)),this, SLOT(sliderChanged(int)));

	connect(surface, SIGNAL(frameChanged(I8u)),this, SLOT(frameChanged(I8u)));

	connect(this, SIGNAL(setSlider(int)),positionSlider, SLOT(setValue(int)));
	
	QBoxLayout * controlLayout = new QHBoxLayout;
	controlLayout->addWidget(playPauseButton);
	controlLayout->addWidget(positionSlider);

	QBoxLayout * layout = new QVBoxLayout;
	layout->addWidget(videoWidget);
	layout->addLayout(controlLayout);

	createActions();
	createMenus();

	auto window = new QWidget;
	window->setLayout(layout);
	setCentralWidget(window);

	setWindowTitle(tr("Media Player"));
	resize(600, 600);
	
}

MediaPlayer::~MediaPlayer(){
	delete player;
}
void MediaPlayer::sliderChanged(int sliderIndex){
	//seek
}
void MediaPlayer::frameChanged(I8u frameIndex){
	emit setSlider(frameIndex);
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

