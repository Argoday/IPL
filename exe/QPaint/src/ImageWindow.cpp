
#include "ImageWindow.h"
#include "MorphologicalDialog.h"

#include <QtGui>
#include <QPainter>
#include <time.h>

#include <String/AString.h>
using String::getString;
#include <Image/Image.h>
#include <Image/Image_IO.h>
#include <Image/Image_Qt.h>
#include <Filter/DilateFilter.h>
#include <Filter/LinearFilterWxH.h>
#include <Algorithm/BaseAlgorithm1x1.h>
#include <Algorithm/BaseAlgorithm3x3.h>


//--- ImageWindow Constructor ---												//Constructor
ImageWindow::ImageWindow(Data::DataManager * const _dataManager)
	:dataManager(_dataManager)
{
	imageLabel = new QLabel;
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(true);

	scrollArea = new QScrollArea;
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(imageLabel);
	setCentralWidget(scrollArea);

	wImage = nullptr;

	createActions();
	createMenus();

	setWindowTitle(tr("Image Viewer"));
	resize(600, 600);
}

ImageWindow::~ImageWindow(){
	if (wImage != nullptr){delete wImage; wImage = nullptr;}
}

// --- Blur ---																//Blur
void ImageWindow::blur(){
	if(wImage==nullptr){return;}
	//blurFilter.makeGaussianFilter(5,3);

	/*blurFilter(0,0) = -1; blurFilter(0,1) = -1; blurFilter(0,2) = -1;
	blurFilter(1,0) = -1; blurFilter(1,1) =  8; blurFilter(1,2) = -1;
	blurFilter(2,0) = -1; blurFilter(2,1) = -1; blurFilter(2,2) = -1;*/

	/*Image::WMaxFilter<PixelType> maxFilter(3,3);
	maxFilter(0,2) = 0; maxFilter(1,2) = 0; maxFilter(2,2) = 0;
	maxFilter(0,1) = 0; maxFilter(1,1) = 1; maxFilter(2,1) = 1;
	maxFilter(0,0) = 0; maxFilter(1,0) = 1; maxFilter(2,0) = 1;
	maxFilter.resetTotalColor();
	wImage = maxFilter.applyToCopy(*wImage);//*/

	/*Image::Image<Image::WPixelYd> *tempImage = new Image::Image<Image::WPixelYd>(wImage->getImageSize());
	clock_t totalTimeDiff=0.0;
	double totalRuns = 50.0;
	for(int i=0;i<totalRuns;++i){
		clock_t startTime = clock();
		tempImage->setAs_pixel_cast(*wImage);
		wImage->setAs_pixel_cast(*tempImage);
		clock_t endTime = clock();
		totalTimeDiff += endTime-startTime;
	}
	delete tempImage;//*/

	Filter::DilateFilter<PixelType> blurFilter(13);
	//Image::WLinearFilter2D<PixelType> blurFilter(13,13);
	/*blurFilter(0,0) = 1;
	blurFilter(1,0) = 2;
	blurFilter(2,0) = 1;
	/*blurFilter(0,0) = 1; blurFilter(0,1) = 2; blurFilter(0,2) = 1;
	blurFilter(1,0) = 2; blurFilter(1,1) = 4; blurFilter(1,2) = 2;
	blurFilter(2,0) = 1; blurFilter(2,1) = 2; blurFilter(2,2) = 1;//*/
	//blurFilter.makeGaussianFilter(5.0,2.0);
	//blurFilter.resetTotalColor();

	Image::Image<PixelType> *tempImage = new Image::Image<PixelType>(*wImage);
	clock_t totalTimeDiff=0.0;
	double totalRuns = 1.0;
	for(int i=0;i<1;++i){
		clock_t startTime = clock();
		blurFilter.applyTo(*wImage,*tempImage);
		clock_t endTime = clock();
		totalTimeDiff += endTime-startTime;
	}
	delete wImage;
	wImage=tempImage;
	tempImage=nullptr;
	//wImage=tempImage;//*/
	std::string diffTime = getString(totalTimeDiff/totalRuns);
	QMessageBox::about(this, tr(("Time (cycles), "+getString(totalRuns)+" runs").c_str()),
		tr(diffTime.c_str())
	);
	
	imageLabel->setPixmap(QPixmap::fromImage(Image::Convert::toQt(*wImage)));
}

class NegateObj {
	public:
		typedef ImageWindow::PixelType::DataType PixelDataType;

