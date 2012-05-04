
#ifndef FILTER__SimpleWxHbooleanOperation_H
#define FILTER__SimpleWxHbooleanOperation_H

#include <Image/Image.h>
#include <Image/ImageKernel.h>
#include <Filter/ImageOperation.h>
#include <Meta/Boolean.h>

namespace Filter {

template <
	typename PixelType
> class AIL_DLL_EXPORT SimpleWxHbooleanOperation
	: public ImageOperation<PixelType>
{
	protected:
		typedef Image::ImageKernel<Pixel::PixelYb1,Pixel::BooleanTestType> FilterDataType;
		mutable FilterDataType filterData;
		I4 xOffset;
		I4 yOffset;

	public:

		FINLINE const FilterDataType & getFilterData() const {return filterData;}

		FINLINE const I4 & getXoffset() const {return xOffset;}
		FINLINE const I4 & getYoffset() const {return yOffset;}

		FINLINE void setXoffset(const I4 & _xOffset){xOffset=_xOffset;}
		FINLINE void setYoffset(const I4 & _yOffset){yOffset=_yOffset;}

		FINLINE       B1 & operator()(const I4 & x,const I4 & y)       {return filterData(x,y);};
		FINLINE const B1 & operator()(const I4 & x,const I4 & y) const {return filterData(x,y);};

		virtual void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const = 0 ;

	protected:
		SimpleWxHbooleanOperation(Image::Image<Pixel::PixelYb1> && _filterData)
			:filterData(Meta::forward(_filterData))
			,xOffset((filterData.getKernel().getWidth()-1)/2)
			,yOffset((filterData.getKernel().getHeight()-1)/2)
		{
		};

		void createFilterSkipData(const I4 & imageWidth);

};

}

#endif
