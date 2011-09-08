
#ifndef FILTER__SimpleWxHdataOperation_H
#define FILTER__SimpleWxHdataOperation_H

#include <AIL.h>
#include <Image/Image.h>
#include <Filter/ImageOperation.h>

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT SimpleWxHdataOperation
	: public ImageOperation<PixelType>
{
	protected:
		Image::Image<PixelType> filterData;
		long xOffset;
		long yOffset;

	public:

		__forceinline const Image::Image<PixelType> &getFilterData() const {return filterData;}

		__forceinline const long &getXoffset() const {return xOffset;}
		__forceinline const long &getYoffset() const {return yOffset;}

		__forceinline void setXoffset(const long &_xOffset){xOffset=_xOffset;}
		__forceinline void setYoffset(const long &_yOffset){yOffset=_yOffset;}

		__forceinline PixelType &operator()(const long &x,const long &y){return filterData(x,y);};
		__forceinline const PixelType &operator()(const long &x,const long &y) const {return filterData(x,y);};

		virtual void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const = 0 ;

		virtual ~SimpleWxHdataOperation(){}

	protected:
		SimpleWxHdataOperation(Image::Image<PixelType> &&_filterData)
			:filterData(Meta::forward(_filterData))
			,xOffset((filterData.getWidth()-1)/2)
			,yOffset((filterData.getHeight()-1)/2)
		{
		};

};

}

#endif