		static __forceinline void process(PixelDataType * const & srcImageDataPtr){
			(*srcImageDataPtr) = 1.0 - (*srcImageDataPtr);
		}
		//static __forceinline void process(const PixelDataType * const & srcImageDataPtr,PixelDataType * const & dstImageDataPtr){
		//	(*dstImageDataPtr) = 1.0 - (*srcImageDataPtr);
		//}
		static __forceinline void process(PixelDataType * const & dstImageDataPtr,const PixelDataType * const & srcImageDataPtr){
			(*dstImageDataPtr) = 1.0 - (*srcImageDataPtr);
		}
		/*static __forceinline void process(PixelDataType *dstPixelPtr,const PixelDataType *srcPixelPtr02,const PixelDataType *srcPixelPtr12,const PixelDataType *srcPixelPtr22,
																	 const PixelDataType *srcPixelPtr01,const PixelDataType *srcPixelPtr11,const PixelDataType *srcPixelPtr21,
																	 const PixelDataType *srcPixelPtr00,const PixelDataType *srcPixelPtr10,const PixelDataType *srcPixelPtr20){
			(*dstPixelPtr) = (((*srcPixelPtr21) - (*srcPixelPtr01)) / 2) + 0.5;
		}//*/
		static __forceinline void process(PixelDataType *dstPixelPtr,const PixelDataType *srcPixelPtr02,const PixelDataType *srcPixelPtr12,const PixelDataType *srcPixelPtr22,
																	 const PixelDataType *srcPixelPtr01,const PixelDataType *srcPixelPtr11,const PixelDataType *srcPixelPtr21,
																	 const PixelDataType *srcPixelPtr00,const PixelDataType *srcPixelPtr10,const PixelDataType *srcPixelPtr20){
			PixelDataType Gx = (((*srcPixelPtr01)*2) + (*srcPixelPtr02) + (*srcPixelPtr00) - (((*srcPixelPtr21)*2) + (*srcPixelPtr22) + (*srcPixelPtr20)));
			PixelDataType Gy = (((*srcPixelPtr12)*2) + (*srcPixelPtr02) + (*srcPixelPtr22) - (((*srcPixelPtr10)*2) + (*srcPixelPtr00) + (*srcPixelPtr20)));
			(*dstPixelPtr).get<0>() = sqrt((Gx.get<0>()*Gx.get<0>()+Gy.get<0>()*Gy.get<0>()) / 32);
			(*dstPixelPtr).get<1>() = sqrt((Gx.get<1>()*Gx.get<1>()+Gy.get<1>()*Gy.get<1>()) / 32);
			(*dstPixelPtr).get<2>() = sqrt((Gx.get<2>()*Gx.get<2>()+Gy.get<2>()*Gy.get<2>()) / 32);
		}//*/
		/*static __forceinline void process(PixelDataType *dstPixelPtr,const PixelDataType *srcPixelPtr02,const PixelDataType *srcPixelPtr12,const PixelDataType *srcPixelPtr22,
																	 const PixelDataType *srcPixelPtr01,const PixelDataType *srcPixelPtr11,const PixelDataType *srcPixelPtr21,
																	 const PixelDataType *srcPixelPtr00,const PixelDataType *srcPixelPtr10,const PixelDataType *srcPixelPtr20){
			PixelDataType Gx = (((*srcPixelPtr01)*2) + (*srcPixelPtr02) + (*srcPixelPtr00) - (((*srcPixelPtr21)*2) + (*srcPixelPtr22) + (*srcPixelPtr20)));
			PixelDataType Gy = (((*srcPixelPtr12)*2) + (*srcPixelPtr02) + (*srcPixelPtr22) - (((*srcPixelPtr10)*2) + (*srcPixelPtr00) + (*srcPixelPtr20)));
			(*dstPixelPtr).get<0>() = (sqrt(Gx.get<0>()*Gx.get<0>()+Gy.get<0>()*Gy.get<0>())) / 5.6568542494923;
			(*dstPixelPtr).get<1>() = (sqrt(Gx.get<1>()*Gx.get<1>()+Gy.get<1>()*Gy.get<1>())) / 5.6568542494923;
			(*dstPixelPtr).get<2>() = (sqrt(Gx.get<2>()*Gx.get<2>()+Gy.get<2>()*Gy.get<2>())) / 5.6568542494923;
		}//*/
		/*static __forceinline void process(PixelDataType *dstPixelPtr,const PixelDataType *srcPixelPtr02,const PixelDataType *srcPixelPtr12,const PixelDataType *srcPixelPtr22,
																	 const PixelDataType *srcPixelPtr01,const PixelDataType *srcPixelPtr11,const PixelDataType *srcPixelPtr21,
																	 const PixelDataType *srcPixelPtr00,const PixelDataType *srcPixelPtr10,const PixelDataType *srcPixelPtr20){
			(*dstPixelPtr) = (((*srcPixelPtr01)*2) + (*srcPixelPtr02) + (*srcPixelPtr00) - (((*srcPixelPtr21)*2) + (*srcPixelPtr22) + (*srcPixelPtr20))) / 8 + 0.5;
		}//*/
		/*AlgorithmType::process(dstImageDataPtr,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidthp1,
										   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
										   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              );//*/
};

