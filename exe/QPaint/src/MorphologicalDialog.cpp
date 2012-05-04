
#include <QtGui>

#include "MorphologicalDialog.h"
#include <Image/Image.h>
#include <Image/Image_Qt.h>
#include <Image/image_cast.h>

#include <Filter/DilateFilter.h>
#include <Filter/ErodeFilter.h>
#include <Filter/BlackTopHatFilter.h>
#include <Filter/WhiteTopHatFilter.h>
#include <Filter/OpenFilter.h>
#include <Filter/CloseFilter.h>
#include <Filter/LinearFilterWxH.h>
#include <Filter/LinearFilterWx1.h>
#include <Filter/LinearFilter1xH.h>
#include <Filter/BoxFilterWx1.h>
#include <Filter/BoxFilter1xH.h>
#include <Paint/Gaussian.h>

void MorphologicalDialog::updateSize(int _size) {
	if(size!=_size){
		size = _size;
		updatePreview();
	}
}
void MorphologicalDialog::updatePreview() {

	int tempOperatorChoice=-1;
	if(dilateButton     ->isChecked()==true){tempOperatorChoice=0;}
	if(erodeButton      ->isChecked()==true){tempOperatorChoice=1;}
	if(openButton       ->isChecked()==true){tempOperatorChoice=2;}
	if(closeButton      ->isChecked()==true){tempOperatorChoice=3;}
	if(tophatButton     ->isChecked()==true){tempOperatorChoice=4;}
	if(bottomhatButton  ->isChecked()==true){tempOperatorChoice=5;}
	if(blurButton       ->isChecked()==true){tempOperatorChoice=6;}
	if(unmaskSharpButton->isChecked()==true){tempOperatorChoice=7;}
	if(tempOperatorChoice==-1){return;}

	int tempSize = size;

	Filter::MorphKernelType tempKernelType = Filter::MorphKernelType::none;
	if(crossButton    ->isChecked()==true){tempKernelType = Filter::MorphKernelType::cross  ;tempSize=tempSize*2+1;}
	if(squareButton   ->isChecked()==true){tempKernelType = Filter::MorphKernelType::square ;tempSize=tempSize*2+1;}
	if(circleButton   ->isChecked()==true){tempKernelType = Filter::MorphKernelType::circle ;tempSize=tempSize*2+1;}
	if(diamondButton  ->isChecked()==true){tempKernelType = Filter::MorphKernelType::diamond;}
	if(tempKernelType==Filter::MorphKernelType::none){return;}

	if((operatorChoice==tempOperatorChoice)&&(kernelType==tempKernelType)&&(lastSize==size)){
		return;
	}
	operatorChoice=tempOperatorChoice;
	kernelType=tempKernelType;
	lastSize=size;

	switch(operatorChoice){
		case 0:
			{
				Filter::DilateFilter<PixelType>      dilateFilter(tempSize,kernelType);
				dilateFilter.applyTo(*previewBeforeImage,*previewAfterImage);
			}
		break;
		case 1:
			{
				Filter::ErodeFilter<PixelType>       erodeFilter(tempSize,kernelType);
				erodeFilter.applyTo(*previewBeforeImage,*previewAfterImage);
			}
		break;
		case 2:
			{
				Filter::OpenFilter<PixelType>        openFilter(tempSize,kernelType);
				openFilter.applyTo(*previewBeforeImage,*previewAfterImage);
			}
		break;
		case 3:
			{
				Filter::CloseFilter<PixelType>       closeFilter(tempSize,kernelType);
				closeFilter.applyTo(*previewBeforeImage,*previewAfterImage);
			}
		break;
		case 4:
			{
				Image::Image<PixelType> tempImage1 = Image::Image<PixelType>(previewAfterImage->getSize(),dataManager);

				Filter::BlackTopHatFilter<PixelType> blackTopHatFilter(tempSize,kernelType);
				blackTopHatFilter.applyTo(*previewBeforeImage,tempImage1);

				Filter::WhiteTopHatFilter<PixelType> whiteTopHatFilter(tempSize,kernelType);
				whiteTopHatFilter.applyTo(*previewBeforeImage,*previewAfterImage);

				(*previewAfterImage)+=tempImage1;
			}
		break;
		case 5:
			{
				Filter::WhiteTopHatFilter<PixelType> whiteTopHatFilter(tempSize,kernelType);
				whiteTopHatFilter.applyTo(*previewBeforeImage,*previewAfterImage);
			}
		break;
		case 6:
			{
				Filter::BoxFilterWx1<PixelType> boxFilter1(size*2+1);
				Filter::BoxFilter1xH<PixelType> boxFilter2(size*2+1);
				Image::Image<PixelType> tempImage1 = Image::Image<PixelType>(previewAfterImage->getSize(),dataManager);
				boxFilter1.applyTo(*previewBeforeImage,tempImage1);
				boxFilter2.applyTo(tempImage1,*previewAfterImage);
			}
		break;
		case 7:
			{
				Image::Image<PixelType::ComputationPixel> previewBeforeImageComp = Image::image_cast<PixelType::ComputationPixel>(*previewBeforeImage);
				Image::Image<PixelType::ComputationPixel> previewAfterImageComp  = Image::Image<PixelType::ComputationPixel>(previewAfterImage->getSize(),dataManager);
				
				Image::Image<PixelType::ComputationPixel> tempImage1 = Image::Image<PixelType::ComputationPixel>(previewAfterImage->getSize(),dataManager);
				Image::Image<PixelType::ComputationPixel> tempImage2 = Image::Image<PixelType::ComputationPixel>(previewAfterImage->getSize(),dataManager);
				Filter::BoxFilterWx1<PixelType::ComputationPixel> boxFilter1(size*2+1);
				Filter::BoxFilter1xH<PixelType::ComputationPixel> boxFilter2(size*2+1);
				boxFilter1.applyTo(previewBeforeImageComp,tempImage1);
				boxFilter2.applyTo(tempImage1,tempImage2);
				
				tempImage1=previewBeforeImageComp;
				tempImage1-=tempImage2;

				previewAfterImageComp=previewBeforeImageComp;
				previewAfterImageComp+=tempImage1;
				previewAfterImageComp.clip();

				(*previewAfterImage) = Image::image_cast<PixelType>(previewAfterImageComp);
			}
		break;
	}
	previewAfterImageLabel->setPixmap(QPixmap::fromImage(Image::Convert::toQt(*previewAfterImage)));
}
MorphologicalDialog::~MorphologicalDialog(){
	if(previewAfterImage !=nullptr){delete previewAfterImage ;previewAfterImage =nullptr;}
}
MorphologicalDialog::MorphologicalDialog(Data::DataManager * const _dataManager,const Image::Image<PixelType> *inputImage,QWidget *parent)
	:QDialog(parent)
	,kernelType(Filter::MorphKernelType::none)
	,dataManager(_dataManager)
	,previewBeforeImage(inputImage)
{
	size=0;
	lastSize=-1;
	operatorChoice=0;

	instructions = new QLabel(tr("Instructions..."));

	operationDescription = new QLabel(tr("Select an Operator..."));

	//--------------------------------------------------------
	previewAfterImage  = new Image::Image<PixelType>(inputImage->getSize(),dataManager);
	
	(*previewAfterImage)=(*previewBeforeImage);

	previewAfterTitle = new QLabel(tr("After:"));

	previewAfterImageLabel = new QLabel();
	previewAfterImageLabel->setBackgroundRole(QPalette::Base);
	previewAfterImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	previewAfterImageLabel->setScaledContents(true);
	previewAfterImageLabel->setPixmap(QPixmap::fromImage(Image::Convert::toQt(*previewAfterImage)));

	QVBoxLayout * previewLayout = new QVBoxLayout;
	previewLayout->addWidget(previewAfterTitle);
	previewLayout->addWidget(previewAfterImageLabel);
	previewLayout->addStretch();
	//--------------------------------------------------------

	//--------------------------------------------------------
	operationSelector = new QGroupBox(tr("Morphological Operator:"));
	dilateButton    = new QRadioButton(tr("&Dilate"));
	erodeButton     = new QRadioButton(tr("&Erode"));
	openButton      = new QRadioButton(tr("&Open"));
	closeButton     = new QRadioButton(tr("C&lose"));
	tophatButton    = new QRadioButton(tr("&Top Hat"));
	bottomhatButton = new QRadioButton(tr("&Bottom Hat"));
	blurButton      = new QRadioButton(tr("Bl&ur"));
	unmaskSharpButton= new QRadioButton(tr("Unmask &Sharpen"));
	
	QObject::connect(dilateButton   , SIGNAL(clicked()) , this,  SLOT(updatePreview()));
	QObject::connect(erodeButton    , SIGNAL(clicked()) , this,  SLOT(updatePreview()));
	QObject::connect(openButton     , SIGNAL(clicked()) , this,  SLOT(updatePreview()));
	QObject::connect(closeButton    , SIGNAL(clicked()) , this,  SLOT(updatePreview()));
	QObject::connect(tophatButton   , SIGNAL(clicked()) , this,  SLOT(updatePreview()));
	QObject::connect(bottomhatButton, SIGNAL(clicked()) , this,  SLOT(updatePreview()));
	QObject::connect(blurButton     , SIGNAL(clicked()) , this,  SLOT(updatePreview()));
	QObject::connect(unmaskSharpButton,SIGNAL(clicked()), this,  SLOT(updatePreview()));

	//dilateButton->setDefault(true);
	operatorChoice = 0;

	operationButtonGroup = new QButtonGroup;
	operationButtonGroup->addButton(dilateButton);
	operationButtonGroup->addButton(erodeButton);
	operationButtonGroup->addButton(openButton);
	operationButtonGroup->addButton(closeButton);
	operationButtonGroup->addButton(tophatButton);
	operationButtonGroup->addButton(bottomhatButton);
	operationButtonGroup->addButton(blurButton);
	operationButtonGroup->addButton(unmaskSharpButton);
	QObject::connect(operationButtonGroup, SIGNAL(buttonClicked()) , this,  SLOT(updatePreview()));
	
	QVBoxLayout *operationLayout = new QVBoxLayout;
	operationLayout->addWidget(dilateButton);
	operationLayout->addWidget(erodeButton);
	operationLayout->addWidget(openButton);
	operationLayout->addWidget(closeButton);
	operationLayout->addWidget(tophatButton);
	operationLayout->addWidget(bottomhatButton);
	operationLayout->addWidget(blurButton);
	operationLayout->addWidget(unmaskSharpButton);
	operationLayout->addStretch();
	operationSelector->setLayout(operationLayout);
	//--------------------------------------------------------

	//--------------------------------------------------------
	kernelSelector = new QGroupBox(tr("Kernel:"));
	crossButton    = new QRadioButton(tr("C&ross"));
	squareButton   = new QRadioButton(tr("&Square"));
	circleButton   = new QRadioButton(tr("&Circle"));
	diamondButton  = new QRadioButton(tr("&Diamond"));

	QObject::connect(crossButton   , SIGNAL(clicked()) , this,  SLOT(updatePreview()));
	QObject::connect(squareButton  , SIGNAL(clicked()) , this,  SLOT(updatePreview()));
	QObject::connect(circleButton  , SIGNAL(clicked()) , this,  SLOT(updatePreview()));
	QObject::connect(diamondButton , SIGNAL(clicked()) , this,  SLOT(updatePreview()));

	kernelButtonGroup = new QButtonGroup;
	kernelButtonGroup->addButton(crossButton  );
	kernelButtonGroup->addButton(squareButton );
	kernelButtonGroup->addButton(circleButton );
	kernelButtonGroup->addButton(diamondButton);
	QObject::connect(kernelButtonGroup, SIGNAL(buttonClicked()) , this,  SLOT(updatePreview()));
	
	QVBoxLayout * kernelLayout = new QVBoxLayout;
	kernelLayout->addWidget(crossButton  );
	kernelLayout->addWidget(squareButton );
	kernelLayout->addWidget(circleButton );
	kernelLayout->addWidget(diamondButton);
	kernelLayout->addStretch();
	kernelSelector->setLayout(kernelLayout);
	//--------------------------------------------------------

	QVBoxLayout * selectionPreviewLayout = new QVBoxLayout;
	selectionPreviewLayout->addWidget(operationSelector);
	selectionPreviewLayout->addWidget(kernelSelector);
	selectionPreviewLayout->addStretch();

	//--------------------------------------------------------
	QHBoxLayout * operationPreviewLayout = new QHBoxLayout;
	operationPreviewLayout->addLayout(selectionPreviewLayout);
	operationPreviewLayout->addStretch();
	operationPreviewLayout->addLayout(previewLayout);
	//--------------------------------------------------------

	//--------------------------------------------------------
	sizeLabel = new QLabel(tr("Size:"));
	sizeSpinBox = new QSpinBox;
	sizeSpinBox->setRange(1,50);
	sizeSlider = new QSlider(Qt::Horizontal);
	sizeSlider->setRange(1,50);
	QObject::connect(sizeSpinBox, SIGNAL(valueChanged(int)) , sizeSlider,  SLOT(setValue(int)));
	QObject::connect(sizeSlider,  SIGNAL(valueChanged(int)) , sizeSpinBox, SLOT(setValue(int)));
	QObject::connect(sizeSlider,  SIGNAL(valueChanged(int)) , this, SLOT(updateSize(int)));
	sizeSpinBox->setValue(3);
	
	QHBoxLayout * sizeLayout = new QHBoxLayout;
	sizeLayout->addWidget(sizeLabel);
	sizeLayout->addWidget(sizeSpinBox);
	sizeLayout->addWidget(sizeSlider);
	sizeLayout->addStretch();
	//--------------------------------------------------------

	//--------------------------------------------------------
	applyButton = new QPushButton(tr("&Apply"));
	applyButton->setDefault(false);
	applyButton->setEnabled(true);
	QObject::connect(applyButton, SIGNAL(clicked()) , this,  SLOT(accept()));
	
	cancelButton = new QPushButton(tr("&Cancel"));
	cancelButton->setDefault(true);
	cancelButton->setEnabled(true);
	QObject::connect(cancelButton, SIGNAL(clicked()) , this,  SLOT(reject()));

	QHBoxLayout * buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch();
	buttonLayout->addWidget(applyButton);
	buttonLayout->addWidget(cancelButton);
	//--------------------------------------------------------

	//--------------------------------------------------------
	QVBoxLayout * mainLayout = new QVBoxLayout;
	mainLayout->addWidget(instructions);
	mainLayout->addLayout(operationPreviewLayout);
	mainLayout->addLayout(sizeLayout);
	mainLayout->addWidget(operationDescription);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
	//--------------------------------------------------------
	
	setWindowTitle(tr("Apply a Morphological Operation"));
	
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());

}

