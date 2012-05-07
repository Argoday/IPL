
#ifndef IMAGE__ImageView_H
#define IMAGE__ImageView_H

#include "AIL.h"
#include "ImageSize.h"
#include <vector>

namespace Image {

template <
	typename PixelDataType
> class AIL_DLL_EXPORT ImageView {
	public:

		typedef ImageView<PixelDataType> ThisType;

		ImageView(const ThisType & _view)
			:imageDataPtr(_view.imageDataPtr)
			,imageDataPtrEnd(_view.imageDataPtrEnd)
			,stride(_view.stride)
			,size(_view.size)
			,simpleView(_view.simpleView)
			,numPixelsBetweenRows(_view.numPixelsBetweenRows)
			,xBeginSection(_view.xBeginSection)
			,xEndSection(_view.xEndSection)
			,yBeginSection(_view.yBeginSection)
			,yEndSection(_view.yEndSection)
		{
		}

		const ImageView & operator=(const ThisType & _view){
			imageDataPtr=_view.imageDataPtr;
			imageDataPtrEnd=_view.imageDataPtrEnd;
			stride=_view.stride;
			size=_view.size;
			simpleView=_view.simpleView;
			numPixelsBetweenRows=_view.numPixelsBetweenRows;
			xBeginSection=_view.xBeginSection;
			xEndSection=_view.xEndSection;
			yBeginSection=_view.yBeginSection;
			yEndSection=_view.yEndSection;
			return (*this);
		}

		ImageView(		PixelDataType * const & _imageDataPtr,
				  const PixelDataType * const & _imageDataPtrEnd,
				  const ImageSize & _size
		)
			:imageDataPtr(_imageDataPtr)
			,imageDataPtrEnd(_imageDataPtrEnd)
			,stride(_size.getWidth())
			,size(_size)
			,simpleView(true)
			,numPixelsBetweenRows(0)
			,xBeginSection(true)
			,xEndSection(true)
			,yBeginSection(true)
			,yEndSection(true)
		{
		}

		ImageView(		PixelDataType * const & _imageDataPtr,
				  const PixelDataType * const & _imageDataPtrEnd,
				  const ImageSize & _size,
				  const I4 & _stride,
				  const I4 & _numPixelsBetweenRows,
				  const B1 & _xBeginSection,
				  const B1 & _xEndSection,
				  const B1 & _yBeginSection,
				  const B1 & _yEndSection
		)
			:imageDataPtr(_imageDataPtr)
			,imageDataPtrEnd(_imageDataPtrEnd)
			,stride(_stride)
			,size(_size)
			,simpleView(false)
			,numPixelsBetweenRows(_numPixelsBetweenRows)
			,xBeginSection(_xBeginSection)
			,xEndSection(_xEndSection)
			,yBeginSection(_yBeginSection)
			,yEndSection(_yEndSection)
		{
		}

		      std::vector<ThisType> makeGrid(const I4 & cellWidthTry,const I4 & cellHeightTry, const I4 & xOffset, const I4 & yOffset, const I4 & filterWidth, const I4 & filterHeight);
		const std::vector<ThisType> makeGrid(const I4 & cellWidthTry,const I4 & cellHeightTry, const I4 & xOffset, const I4 & yOffset, const I4 & filterWidth, const I4 & filterHeight) const ;

		FINLINE       PixelDataType * getDataPtr()       {return imageDataPtr;}
		FINLINE const PixelDataType * getDataPtr() const {return imageDataPtr;}

		FINLINE const PixelDataType * const & getDataPtrEnd() const {return imageDataPtrEnd;}

		FINLINE const I4 & getStride() const {return stride;}

		FINLINE const ImageSize & getSize() const {return size;}
		
		FINLINE const I4 & getWidth()  const {return size.getWidth() ;}
		FINLINE const I4 & getHeight() const {return size.getHeight();}

		FINLINE const B1 & isSimpleView() const {return simpleView;}

		FINLINE const B1 & hasXbeginSection() const {return xBeginSection;}
		FINLINE const B1 & hasXendSection()   const {return xEndSection  ;}
		FINLINE const B1 & hasYbeginSection() const {return yBeginSection;}
		FINLINE const B1 & hasYendSection()   const {return yEndSection  ;}

		FINLINE const I4 & getNumPixelsBetweenRows()  const {return numPixelsBetweenRows;}

		PixelDataType & getPixel(const I4 & x,const I4 & y) {
			I4 tempX=x;if(x<0){tempX=0;}else if(x>=size.getWidth() ){tempX=size.getWidth_1() ;}
			I4 tempY=y;if(y<0){tempY=0;}else if(y>=size.getHeight()){tempY=size.getHeight_1();}
			return imageDataPtr[tempX+tempY*stride];
		}
		const PixelDataType & getPixel(const I4 & x,const I4 & y) const {
			I4 tempX=x;if(x<0){tempX=0;}else if(x>=size.getWidth() ){tempX=size.getWidth_1() ;}
			I4 tempY=y;if(y<0){tempY=0;}else if(y>=size.getHeight()){tempY=size.getHeight_1();}
			return imageDataPtr[tempX+tempY*stride];
		}

	private:

		std::vector<ThisType> makeGrid_p(const I4 & width,const I4 & height, const I4 & xOffset, const I4 & yOffset, const I4 & filterWidth, const I4 & filterHeight) const ;

		      PixelDataType * imageDataPtr;
		const PixelDataType * imageDataPtrEnd;

		I4 stride;
		I4 numPixelsBetweenRows;

		ImageSize size;

		B1 simpleView;

		B1 xBeginSection;
		B1 xEndSection;
		B1 yBeginSection;
		B1 yEndSection;

};

}

#endif