// --- Negative ---															// Negative
void ImageWindow::negative(){
	if(wImage==nullptr){return;}
	/*Image::WImage<PixelType> *fImage = Image::WImage<>::CreateImage(*wImage);
	Image::Morph<PixelType>::erode3x3(*wImage,*fImage);
	delete wImage;
	wImage=fImage;
	fImage=nullptr;*/
	clock_t startTime = clock();
	//(*wImage)*= -1.0;
	//(*wImage)+=  1.0;
	//Image::BaseAlgorithm1x1<Image::ImageBase::DefaultPixelType::DataType,NegateObj>(wImage->getView());

	Image::Image<PixelType> tempImage1 = Image::Image<PixelType>(wImage->getSize(),dataManager);
	Algorithm::BaseAlgorithm3x3<NegateObj,ImageWindow::PixelType::DataType>(wImage->getDataView(),tempImage1.getDataView());
	//Algorithm::BaseAlgorithm1x1<NegateObj,Image::ImageBase::DefaultPixelType::DataType>(wImage->getDataView(),tempImage1.getDataView());
	//Algorithm::BaseAlgorithm1x1<NegateObj,Image::ImageBase::DefaultPixelType::DataType>(wImage->getDataView());
	wImage->swap(tempImage1);
	//wImage->clip();
	//(*wImage)+= wImage->getMaxValueVol();
	clock_t endTime = clock();
	std::string diffTime = getString(endTime-startTime);

	QMessageBox::about(this, tr("Time (cycles)"),
		tr(diffTime.c_str())
	);
	imageLabel->setPixmap(QPixmap::fromImage(Image::Convert::toQt(*wImage)));
}
// --- MorphologicalDialog ---														//MorphologicalDialog
void ImageWindow::openMorphologicalDialog(){
	if(wImage==nullptr){return;}

	MorphologicalDialog dialog(dataManager,wImage);
	if(dialog.exec()){
		switch(dialog.operatorChoice){
			/*case 0: Image::dilate(wImage);    break;
			case 1:	Image::erode(wImage);     break;
			case 2:	Image::open(wImage);      break;
			case 3:	Image::close(wImage);     break;
			case 4:	Image::topHat(wImage);    break;
			case 5:	Image::bottomHat(wImage); break;//*/
			default:                          break;
		}	

		//imageLabel->setPixmap(QPixmap::fromImage(wImage->castAsQImage()));
	}

}

// --- Open Command ---														// Open File
void ImageWindow::open(){

	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
	if(fileName.isEmpty()==true){return;}

	wImage = new Image::Image<PixelType>(Image::IO::read<PixelType>(dataManager,fileName.toStdString()));

	imageLabel->setPixmap(QPixmap::fromImage(Image::Convert::toQt(*wImage)));

	scaleFactor = 1.0;

	fitToWindowAct->setEnabled(true);
	saveAct       ->setEnabled(true);
	printAct      ->setEnabled(true);

	negativeAct   ->setEnabled(true);
	blurAct       ->setEnabled(true);
	morphologicalDialogAct->setEnabled(true);

	updateActions();

	if(fitToWindowAct->isChecked()==false){imageLabel->adjustSize();}
	scrollArea->resize(wImage->getWidth()*20, wImage->getHeight()*20);
	resize(wImage->getWidth()+3, wImage->getHeight()+25);

}

// --- Save Command ---
void ImageWindow::save(){

	QString filePathName = QFileDialog::getSaveFileName(this,tr("Save File"), QDir::currentPath(), tr("Images (*.png *.jpg *.bmp *.tiff)"));
	if (filePathName.isEmpty()==true) {return;}
	
	Image::IO::write(*wImage,filePathName.toStdString());
	
}

// --- Print Command ---
void ImageWindow::print(){
	QPrintDialog printDialog(&printer, this);
	if (printDialog.exec()){
		QPainter painter(&printer);
		QRect rect = painter.viewport();

		QSize size = imageLabel->size();
		size.scale(rect.size(), Qt::KeepAspectRatio);
		painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
		painter.setWindow(imageLabel->pixmap()->rect());

		painter.drawPixmap(0,0,*imageLabel->pixmap());
	}
}

// --- Zooms ---															//Zooms
void ImageWindow::zoomIn(){scaleImage(1.25);}
void ImageWindow::zoomOut(){scaleImage(0.8);}

// Scale Image																// Scale Image
void ImageWindow::scaleImage(double factor){
	Q_ASSERT(imageLabel->pixmap());
	scaleFactor *= factor;
	imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

	adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
	adjustScrollBar(scrollArea->verticalScrollBar(), factor);

	zoomInAct->setEnabled(scaleFactor < 5.0);
	zoomOutAct->setEnabled(scaleFactor > 0.2);
}

