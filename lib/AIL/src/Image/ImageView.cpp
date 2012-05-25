
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
	if((size.getHeight()<filterHeight)&&(size.getWidth()<filterWidth)){
		ImageView<PixelDataType> cell(*this);
		grid.push_back(cell);
		return grid;
	}
	I4 cellWidth  = cellWidthTry;
	I4 cellHeight = cellHeightTry;
	if(size.getHeight()<filterHeight){
		//NOTE: TODO: While this case appears correct it has not been properly tested due to the fact that the BaseAlgorithms do not support filters larger than the image yet.
		//            After that support is added then this can be tested

		if(xOffset>0){
			ImageView<PixelDataType> beginCell(imageDataPtr
											  ,imageDataPtr + filterWidth + stride*size.getHeight_1() + 1
											  ,ImageSize(filterWidth,size.getHeight())
											  ,stride
											  ,stride - filterWidth
											  ,true,false,true,true);
			grid.push_back(beginCell);
		}

		I4 cellsX = ( (size.getWidth() - filterWidth) / cellWidth );
		for(I4 xIndex=0;xIndex<cellsX;++xIndex){
			I4 cellWidthClip = (xIndex==(cellsX-1)) ? (size.getWidth()-(xIndex*cellWidth)) : (cellWidth + filterWidth);
			
			I4 xStart = xIndex*cellWidth;
			I4 xEnd   = xIndex*cellWidth + cellWidthClip;

			ImageView<PixelDataType> cell(imageDataPtr + xStart
										 ,imageDataPtr + xEnd   + stride*size.getHeight_1() + 1
										 ,ImageSize(cellWidthClip,size.getHeight())
										 ,stride
										 ,stride - cellWidthClip
										 ,false,false,true,true);
			grid.push_back(cell);
		}

		ImageView<PixelDataType> endCell(imageDataPtr + size.getWidth() - filterWidth
										,imageDataPtr + size.getWidth() + stride*size.getHeight_1()
										,ImageSize(filterWidth,size.getHeight())
										,stride
										,stride - filterWidth
										,false,true,true,true);
		grid.push_back(endCell);

		return grid;
	}
	if(size.getWidth()<filterWidth){
		//NOTE: TODO: While this case appears correct it has not been properly tested due to the fact that the BaseAlgorithms do not support filters larger than the image yet.
		//            After that support is added then this can be tested

		if(yOffset>0){
			ImageView<PixelDataType> beginCell(imageDataPtr
											  ,imageDataPtr + size.getWidth() + stride*(filterHeight - 1) + 1
											  ,ImageSize(size.getWidth(),filterHeight)
											  ,stride,numPixelsBetweenRows,true,true,true,false);
			grid.push_back(beginCell);
		}

		I4 cellsY = ( (size.getHeight() - filterHeight) / cellHeight );
		for(I4 yIndex=0;yIndex<cellsY;++yIndex){
			I4 cellHeightClip = (yIndex==(cellsY-1)) ? (size.getHeight()-(yIndex*cellHeight)) : (cellHeight + filterHeight);
			
			I4 yStart = yIndex*cellHeight;
			I4 yEnd   = yIndex*cellHeight + cellHeightClip;

			ImageView<PixelDataType> cell(imageDataPtr + stride*yStart
										 ,imageDataPtr + stride*yEnd   + size.getWidth() + 1
										 ,ImageSize(size.getWidth(),cellHeightClip)
										 ,stride,numPixelsBetweenRows,true,true,false,false);
			grid.push_back(cell);
		}

		ImageView<PixelDataType> endCell(imageDataPtr + stride * (size.getHeight_1()-filterHeight)
										,imageDataPtr + stride *  size.getHeight_1()               + size.getWidth()
										,ImageSize(size.getWidth(),filterHeight)
										,stride,numPixelsBetweenRows,true,true,false,true);
		grid.push_back(endCell);

		return grid;
	}
	if((filterHeight==1)&&(filterWidth==1)){
		I4 cellsY = (size.getHeight_1() / cellHeight) + 1;
		I4 cellsX = (size.getWidth_1()  / cellWidth ) + 1;
		for(I4 yIndex=0;yIndex<cellsY;++yIndex){
			for(I4 xIndex=0;xIndex<cellsX;++xIndex){
				I4 cellWidthClip =(xIndex==(cellsX-1))?(size.getWidth() -(xIndex*cellWidth )):cellWidth ;
				I4 cellHeightClip=(yIndex==(cellsY-1))?(size.getHeight()-(yIndex*cellHeight)):cellHeight;
			
				I4 xStart = xIndex * cellWidth ;
				I4 yStart = yIndex * cellHeight;
				I4 xEnd   = xIndex * cellWidth  + cellWidthClip  - 1;
				I4 yEnd   = yIndex * cellHeight + cellHeightClip - 1;

				ImageView<PixelDataType> cell(imageDataPtr + xStart + stride*yStart
											 ,imageDataPtr + xEnd   + stride*yEnd   + 1
											 ,ImageSize(cellWidthClip,cellHeightClip)
											 ,stride,stride-cellWidthClip,true,true,true,true);
				grid.push_back(cell);
			}
		}
		return grid;
	}
	if(filterHeight==1){
		I4 cellsY = (size.getHeight_1() / cellHeight) + 1;
		for(I4 yIndex=0;yIndex<cellsY;++yIndex){
			I4 cellHeightClip = (yIndex==(cellsY-1)) ? (size.getHeight()-(yIndex*cellHeight)) : cellHeight;
			
			I4 yStart = yIndex*cellHeight;
			I4 yEnd   = yIndex*cellHeight + cellHeightClip - 1;

			ImageView<PixelDataType> beginCell(imageDataPtr + stride*yStart
											  ,imageDataPtr + stride*yEnd   + filterWidth
											  ,ImageSize(filterWidth,cellHeightClip)
											  ,stride,stride-filterWidth,true,false,false,false);
			grid.push_back(beginCell);

			ImageView<PixelDataType> endCell(imageDataPtr + stride*yStart + size.getWidth() - filterWidth
											,imageDataPtr + stride*yEnd   + size.getWidth()
											,ImageSize(filterWidth,cellHeightClip)
											,stride,stride-filterWidth,false,true,false,false);
			grid.push_back(endCell);
		}

		I4 cellsX = ( (size.getWidth() - filterWidth) / cellWidth );
		for(I4 yIndex=0;yIndex<cellsY;++yIndex){
			for(I4 xIndex=0;xIndex<cellsX;++xIndex){
				I4 cellWidthClip =(xIndex==(cellsX-1)) ? (size.getWidth() -(xIndex*cellWidth )) : (cellWidth + filterWidth);
				I4 cellHeightClip=(yIndex==(cellsY-1)) ? (size.getHeight()-(yIndex*cellHeight)) : cellHeight;
			
				I4 xStart = xIndex * cellWidth ;
				I4 yStart = yIndex * cellHeight;
				I4 xEnd   = xIndex * cellWidth  + cellWidthClip  - 1;
				I4 yEnd   = yIndex * cellHeight + cellHeightClip - 1;

				ImageView<PixelDataType> cell(imageDataPtr + xStart + stride*yStart
											 ,imageDataPtr + xEnd   + stride*yEnd   + 1
											 ,ImageSize(cellWidthClip,cellHeightClip)
											 ,stride,stride-cellWidthClip,false,false,false,false);
				grid.push_back(cell);
			}
		}

		return grid;
	}
	if(filterWidth==1){
		I4 cellsX = (size.getWidth_1() / cellWidth) + 1;
		for(I4 xIndex=0;xIndex<cellsX;++xIndex){
			I4 cellWidthClip = (xIndex==(cellsX-1)) ? (size.getWidth()-(xIndex*cellWidth)) : cellWidth;
			
			I4 xStart = xIndex*cellHeight;
			I4 xEnd   = xIndex*cellHeight + cellWidthClip - 1;

			ImageView<PixelDataType> beginCell(imageDataPtr + xStart
											  ,imageDataPtr + xEnd   + stride*(filterHeight)
											  ,ImageSize(cellWidthClip,filterHeight)
											  ,stride,stride-cellWidthClip,false,false,true,false);
			grid.push_back(beginCell);

			ImageView<PixelDataType> endCell(imageDataPtr + xStart + stride*(size.getHeight() - filterHeight)
											,imageDataPtr + xEnd   + stride*(size.getHeight()               )
											,ImageSize(cellWidthClip,filterHeight)
											,stride,stride-cellWidthClip,false,false,false,true);
			grid.push_back(endCell);
		}

		I4 cellsY = ( (size.getHeight() - filterHeight) / cellHeight);
		for(I4 yIndex=0;yIndex<cellsY;++yIndex){
			for(I4 xIndex=0;xIndex<cellsX;++xIndex){
				I4 cellWidthClip =(xIndex==(cellsX-1)) ? (size.getWidth() -(xIndex*cellWidth )) : cellWidth;
				I4 cellHeightClip=(yIndex==(cellsY-1)) ? (size.getHeight()-(yIndex*cellHeight)) : (cellHeight + filterHeight);
			
				I4 xStart = xIndex * cellWidth ;
				I4 yStart = yIndex * cellHeight;
				I4 xEnd   = xIndex * cellWidth  + cellWidthClip  - 1;
				I4 yEnd   = yIndex * cellHeight + cellHeightClip - 1;

				ImageView<PixelDataType> cell(imageDataPtr + xStart + stride*yStart
											 ,imageDataPtr + xEnd   + stride*yEnd   + 1
											 ,ImageSize(cellWidthClip,cellHeightClip)
											 ,stride,stride-cellWidthClip,false,false,false,false);
				grid.push_back(cell);
			}
		}

		return grid;
	}

	if((yOffset>0)&&(xOffset>0)){
		ImageView<PixelDataType> beginXbeginYCell(imageDataPtr
												 ,imageDataPtr + stride*(filterHeight - 1) + filterWidth
												 ,ImageSize(filterWidth,filterHeight)
												 ,stride,stride-filterWidth,true,false,true,false);
		grid.push_back(beginXbeginYCell);
	}

	if( (xOffset>0) && ( (filterHeight-yOffset-1) > 0 ) ){
		ImageView<PixelDataType> beginXendYCell(imageDataPtr + stride * (size.getHeight_1()-filterHeight)
											   ,imageDataPtr + stride *  size.getHeight_1()               + filterWidth
											   ,ImageSize(filterWidth,filterHeight)
											   ,stride,stride-filterWidth,true,false,false,true);
		grid.push_back(beginXendYCell);
	}

	if( (yOffset>0) && ( (filterWidth-xOffset-1) > 0 ) ){
		ImageView<PixelDataType> endXbeginYCell(imageDataPtr + size.getWidth() - filterWidth
											   ,imageDataPtr + size.getWidth()               + stride*(filterHeight - 1)
											   ,ImageSize(filterWidth,filterHeight)
											   ,stride,stride-filterWidth,false,true,true,false);
		grid.push_back(endXbeginYCell);
	}

	if( ( (filterWidth-xOffset-1) > 0 ) && ( (filterWidth-xOffset-1) > 0 ) ){
		ImageView<PixelDataType> endXendYCell(imageDataPtr + stride * (size.getHeight_1()-filterHeight) + size.getWidth() - filterWidth
											 ,imageDataPtr + stride *  size.getHeight_1()               + size.getWidth()
											 ,ImageSize(filterWidth,filterHeight)
											 ,stride,stride-filterWidth,false,true,false,true);
		grid.push_back(endXendYCell);
	}

	I4 cellsX = ( (size.getWidth()  - filterWidth)  / cellWidth );
	I4 cellsY = ( (size.getHeight() - filterHeight) / cellHeight);

	for(I4 xIndex=0;xIndex<cellsX;++xIndex){
		I4 cellWidthClip = (xIndex==(cellsX-1)) ? (size.getWidth()-(xIndex*cellWidth)) : (cellWidth  + filterWidth );
			
		I4 xStart = xIndex*cellHeight;
		I4 xEnd   = xIndex*cellHeight + cellWidthClip - 1;

		ImageView<PixelDataType> beginYcell(imageDataPtr + xStart
										   ,imageDataPtr + xEnd   + stride*(filterHeight)
										   ,ImageSize(cellWidthClip,filterHeight)
										   ,stride,stride-cellWidthClip,false,false,true,false);
		grid.push_back(beginYcell);

		ImageView<PixelDataType> endYcell(imageDataPtr + xStart + stride*(size.getHeight() - filterHeight)
										 ,imageDataPtr + xEnd   + stride*(size.getHeight()               )
										 ,ImageSize(cellWidthClip,filterHeight)
										 ,stride,stride-cellWidthClip,false,false,false,true);
		grid.push_back(endYcell);
	}

	for(I4 yIndex=0;yIndex<cellsY;++yIndex){
		I4 cellHeightClip = (yIndex==(cellsY-1)) ? (size.getHeight()-(yIndex*cellHeight)) : (cellHeight + filterHeight);
			
		I4 yStart = yIndex*cellHeight;
		I4 yEnd   = yIndex*cellHeight + cellHeightClip - 1;

		ImageView<PixelDataType> beginXCell(imageDataPtr + stride*yStart
										   ,imageDataPtr + stride*yEnd   + filterWidth
										   ,ImageSize(filterWidth,cellHeightClip)
										   ,stride,stride-filterWidth,true,false,false,false);
		grid.push_back(beginXCell);

		ImageView<PixelDataType> endXCell(imageDataPtr + stride*yStart + size.getWidth() - filterWidth
										 ,imageDataPtr + stride*yEnd   + size.getWidth()
										 ,ImageSize(filterWidth,cellHeightClip)
										 ,stride,stride-filterWidth,false,true,false,false);
		grid.push_back(endXCell);
	}

	for(I4 yIndex=0;yIndex<cellsY;++yIndex){
		for(I4 xIndex=0;xIndex<cellsX;++xIndex){
			I4 cellWidthClip =(xIndex==(cellsX-1)) ? (size.getWidth() -(xIndex*cellWidth )) : (cellWidth  + filterWidth );
			I4 cellHeightClip=(yIndex==(cellsY-1)) ? (size.getHeight()-(yIndex*cellHeight)) : (cellHeight + filterHeight);
			
			I4 xStart = xIndex * cellWidth ;
			I4 yStart = yIndex * cellHeight;
			I4 xEnd   = xIndex * cellWidth  + cellWidthClip  - 1;
			I4 yEnd   = yIndex * cellHeight + cellHeightClip - 1;

			ImageView<PixelDataType> cell(imageDataPtr + xStart + stride*yStart
										 ,imageDataPtr + xEnd   + stride*yEnd   + 1
										 ,ImageSize(cellWidthClip,cellHeightClip)
										 ,stride,stride-cellWidthClip,false,false,false,false);
			grid.push_back(cell);
		}
	}

	return grid;
}

}


#include <Pixel/PixelTemplateMacros.h>
CREATE_PIXEL_TEMPLATE_CALLS(Image::ImageView)
CREATE_PIXELDATA_TEMPLATE_CALLS(Image::ImageView)
