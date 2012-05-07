
#include "ImageView.h"

namespace Image {

template <
	typename PixelDataType
> AIL_DLL_EXPORT std::vector<ImageView<PixelDataType>> ImageView<PixelDataType>::makeGrid(const I4 & cellWidthTry,const I4 & cellHeightTry, const I4 & xOffset, const I4 & yOffset, const I4 & filterWidth, const I4 & filterHeight){
	return makeGrid_p(cellWidthTry,cellHeightTry,xOffset,yOffset,filterWidth,filterHeight);
}

template <
	typename PixelDataType
> AIL_DLL_EXPORT const std::vector<ImageView<PixelDataType>> ImageView<PixelDataType>::makeGrid(const I4 & cellWidthTry,const I4 & cellHeightTry, const I4 & xOffset, const I4 & yOffset, const I4 & filterWidth, const I4 & filterHeight) const {
	return makeGrid_p(cellWidthTry,cellHeightTry,xOffset,yOffset,filterWidth,filterHeight);
}

template <
	typename PixelDataType
> AIL_DLL_EXPORT std::vector<ImageView<PixelDataType>> ImageView<PixelDataType>::makeGrid_p(const I4 & cellWidthTry,const I4 & cellHeightTry, const I4 & xOffset, const I4 & yOffset, const I4 & filterWidth, const I4 & filterHeight) const {
	std::vector<ImageView<PixelDataType>> grid;
	if((size.getHeight()<cellHeightTry)&&(size.getWidth()<cellWidthTry)){
		ImageView<PixelDataType> cell(*this);
		grid.push_back(cell);
		return grid;
	}
	I4 cellWidth =0;
	I4 cellHeight=0;
	if(cellWidthTry <=(filterWidth +10)){cellWidth =filterWidth +10;}else{cellWidth=cellWidthTry  ;}  //TODO: This bounds check can be tighter ... work it out properly sometime
	if(cellHeightTry<=(filterHeight+10)){cellHeight=filterHeight+10;}else{cellHeight=cellHeightTry;}

	I4 cellsY = ( (size.getHeight() - 1) / cellHeight) + 1;
	I4 cellsX = ( (size.getWidth()  - 1) / cellWidth ) + 1;
	for(I4 yIndex=0;yIndex<cellsY;++yIndex){
		for(I4 xIndex=0;xIndex<cellsX;++xIndex){
			I4 cellWidthClip =((cellWidth *(xIndex+1))<size.getWidth() )?cellWidth :(size.getWidth() -(xIndex*cellWidth ));
			I4 cellHeightClip=((cellHeight*(yIndex+1))<size.getHeight())?cellHeight:(size.getHeight()-(yIndex*cellHeight));
			
			I4 xStart = xIndex * cellWidth  - xOffset;if(xStart<0){xStart=0;}
			I4 yStart = yIndex * cellHeight - yOffset;if(yStart<0){yStart=0;}
			I4 xEnd   = xIndex * cellWidth  + cellWidthClip  + (filterWidth  - xOffset - 1);if(xEnd>size.getWidth() ){xEnd = size.getWidth() ;}
			I4 yEnd   = yIndex * cellHeight + cellHeightClip + (filterHeight - yOffset - 1);if(yEnd>size.getHeight()){yEnd = size.getHeight();}

			I4 cellWidthActual =xEnd-xStart;
			I4 cellHeightActual=yEnd-yStart;

			ImageSize cellSizeActual(cellWidthActual,cellHeightActual);

			ImageView<PixelDataType> cell(imageDataPtr + xStart + stride*yStart
										 ,imageDataPtr + xEnd   + stride*yEnd   + 1
										 ,cellSizeActual
										 ,stride
										 ,stride - cellWidthActual
										 ,(xIndex==        0 )?true:false
										 ,(xIndex==(cellsX-1))?true:false
										 ,(yIndex==        0 )?true:false
										 ,(yIndex==(cellsY-1))?true:false);
			grid.push_back(cell);
		}
	}
	return grid;
}

}


#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Image::ImageView)
CREATE_PIXELDATA_TEMPLATE_CALLS(Image::ImageView)
