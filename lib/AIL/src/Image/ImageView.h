
#ifndef IMAGE__ImageView_H
#define IMAGE__ImageView_H

#include "AIL.h"
#include "ImageSize.h"

namespace Image {

template <
	typename PixelDataType
> class AIL_DLL_EXPORT ImageView {
	public:

		typedef ImageView<PixelDataType> ThisType;

		ImageView(const ThisType & _view)
			:imageDataPtr(_view.imageDataPtr)
			,imageDataPtrEnd(_view.imageDataPtrEnd)
			,size(_view.size)
			,simpleView(_view.simpleView)
			,numPixelsBetweenRows(_view.numPixelsBetweenRows)
			,top(_view.top)
			,bottom(_view.bottom)
			,left(_view.left)
			,right(_view.right)
		{
		}

		const ImageView &operator=(const ThisType & _view){
			imageDataPtr=_view.imageDataPtr;
			imageDataPtrEnd=_view.imageDataPtrEnd;
			size=_view.size;
			simpleView=_view.simpleView;
			numPixelsBetweenRows=_view.numPixelsBetweenRows;
			top=_view.top;
			bottom=_view.bottom;
			left=_view.left;
			right=_view.right;
			return (*this);
		}

		ImageView(PixelDataType * const & _imageDataPtr,
				  const PixelDataType * const & _imageDataPtrEnd,
				  const ImageSize & _size
		)
			:imageDataPtr(_imageDataPtr)
			,imageDataPtrEnd(_imageDataPtrEnd)
			,size(_size)
			,simpleView(true)
			,numPixelsBetweenRows(0)
			,top(true)
			,bottom(true)
			,left(true)
			,right(true)
		{
		}

		ImageView(PixelDataType * const & _imageDataPtr,
				  const PixelDataType * const & _imageDataPtrEnd,
				  const ImageSize & _size,
				  const I4   & _numPixelsBetweenRows,
				  const bool & _hasTop,
				  const bool & _hasBottom,
				  const bool & _hasLeft,
				  const bool & _hasRight
		)
			:imageDataPtr(_imageDataPtr)
			,imageDataPtrEnd(_imageDataPtrEnd)
			,size(_size)
			,simpleView(false)
			,numPixelsBetweenRows(_numPixelsBetweenRows)
			,top(_hasTop)
			,bottom(_hasBottom)
			,left(_hasLeft)
			,right(_hasRight)
		{
		}

		FINLINE       PixelDataType * getDataPtr()       {return imageDataPtr;}
		FINLINE const PixelDataType * getDataPtr() const {return imageDataPtr;}

		FINLINE const PixelDataType * const & getDataPtrEnd() const {return imageDataPtrEnd;}

		FINLINE const ImageSize & getSize() const {return size;}
		
		FINLINE const I4 & getWidth()  const {return size.getWidth();}
		FINLINE const I4 & getHeight() const {return size.getHeight();}

		FINLINE const bool & isSimpleView() const {return simpleView;}

		FINLINE const bool & hasTop()    const {return top   ;}
		FINLINE const bool & hasBottom() const {return bottom;}
		FINLINE const bool & hasLeft()   const {return left  ;}
		FINLINE const bool & hasRight()  const {return right ;}

		PixelDataType & getPixel(const I4 & x,const I4 & y) {
			I4 tempX=x;if(x<0){tempX=0;}else if(x>=size.getWidth() ){tempX=size.getWidth_1();}
			I4 tempY=y;if(y<0){tempY=0;}else if(y>=size.getHeight()){tempY=size.getHeight_1();}
			return imageDataPtr[tempX+tempY*size.getWidth()];
		}
		const PixelDataType & getPixel(const I4 & x,const I4 & y) const {
			I4 tempX=x;if(x<0){tempX=0;}else if(x>=size.getWidth() ){tempX=size.getWidth_1();}
			I4 tempY=y;if(y<0){tempY=0;}else if(y>=size.getHeight()){tempY=size.getHeight_1();}
			return imageDataPtr[tempX+tempY*size.getWidth()];
		}

	private:
		PixelDataType * imageDataPtr;
		const PixelDataType * imageDataPtrEnd;

		ImageSize size;

		I4 numPixelsBetweenRows;

		bool simpleView;

		bool top;
		bool bottom;
		bool left;
		bool right;

};

}

#endif
