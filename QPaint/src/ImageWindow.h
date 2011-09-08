
#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QMainWindow>
#include <QPrinter>
#include <QImageWriter>
#include <Image/Image.h>
#include <Pixel/PixelRGB.h>
#include <Data/DataManager.h>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class ImageWindow : public QMainWindow {
	Q_OBJECT

	public:
		ImageWindow(Data::DataManager * const _dataManager);	// constructor
		~ImageWindow();	// destructor

	private slots:		// Commands
		void open();
		void print();
		void save();
		void zoomIn();
		void zoomOut();
		void normalSize();
		void fitToWindow();
		void about();
		void exit();

		void negative();
		void blur();

		void openMorphologicalDialog();

	private:
		void createActions();
		void createMenus();
		void updateActions();
		void scaleImage(double factor);
		void adjustScrollBar(QScrollBar *scrollBar, double factor);

	//Misc Declarations
		QPrinter printer;
		QImageWriter imageWriter;
		QLabel *imageLabel;
		QScrollArea *scrollArea;
		double scaleFactor;

	//File Actions
		QAction *openAct;
		QAction *saveAct;
		QAction *printAct;
		QAction *exitAct;
		QAction *aboutAct;

	//Edit Actions
		QAction *undoAct;
		QAction *redoAct;
		QAction *cutAct;
		QAction *copyAct;
		QAction *pasteAct;

	//Zoom Actions
		QAction *zoomInAct;
		QAction *zoomOutAct;
		QAction *normalSizeAct;
		QAction *fitToWindowAct;

	//Global Effect Image Actions
		QAction *negativeAct;
		QAction *blurAct;
		QAction *morphologicalDialogAct;

	//Menus
		QMenu *fileMenu;
		QMenu *editMenu;
		QMenu *toolsMenu;
		QMenu *effectsMenu;
		QMenu *zoomMenu;
		QMenu *modeMenu;
		QMenu *helpMenu;
	
		typedef Pixel::PixelRGBf8 PixelType;
		Image::Image<PixelType> * wImage;
		Data::DataManager * dataManager;

#ifdef PAINT_ENGINE__W_GUI_MANAGER_H
		PaintEngine::WGuiManager *wGuiManager;
#endif

};


#endif
