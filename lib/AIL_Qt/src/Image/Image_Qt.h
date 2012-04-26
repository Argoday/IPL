

#ifndef IMAGE__Image_Qt_H
#define IMAGE__Image_Qt_H

#include "AIL_QT.h"
#include <Image/Image.h>
#include <QImage.h>

namespace Data {
	class DataManager;
}

namespace Image {

namespace Convert {
	template<typename PixelType> AIL_QT_DLL_EXPORT QImage toQt(const Image<PixelType> &image);
	template<typename PixelType> AIL_QT_DLL_EXPORT Image<PixelType> fromQt(Data::DataManager * const dataManager,const QImage &image);
}

namespace IO {
	AIL_QT_DLL_EXPORT QImage readQt(const std::string & fileName);
	AIL_QT_DLL_EXPORT void writeQt(const QImage & image,const std::string & fileName);

	template<typename PixelType> AIL_QT_DLL_EXPORT Image<PixelType> readQt(Data::DataManager * const dataManager,const std::string & fileName);
	template<typename PixelType> AIL_QT_DLL_EXPORT void writeQt(const Image<PixelType> & image,const std::string & fileName);

}

}

#endif
