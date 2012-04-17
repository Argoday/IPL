
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
		long xOffset;
		long yOffset;

	public:

		__forceinline const FilterDataType & getFilterData() const {return filterData;}

		__forceinline const long &getXoffset() const {return xOffset;}
		__forceinline const long &getYoffset() const {return yOffset;}

		__forceinline void setXoffset(const long &_xOffset){xOffset=_xOffset;}
		__forceinline void setYoffset(const long &_yOffset){yOffset=_yOffset;}

		__forceinline bool &operator()(const long &x,const long &y){return filterData(x,y);};
		__forceinline const bool &operator()(const long &x,const long &y) const {return filterData(x,y);};

		virtual void applyTo(const Image::Image<PixelType> &srcImage,Image::Image<PixelType> &dstImage) const = 0 ;

	protected:
		SimpleWxHbooleanOperation(Image::Image<Pixel::PixelYb> &&_filterData)
			:filterData(Meta::forward(_filterData))
			,xOffset((filterData.getKernel().getWidth()-1)/2)
			,yOffset((filterData.getKernel().getHeight()-1)/2)
		{
		};

		void createFilterSkipData(const long &imageWidth);

};

}

#endif
