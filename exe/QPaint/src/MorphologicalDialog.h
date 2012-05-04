
#ifndef QPAINT__MORPHOLOGICAL_DIALOG
#define QPAINT__MORPHOLOGICAL_DIALOG

#include <QDialog>

class QRadioButton;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QButtonGroup;
class QGroupBox;
class QSlider;

#include <Image/Image.h>
#include <Filter/MorphKernelType.h>
#include <Data/DataManager.h>

class MorphologicalDialog : public QDialog {
	Q_OBJECT

	public:
		typedef Pixel::PixelRGBi1u PixelType;

		MorphologicalDialog(Data::DataManager * const _dataManager,const Image::Image<PixelType> *inputImage,QWidget *parent = nullptr);
		~MorphologicalDialog();

		int size;
		int operatorChoice;
		Filter::MorphKernelType kernelType;

		QSpinBox * sizeSpinBox;

	//signals:
	//	void applyOperator();

	private slots:

		void updatePreview();
		void updateSize(int _size);
	//	void applyOperator();

	private:

		QLabel * instructions;
		QLabel * operationDescription;
		
		QLabel * previewBeforeTitle;
		QLabel * previewAfterTitle;

		QLabel * previewBeforeImageLabel;
		QLabel * previewAfterImageLabel;

		QButtonGroup * operationButtonGroup;
		QGroupBox    * operationSelector;
		QRadioButton * dilateButton;
		QRadioButton * erodeButton;
		QRadioButton * openButton;
		QRadioButton * closeButton;
		QRadioButton * tophatButton;
		QRadioButton * bottomhatButton;
		QRadioButton * blurButton;
		QRadioButton * unmaskSharpButton;

		QButtonGroup * kernelButtonGroup;
		QGroupBox    * kernelSelector;
		QRadioButton * crossButton;
		QRadioButton * squareButton;
		QRadioButton * circleButton;
		QRadioButton * diamondButton;

		QLabel  * sizeLabel;
		QSlider * sizeSlider;

		QPushButton *applyButton;
		QPushButton *cancelButton;

		const Image::Image<PixelType> * const previewBeforeImage;
		Image::Image<PixelType> * previewAfterImage;
		Data::DataManager * dataManager;

		long lastSize;

};

#endif
