
#ifndef FILTER__SimpleWxHbooleanOperation_H
#define FILTER__SimpleWxHbooleanOperation_H

#include <Image/Image.h>
#include <Image/ImageKernel.h>
#include <Filter/ImageOperation.h>
#include <Meta/Boolean.h>

namespace Filter {

template <
	typename PixelType = Image::ImageBase::DefaultPixelType
> class SimpleWxHbooleanOperation
	: public ImageOperation<PixelType>
{
	protected:
		typedef Image::ImageKernel<Pixel::PixelYb,Pixel::BooleanTestType> FilterDataType;
		mutable FilterDataType filterData;
		I4 xOffset;
		I4 yOffset;

	public:

		__forceinline const FilterDataType & getFilterData() const {return filterData;}

		__forceinline const I4 & getXoffset() const {return xOffset;}
		__forceinline const I4 & getYoffset() const {return yOffset;}

		__forceinline void setXoffset(const I4 & _xOffset){xOffset=_xOffset;}
		__forceinline void setYoffset(const I4 & _yOffset){yOffset=_yOffset;}

		__forceinline       bool & operator()(const I4 &x,const I4 &y)       {return filterData(x,y);};
		__forceinline const bool & operator()(const I4 &x,const I4 &y) const {return filterData(x,y);};

		virtual void applyTo(const Image::Image<PixelType> & srcImage,Image::Image<PixelType> & dstImage) const = 0 ;

	protected:
		SimpleWxHbooleanOperation(Image::Image<Pixel::PixelYb> && _filterData)
			:filterData(Meta::forward(_filterData))
			,xOffset((filterData.getKernel().getWidth()-1)/2)
			,yOffset((filterData.getKernel().getHeight()-1)/2)
		{
		};

		void createFilterSkipData(const I4 & imageWidth);

};

}

#endif