// --- Normal Size ---
void ImageWindow::normalSize(){
	imageLabel->adjustSize();
	scaleFactor = 1.0;
}

// --- Exit ---
void ImageWindow::exit(){
	emit close();
}

// --- Fit to Window ---
 void ImageWindow::fitToWindow(){
	bool fitToWindow = fitToWindowAct->isChecked();
	scrollArea->setWidgetResizable(fitToWindow);
	if (fitToWindow==false) {normalSize();}
	updateActions();
}

// --- About ---
void ImageWindow::about(){
	QMessageBox::about(this, tr("About Image Viewer"),
			tr("<p>I am Blurb!</p>"));
}

// --- Actions ---
void ImageWindow::createActions(){
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	printAct = new QAction(tr("&Print"), this);
	printAct->setShortcut(tr("Ctrl+P"));
	printAct->setEnabled(false);
	connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcut(tr("Ctrl+S"));
	saveAct->setEnabled(false);
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));

	zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
	zoomInAct->setShortcut(tr("Ctrl++"));
	zoomInAct->setEnabled(false);
	connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

	zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
	zoomOutAct->setShortcut(tr("Ctrl+-"));
	zoomOutAct->setEnabled(false);
	connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

	normalSizeAct = new QAction(tr("&Normal Size"), this);
	normalSizeAct->setShortcut(tr("Ctrl+S"));
	normalSizeAct->setEnabled(false);
	connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

	fitToWindowAct = new QAction(tr("&Fit to Window"), this);
	fitToWindowAct->setEnabled(false);
	fitToWindowAct->setCheckable(true);
	connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	negativeAct = new QAction(tr("Ne&gative"), this);
	negativeAct->setEnabled(false);
	connect(negativeAct, SIGNAL(triggered()), this, SLOT(negative()));

	blurAct = new QAction(tr("&Blur"), this);
	blurAct->setEnabled(false);
	connect(blurAct, SIGNAL(triggered()), this, SLOT(blur()));
	
	morphologicalDialogAct = new QAction(tr("&Morphological Operator"), this);
	morphologicalDialogAct->setEnabled(false);
	connect(morphologicalDialogAct, SIGNAL(triggered()), this, SLOT(openMorphologicalDialog()));

	undoAct = new QAction(tr("&Undo"), this);
	undoAct->setShortcut(tr("Ctrl+Z"));
	undoAct->setEnabled(false);

	redoAct = new QAction(tr("&Redo"), this);
	redoAct->setShortcut(tr("Ctrl+A"));
	redoAct->setEnabled(false);

	cutAct = new QAction(tr("Cu&t"), this);
	cutAct->setShortcut(tr("Ctrl+X"));
	cutAct->setEnabled(false);

	copyAct = new QAction(tr("&Copy"), this);
	copyAct->setShortcut(tr("Ctrl+C"));
	copyAct->setEnabled(false);

	pasteAct = new QAction(tr("&Paste"), this);
	pasteAct->setShortcut(tr("Ctrl+V"));
	pasteAct->setEnabled(false);

}


// --- Menus ---
void ImageWindow::createMenus(){
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addSeparator();
	fileMenu->addAction(printAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	editMenu = new QMenu(tr("&Edit"),this);
	editMenu->addAction(undoAct);
	editMenu->addAction(redoAct);
	editMenu->addSeparator();
	editMenu->addAction(cutAct);
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);

	toolsMenu = new QMenu(tr("&Tools"),this);

	effectsMenu = new QMenu(tr("Effects"), this);
	effectsMenu->addAction(negativeAct);
	effectsMenu->addAction(blurAct);
	effectsMenu->addSeparator();
	effectsMenu->addAction(morphologicalDialogAct);

	zoomMenu = new QMenu(tr("&Zoom"), this);
	zoomMenu->addAction(zoomInAct);
	zoomMenu->addAction(zoomOutAct);
	zoomMenu->addAction(normalSizeAct);
	zoomMenu->addSeparator();
	zoomMenu->addAction(fitToWindowAct);

	modeMenu = new QMenu(tr("&Mode"),this);

	helpMenu = new QMenu(tr("&Help"), this);
	helpMenu->addAction(aboutAct);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(editMenu);
	menuBar()->addMenu(toolsMenu);
	menuBar()->addMenu(effectsMenu);
	menuBar()->addMenu(zoomMenu);
	menuBar()->addMenu(modeMenu);
	menuBar()->addMenu(helpMenu);
}

// --- Update Actions ---													//Update Actions
void ImageWindow::updateActions(){
	zoomInAct->setEnabled(!fitToWindowAct->isChecked());
	zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
	normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

// --- Adjust Scroll Bar ---												//Adjust Scroll Bar
void ImageWindow::adjustScrollBar(QScrollBar *scrollBar, double factor){
	scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}


