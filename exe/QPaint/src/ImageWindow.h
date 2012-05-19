
#ifndef ImageWindow_H
#define ImageWindow_H

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
		ImageWindow(Data::DataManager * const _dataManager);
		~ImageWindow();

		typedef Pixel::PixelRGBi1u PixelType;

	private slots:
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
		void adjustScrollBar(QScrollBar * scrollBar, double factor);

		QPrinter printer;
		QImageWriter imageWriter;
		QLabel * imageLabel;
		QScrollArea *scrollArea;
		double scaleFactor;

	//File
		QAction *openAct;
		QAction *saveAct;
		QAction *printAct;
		QAction *exitAct;
		QAction *aboutAct;

	//Edit
		QAction *undoAct;
		QAction *redoAct;
		QAction *cutAct;
		QAction *copyAct;
		QAction *pasteAct;

	//Zoom
		QAction *zoomInAct;
		QAction *zoomOutAct;
		QAction *normalSizeAct;
		QAction *fitToWindowAct;

	//Image Actions
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
	
		Image::Image<PixelType> * wImage;
		Data::DataManager * dataManager;

};


#endif
