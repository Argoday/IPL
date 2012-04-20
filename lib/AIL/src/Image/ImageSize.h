
#ifndef IMAGE__ImageSize_H
#define IMAGE__ImageSize_H

#include "AIL.h"
#include "Data/DataTypes.h"

namespace Image {

class AIL_DLL_EXPORT ImageSize {

	public:
		ImageSize(const I4 & _width,const I4 & _height);

		typedef ImageSize ThisType;

		__forceinline const I4 & getWidth()    const {return width   ;}
		__forceinline const I4 & getWidth_1()  const {return width_1 ;}

		__forceinline const I4 & getHeight()   const {return height   ;}
		__forceinline const I4 & getHeight_1() const {return height_1 ;}
		
		__forceinline const I4 & getNumPixels() const {return numPixels;}

		friend __forceinline bool operator<(const ThisType &other1, const ThisType &other2){
			return (other1.getNumPixels() < other2.getNumPixels());
		}
		friend __forceinline bool operator!=(const ThisType &other1, const ThisType &other2){
			return (other1.getWidth()!=other2.getWidth())||(other1.getHeight()!=other2.getHeight());
		}
		friend __forceinline bool operator==(const ThisType &other1, const ThisType &other2){
			return (other1.getWidth()==other2.getWidth())&&(other1.getHeight()==other2.getHeight());
		}

	private:
		I4 width;
		I4 width_1;

		I4 height;
		I4 height_1;

		I4 numPixels;
};

}

#endif

