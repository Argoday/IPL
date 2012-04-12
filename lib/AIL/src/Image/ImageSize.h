
#ifndef IMAGE__ImageSize_H
#define IMAGE__ImageSize_H

#include "AIL.h"

namespace Image {

class AIL_DLL_EXPORT ImageSize {

	public:
		ImageSize(const long &_width,const long &_height);

		typedef ImageSize ThisType;

		__forceinline const long &getWidth()    const {return width   ;}
		__forceinline const long &getWidth_1()  const {return width_1 ;}

		__forceinline const long &getHeight()   const {return height   ;}
		__forceinline const long &getHeight_1() const {return height_1 ;}
		
		__forceinline const long &getNumPixels() const {return numPixels;}

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
		long width;
		long width_1;

		long height;
		long height_1;

		long numPixels;
};

}

#endif

