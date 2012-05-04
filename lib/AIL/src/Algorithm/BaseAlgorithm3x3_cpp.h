
#ifndef ALGORITHM__BaseAlgorithm3x3_CPP_H
#define ALGORITHM__BaseAlgorithm3x3_CPP_H

#include <Image/ImageView.h>

namespace Algorithm {

template <
	typename AlgorithmType,
	typename PixelDataType
> void BaseAlgorithm3x3 (
	const Image::ImageView<PixelDataType> & srcImage,
	Image::ImageView<PixelDataType> & dstImage)
{
	if(srcImage.getSize()!=dstImage.getSize()){return;}
	if((srcImage.isSimpleView()==false)||(dstImage.isSimpleView()==false)){return;} // TODO: implement the other cases

	auto srcImageHeightm1 = srcImage.getHeight()-1;

	const auto & srcImageWidth   = srcImage.getWidth();
	      auto   srcImageWidthm1 = srcImage.getWidth()-1;
	      auto   srcImageWidthp1 = srcImage.getWidth()+1;

	auto srcImageDataPtr = srcImage.getDataPtr();
	auto dstImageDataPtr = dstImage.getDataPtr();
	
	I4 y = 0; // TODO: Write these loops to get rid of x and y ... and make sure that the complier still unrolls the loops
	I4 x = 0;

	//First Row - First Pixel
	AlgorithmType::process(dstImageDataPtr,srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
	                                       srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
	                                       srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidthp1);
	++dstImageDataPtr;
	++srcImageDataPtr;

	//First Row - Inside Pixels
	for (x=1; x<srcImageWidthm1; ++x){
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
											   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
											   srcImageDataPtr+srcImageWidthm1,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidthp1);
		++dstImageDataPtr;
		++srcImageDataPtr;
	}
	//First Row - Last Pixel
	AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr              ,
										   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr              ,
										   srcImageDataPtr+srcImageWidthm1,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidth);
	++dstImageDataPtr;
	++srcImageDataPtr;

	for (y=1; y<srcImageHeightm1; ++y){	
		//Inside Row - First Pixel
		x=0;
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidthm1,
											   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
											   srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidthp1);
		++dstImageDataPtr;
		++srcImageDataPtr;
		//Inside Row - Inside Pixels
		for (x=1; x<srcImageWidthm1; ++x){
			AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidthp1,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidthm1,
												   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
												   srcImageDataPtr+srcImageWidthm1,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidthp1);
			++dstImageDataPtr;
			++srcImageDataPtr;
		}
		//Inside Row - Last Pixel
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidthp1,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidth,
											   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr              ,
											   srcImageDataPtr+srcImageWidthm1,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidth);
		++dstImageDataPtr;
		++srcImageDataPtr;
	}
	x=0;

	//Last Row - First pixel
	AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidthm1,
										   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
										   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              );
	++dstImageDataPtr;
	++srcImageDataPtr;

	//Last Row - Inside Pixels
	for (x=1; x<srcImageWidthm1; ++x){
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidthp1,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidthm1,
											   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
											   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr+1              );
		++dstImageDataPtr;
		++srcImageDataPtr;
	}

	//Last Row - Last Pixel
	AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidthp1,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidth,
										   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr              ,
										   srcImageDataPtr-1              ,srcImageDataPtr              ,srcImageDataPtr              );

}


};

#endif
