
#ifndef FILTER__SimpleWxHdataOperation_H
#define FILTER__SimpleWxHdataOperation_H

#include "AIL.h"
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
		I4 xOffset;
		I4 yOffset;

	public:

		FINLINE const Image::Image<PixelType> &getFilterData() const {return filterData;}

		FINLINE const I4 & getXoffset() const {return xOffset;}
		FINLINE const I4 & getYoffset() const {return yOffset;}

		FINLINE void setXoffset(const I4 & _xOffset){xOffset=_xOffset;}
		FINLINE void setYoffset(const I4 & _yOffset){yOffset=_yOffset;}

		FINLINE       PixelType & operator()(const I4 & x,const I4 & y)       {return filterData(x,y);};
		FINLINE const PixelType & operator()(const I4 & x,const I4 & y) const {return filterData(x,y);};

		virtual void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const = 0 ;

		virtual ~SimpleWxHdataOperation(){}

	protected:
		SimpleWxHdataOperation(Image::Image<PixelType> && _filterData)
			:filterData(Meta::forward(_filterData))
			,xOffset((filterData.getWidth()-1)/2)
			,yOffset((filterData.getHeight()-1)/2)
		{
		};

};

}

#endif
