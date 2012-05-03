
#include "ImageView.h"

namespace Image {

template <
	typename PixelDataType
> AIL_DLL_EXPORT std::vector<ImageView<PixelDataType>> ImageView<PixelDataType>::makeGrid(const I4 & width,const I4 & height, const I4 & borderXLeft, const I4 & borderXRight, const I4 & borderYBottom, const I4 & borderYTop){
	return makeGrid_p(width,height,borderXLeft,borderXRight,borderYBottom,borderYTop);
}

template <
	typename PixelDataType
> AIL_DLL_EXPORT const std::vector<ImageView<PixelDataType>> ImageView<PixelDataType>::makeGrid(const I4 & width,const I4 & height, const I4 & borderXLeft, const I4 & borderXRight, const I4 & borderYBottom, const I4 & borderYTop) const {
	return makeGrid_p(width,height,borderXLeft,borderXRight,borderYBottom,borderYTop);
}

template <
	typename PixelDataType
> AIL_DLL_EXPORT std::vector<ImageView<PixelDataType>> ImageView<PixelDataType>::makeGrid_p(const I4 & width,const I4 & height, const I4 & borderXLeft, const I4 & borderXRight, const I4 & borderYBottom, const I4 & borderYTop) const {
	std::vector<ImageView<PixelDataType>> grid;
	if((size.getHeight()<height)&&(size.getWidth()<width)){
		ImageView<PixelDataType> cell(*this);
		grid.push_back(cell);
		return grid;
	}
	I4 cellWidth  = (width  - borderXLeft   - borderXRight);
	I4 cellHeight = (height - borderYBottom - borderYTop  );
	if((cellWidth<0)||(cellHeight<0)){
		ImageView<PixelDataType> cell(*this);
		grid.push_back(cell);
		return grid;
	}

	//TODO: Handle borders properly - this only works right now with 0 border
	ImageSize cellSize(cellWidth,cellHeight);

	I4 cellsY = ( (size.getHeight() - 1) / cellHeight) + 1;
	I4 cellsX = ( (size.getWidth()  - 1) / cellWidth ) + 1;
	for(I4 yIndex=0;yIndex<cellsY;++yIndex){
		for(I4 xIndex=0;xIndex<cellsX;++xIndex){
			I4 cellWidthActual =((cellWidth *(xIndex+1))<size.getWidth() )?cellWidth :(size.getWidth() -(xIndex*cellWidth ));
			I4 cellHeightActual=((cellHeight*(yIndex+1))<size.getHeight())?cellHeight:(size.getHeight()-(yIndex*cellHeight));
			ImageSize cellSizeActual(cellWidthActual,cellHeightActual);
			
			I4 cellNumPixelsBetweenRows = size.getWidth() - cellWidthActual;

			I4 xStart = xIndex * cellWidth ;
			I4 yStart = yIndex * cellHeight;
			I4 xEnd   = xIndex * cellWidth  + cellWidthActual;
			I4 yEnd   = yIndex * cellHeight + cellHeightActual - 1;

			ImageView<PixelDataType> cell(imageDataPtr + xStart + size.getWidth()*yStart
										 ,imageDataPtr + xEnd   + size.getWidth()*yEnd
										 ,cellSizeActual
										 ,cellNumPixelsBetweenRows
										 ,true
										 ,true
										 ,true
										 ,true);
			grid.push_back(cell);
		}
	}
	return grid;
}

}


#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Image::ImageView)
CREATE_PIXELDATA_TEMPLATE_CALLS(Image::ImageView)
