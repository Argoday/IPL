
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

	if((srcImage.isSimpleView()==true)&&(dstImage.isSimpleView()==true)){
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
		for(x=1; x<srcImageWidthm1; ++x){
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

		for(y=1; y<srcImageHeightm1; ++y){	
			//Inside Row - First Pixel
			AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidthm1,
												   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
												   srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidth,srcImageDataPtr+srcImageWidthp1);
			++dstImageDataPtr;
			++srcImageDataPtr;
			//Inside Row - Inside Pixels
			for(x=1; x<srcImageWidthm1; ++x){
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

		//Last Row - First pixel
		AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidth,srcImageDataPtr-srcImageWidthm1,
											   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              ,
											   srcImageDataPtr              ,srcImageDataPtr              ,srcImageDataPtr+1              );
		++dstImageDataPtr;
		++srcImageDataPtr;

		//Last Row - Inside Pixels
		for(x=1; x<srcImageWidthm1; ++x){
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

	}else{
		auto srcImageHeightm1 = srcImage.getHeight()-1;

		const auto & srcImageWidth   = srcImage.getWidth();
			  auto   srcImageWidthm1 = srcImage.getWidth()-1;
			  auto   srcImageWidthp1 = srcImage.getWidth()+1;

		const auto & srcImageStride   = srcImage.getStride();
			  auto   srcImageStridem1 = srcImage.getStride()-1;
			  auto   srcImageStridep1 = srcImage.getStride()+1;

		auto dstImageDataPtr = dstImage.getDataPtr();
		auto srcImageDataPtr = srcImage.getDataPtr();
	
		I4 y = 0; // TODO: Write these loops to get rid of x and y ... and make sure that the complier still unrolls the loops
		I4 x = 0;

		if(srcImage.hasYbeginSection()==true){
			if(srcImage.hasXbeginSection()==true){
				//First Row - First Pixel
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr               ,srcImageDataPtr               ,srcImageDataPtr+1              ,
													   srcImageDataPtr               ,srcImageDataPtr               ,srcImageDataPtr+1              ,
													   srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStridep1);
			}
			++dstImageDataPtr;
			++srcImageDataPtr;

			//First Row - Inside Pixels
			for(x=1;x<srcImageWidthm1;++x){
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-1               ,srcImageDataPtr               ,srcImageDataPtr+1              ,
													   srcImageDataPtr-1               ,srcImageDataPtr               ,srcImageDataPtr+1              ,
													   srcImageDataPtr+srcImageStridem1,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStridep1);
				++dstImageDataPtr;
				++srcImageDataPtr;
			}

			if(srcImage.hasXendSection()==true){
				//First Row - Last Pixel
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-1               ,srcImageDataPtr               ,srcImageDataPtr              ,
													   srcImageDataPtr-1               ,srcImageDataPtr               ,srcImageDataPtr              ,
													   srcImageDataPtr+srcImageStridem1,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStride);
			}
			++dstImageDataPtr;
			++srcImageDataPtr;
		}else{
			dstImageDataPtr+=srcImageWidth;
			srcImageDataPtr+=srcImageWidth;
		}
		dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
		srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();

		if((srcImage.hasXbeginSection()==false)&&(srcImage.hasXendSection()==false)){
			for(y=1;y<srcImageHeightm1;++y){
				++dstImageDataPtr;
				++srcImageDataPtr;
				//Inside Row - Inside Pixels
				for (x=1; x<srcImageWidthm1; ++x){
					AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStridep1,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStridem1,
														   srcImageDataPtr-1               ,srcImageDataPtr               ,srcImageDataPtr+1              ,
														   srcImageDataPtr+srcImageStridem1,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStridep1);
					++dstImageDataPtr;
					++srcImageDataPtr;
				}
				++dstImageDataPtr;
				++srcImageDataPtr;
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
				srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
			}
		}else if((srcImage.hasXbeginSection()==true)&&(srcImage.hasXendSection()==false)){
			for(y=1; y<srcImageHeightm1; ++y){	
				//Inside Row - First Pixel
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStridem1,
													   srcImageDataPtr               ,srcImageDataPtr               ,srcImageDataPtr+1              ,
													   srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStridep1);
				++dstImageDataPtr;
				++srcImageDataPtr;
				//Inside Row - Inside Pixels
				for(x=1; x<srcImageWidthm1; ++x){
					AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStridep1,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStridem1,
														   srcImageDataPtr-1               ,srcImageDataPtr               ,srcImageDataPtr+1              ,
														   srcImageDataPtr+srcImageStridem1,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStridep1);
					++dstImageDataPtr;
					++srcImageDataPtr;
				}
				++dstImageDataPtr;
				++srcImageDataPtr;
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
				srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
			}
		}else if((srcImage.hasXbeginSection()==false)&&(srcImage.hasXendSection()==true)){
			for(y=1; y<srcImageHeightm1; ++y){	
				++dstImageDataPtr;
				++srcImageDataPtr;
				//Inside Row - Inside Pixels
				for(x=1; x<srcImageWidthm1; ++x){
					AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStridep1,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStridem1,
														   srcImageDataPtr-1               ,srcImageDataPtr               ,srcImageDataPtr+1              ,
														   srcImageDataPtr+srcImageStridem1,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStridep1);
					++dstImageDataPtr;
					++srcImageDataPtr;
				}
				//Inside Row - Last Pixel
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStridep1,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStride,
													   srcImageDataPtr-1               ,srcImageDataPtr               ,srcImageDataPtr              ,
													   srcImageDataPtr+srcImageStridem1,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStride);
				++dstImageDataPtr;
				++srcImageDataPtr;
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
				srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
			}
		}else{
			for(y=1; y<srcImageHeightm1; ++y){	
				//Inside Row - First Pixel
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStridem1,
													   srcImageDataPtr               ,srcImageDataPtr               ,srcImageDataPtr+1              ,
													   srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStridep1);
				++dstImageDataPtr;
				++srcImageDataPtr;
				//Inside Row - Inside Pixels
				for(x=1; x<srcImageWidthm1; ++x){
					AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStridep1,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStridem1,
														   srcImageDataPtr-1               ,srcImageDataPtr               ,srcImageDataPtr+1              ,
														   srcImageDataPtr+srcImageStridem1,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStridep1);
					++dstImageDataPtr;
					++srcImageDataPtr;
				}
				//Inside Row - Last Pixel
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStridep1,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStride,
													   srcImageDataPtr-1               ,srcImageDataPtr               ,srcImageDataPtr              ,
													   srcImageDataPtr+srcImageStridem1,srcImageDataPtr+srcImageStride,srcImageDataPtr+srcImageStride);
				++dstImageDataPtr;
				++srcImageDataPtr;
				dstImageDataPtr+=dstImage.getNumPixelsBetweenRows();
				srcImageDataPtr+=srcImage.getNumPixelsBetweenRows();
			}
		}

		if(srcImage.hasYendSection()==true){
			if(srcImage.hasXbeginSection()==true){
				//Last Row - First pixel
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStridem1,
														srcImageDataPtr              ,srcImageDataPtr               ,srcImageDataPtr+1               ,
														srcImageDataPtr              ,srcImageDataPtr               ,srcImageDataPtr+1               );
			}
			++dstImageDataPtr;
			++srcImageDataPtr;
		
			//Last Row - Inside Pixels
			for (x=1; x<srcImageWidthm1; ++x){
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStridep1,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStridem1,
													   srcImageDataPtr-1               ,srcImageDataPtr              ,srcImageDataPtr+1               ,
													   srcImageDataPtr-1               ,srcImageDataPtr              ,srcImageDataPtr+1               );
				++dstImageDataPtr;
				++srcImageDataPtr;
			}

			if(srcImage.hasXendSection()==true){
				//Last Row - Last Pixel
				AlgorithmType::process(dstImageDataPtr,srcImageDataPtr-srcImageStridep1,srcImageDataPtr-srcImageStride,srcImageDataPtr-srcImageStride,
													   srcImageDataPtr-1               ,srcImageDataPtr              ,srcImageDataPtr              ,
													   srcImageDataPtr-1               ,srcImageDataPtr              ,srcImageDataPtr              );
			}
		}
	}
}

}

#endif
