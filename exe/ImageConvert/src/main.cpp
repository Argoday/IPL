
#include <String/AString.h>

#include <qcoreapplication.h>
#include <qtimer.h>
#include <qstringlist.h>

#include <sstream>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <vector>

#include <Image/Image_IO.h>

#include "MainObject.h"

int main(int argc, char *argv[]){

	QCoreApplication a(argc, argv);
 
	MainObject g;
	QTimer::singleShot(0, &g, SLOT(startApplication()));
 
	return a.exec();
}


void realMain(const QStringList &args,const QString & filePath){
	if((args.length()>4)||(args.length()<2)){
		return;
	}
	bool verbose=false;
	if(args.length()==4){
		if(args[3].toStdString()=="verbose"){
			verbose=true;
		}else{
			return;
		}
	}
	std::string fromFileName = args[1].toStdString();
	std::string toFileName   = args[2].toStdString();
	Image::Image<Pixel::PixelRGBf8> image = Image::IO::read<Pixel::PixelRGBf8>(nullptr,fromFileName);
	if(image.getHeight()==0){
		std::cout<<"Error Reading File - received image of zero height"<<std::endl;
	}else{
		Image::IO::write(image,toFileName);
	}
}
