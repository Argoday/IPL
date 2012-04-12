
#ifndef ALGORITHM__BaseAlgorithm3x3_CPP_H
#define ALGORITHM__BaseAlgorithm3x3_CPP_H

#include <Image/ImageView.h>

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelDataType
> void BaseAlgorithm3x3 (
	const Image::ImageView<PixelDataType> &srcImage,
	Image::ImageView<PixelDataType> &dstImage)
{
	if((srcImage.isSimpleView()==false)||(dstImage.isSimpleView()==false)){return;} // TODO: implement the other cases
	if(srcImage.getSize()!=dstImage.getSize()){return;}

	long srcImageHeightm1 = srcImage.getHeight()-1;

	long srcImageWidth    = srcImage.getWidth();
	long srcImageWidthm1  = srcImage.getWidth()-1;
	long srcImageWidthp1  = srcImage.getWidth()+1;

	const PixelDataType * srcImageDataPtr = srcImage.getDataPtr();
	PixelDataType * dstImageDataPtr = dstImage.getDataPtr();
	
	long y = 0; // TODO: Write these loops to get rid of x and y ... and make sure that the complier still unrolls the loops
	long x = 0;

	//First Pixel
	AlgorithmType::process(dstImageDataPtr,srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
	                                       srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
	                                       srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidthp1);
	++dstImageDataPtr;
	++srcImageDataPtr;

	//First Row
	for (x=1; x<srcImageWidthm1; ++x){
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
											   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
											   srcImageDataPtr+srcImageWidthm1,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidthp1);
		++dstImageDataPtr;
		++srcImageDataPtr;
	}
	//Last Pixel First Row
	AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr              ,
										   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr              ,
										   srcImageDataPtr+srcImageWidthm1,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidth);
	++dstImageDataPtr;
	++srcImageDataPtr;

	for (y=1; y<srcImageHeightm1; ++y){	
		//First Pixel of inside Row
		x=0;
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidthm1,
											   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
											   srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidthp1);
		++dstImageDataPtr;
		++srcImageDataPtr;
		//Inside Row
		for (x=1; x<srcImageWidthm1; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidthp1,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidthm1,
												   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
												   srcImageDataPtr+srcImageWidthm1,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidthp1);
			++dstImageDataPtr;
			++srcImageDataPtr;
		}
		//Last Pixel Inside Row
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidthp1,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidth,
											   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr              ,
											   srcImageDataPtr+srcImageWidthm1,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidth);
		++dstImageDataPtr;
		++srcImageDataPtr;
	}
	x=0;

	//Last Row, first pixel
	AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidthm1,
										   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
										   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              );
	++dstImageDataPtr;
	++srcImageDataPtr;

	//Last Row
	for (x=1; x<srcImageWidthm1; ++x){
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidthp1,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidthm1,
											   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
											   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr+1              );
		++dstImageDataPtr;
		++srcImageDataPtr;
	}

	//Last Pixel Last Row
	AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidthp1,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidth,
										   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr              ,
										   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr              );

}


};

#endif
