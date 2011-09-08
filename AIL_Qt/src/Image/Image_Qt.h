

#ifndef IMAGE__Convert_Qt_H
#define IMAGE__Convert_Qt_H

#include "AIL_QT.h"
#include <Image/Image.h>
#include <QImage.h>

namespace Data {
	class DataManager;
}

namespace Image {

namespace Convert {
	template<typename PixelType> AIL_QT_DLL_EXPORT QImage convertToQt (const Image<PixelType> &image);
	template<typename PixelType> AIL_QT_DLL_EXPORT Image<PixelType> convertFromQt(const QImage &image);
	template<typename PixelType> AIL_QT_DLL_EXPORT Image<PixelType> convertFromQt(const QImage &image,Data::DataManager * const dataManager);
}

}

#endif
