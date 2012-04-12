
#include "Image_png.h"
#include <Image/Image.h>
#include <Pixel/pixel_cast.h>
#include <png.h>

#pragma warning( disable : 4244 ) //Note: Disable warning for possible conversion loss when going to RGBAi1 ... this should however be handled directly by pixel_cast

namespace Image {

namespace IO {

template<typename PixelType> AIL_PNG_DLL_EXPORT Image<PixelType> readPNG(Data::DataManager * const dataManager,const std::string & fileName) {
	
	//TODO:! change the error returns so that they free row_pointers and report an actual error

	Image<PixelType> ailImage(0,0,dataManager);

	int width, height;
	png_byte color_type;
	png_byte bit_depth;

	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep * row_pointers;

	// ----------------- start libPNG block ---------------------------------------
	char header[8];

    FILE * fp = nullptr;
	if(fopen_s(&fp,fileName.c_str(), "rb") !=0){
		return ailImage; //TODO: ERROR: File could not be opened for reading
	}
    fread(header, 1, 8, fp);
    if (png_sig_cmp(reinterpret_cast<png_const_bytep>(header), 0, 8)){
		return ailImage; //TODO: ERROR: File is not recognized as a PNG file
	}

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr){
		return ailImage; //TODO: ERROR: png_create_read_struct failed
	}

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr){
		return ailImage; //TODO: ERROR: png_create_info_struct failed
	}

    if (setjmp(png_jmpbuf(png_ptr))){
		return ailImage; //TODO: ERROR: Error during init_io
	}

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr))){
		return ailImage; //TODO: ERROR: Error during read_image
	}

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (int y=0; y<height; y++){
		row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
	}

    png_read_image(png_ptr, row_pointers);

    fclose(fp);
	// ------------------- end libPNG block ---------------------------------------

	if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_GRAY){
		ailImage = Image<PixelType>(width,height);
		auto imageDataPtr = ailImage.getDataPtr();
		for (long y=0; y<ailImage.getHeight(); ++y){ // TODO: Move this to Algorithm and make a straight copy when in the right color space
			png_byte* row = row_pointers[y];
			for (long x=0; x<ailImage.getWidth(); ++x){
				(*imageDataPtr)=Pixel::pixel_cast<PixelType>(Pixel::PixelGRAYi1u(row[x]));
				++imageDataPtr;
			}
		}
	}else if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB){
		ailImage = Image<PixelType>(width,height);
		auto imageDataPtr = ailImage.getDataPtr();
		for (long y=0; y<ailImage.getHeight(); ++y){ // TODO: Move this to Algorithm and make a straight copy when in the right color space
			png_byte* row = row_pointers[y];
			for (long x=0; x<ailImage.getWidth(); ++x){
				png_byte * ptr = &(row[x*3]);
				(*imageDataPtr)=Pixel::pixel_cast<PixelType>(Pixel::PixelRGBi1u(ptr[0], ptr[1], ptr[2]));
				++imageDataPtr;
			}
		}
	}else if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGBA){
		ailImage = Image<PixelType>(width,height);
		auto imageDataPtr = ailImage.getDataPtr();
		for (long y=0; y<ailImage.getHeight(); ++y){ // TODO: Move this to Algorithm and make a straight copy when in the right color space
			png_byte* row = row_pointers[y];
			for (long x=0; x<ailImage.getWidth(); ++x){
				png_byte * ptr = &(row[x*4]);
				//Pixel::PixelRGBAi1u pix(ptr[0], ptr[1], ptr[2], ptr[3]); //TODO: Add alpha support
				Pixel::PixelRGBi1u pix(ptr[0], ptr[1], ptr[2]);
				(*imageDataPtr)=Pixel::pixel_cast<PixelType>(pix);
				++imageDataPtr;
			}
		}
	}else{
		//Unsupported color type
		ailImage = Image<PixelType>(0,0);
	}

	// ----------------- start libPNG block ---------------------------------------
	for(int y=0; y<height; y++){
		free(row_pointers[y]);
	}
	free(row_pointers);
	// ------------------- end libPNG block ---------------------------------------

	return ailImage;
}

template<typename PixelType> AIL_PNG_DLL_EXPORT void writePNG(const Image<PixelType> & image,const std::string & fileName) {
	
	//TODO:! change the error returns so that they free row_pointers and report an actual error

	// ----------------- start libPNG block ---------------------------------------
	int width =image.getWidth();
	int height=image.getHeight();
	png_byte color_type=PNG_COLOR_TYPE_RGBA; //TODO: Add proper support for alpha channel and other color spaces
	png_byte bit_depth=8;
	
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep * row_pointers;

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr){
		return ; //TODO: ERROR: png_create_write_struct failed
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr){
		return ; //TODO: ERROR: png_create_info_struct failed
	}

	png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (int y=0; y<height; y++){
		row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
	}
	// ----------------- end libPNG block ---------------------------------------

	const PixelType * imageDataPtr = image.getDataPtr();
	for (long y=0; y<image.getHeight(); ++y){ // TODO: Move this to Algorithm and make a straight copy when in the right color space
		png_byte* row = row_pointers[y];
		for (long x=0; x<image.getWidth(); ++x){
			png_byte* ptr = &(row[x*4]);
			Pixel::PixelRGBf8 pix = Pixel::pixel_cast<Pixel::PixelRGBf8>(*imageDataPtr); //TODO: fix this so that it uses PixelRGBAi1u directly overlayed with ptr
			ptr[0]=pix.getR()*255.0;
			ptr[1]=pix.getG()*255.0;
			ptr[2]=pix.getB()*255.0;
			ptr[3]=255;
			++imageDataPtr;
		}
	}

	// ----------------- start libPNG block ---------------------------------------
	FILE * fp = nullptr;
	if(fopen_s(&fp,fileName.c_str(), "wb") !=0){
		return ; //TODO: ERROR: File could not be opened for writing
	}

	if (setjmp(png_jmpbuf(png_ptr))){
		return ; //TODO: ERROR: Error during init_io
	}

	png_init_io(png_ptr, fp);

	// write header
	if (setjmp(png_jmpbuf(png_ptr))){
		return ; //TODO: ERROR: Error during writing header
	}

	png_write_info(png_ptr, info_ptr);

	// write bytes
	if (setjmp(png_jmpbuf(png_ptr))){
		return ; //TODO: ERROR: Error during writing bytes
	}

	png_write_image(png_ptr, row_pointers);
	// end write

	if (setjmp(png_jmpbuf(png_ptr))){
		return ; //TODO: ERROR: Error during end of write
	}

	png_write_end(png_ptr, NULL);

	for(int y=0; y<height; y++){
		free(row_pointers[y]);
	}
	free(row_pointers);

	fclose(fp);
	// ------------------- end libPNG block ---------------------------------------
	
}

}

}

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_RETURN
#define FUNCTION_RETURN AIL_PNG_DLL_EXPORT Image::Image
#define FUNCTION_NAME Image::IO::readPNG
#define FUNCTION_SIGNATURE (Data::DataManager * const dataManager,const std::string & fileName)

#include <Pixel/PixelFunctionTemplateMacro.h>
//-------------------------------------------------------

//-------------------------------------------------------
#define FUNCTION_TEMPLATE_ARGUMENT_1
#define FUNCTION_RETURN AIL_PNG_DLL_EXPORT void
#define FUNCTION_NAME Image::IO::writePNG
#define FUNCTION_SIGNATURE_1 (const Image
#define FUNCTION_SIGNATURE_2 & image,const std::string & fileName)

#include <Pixel/PixelFunctionTemplateMacro.h>
//-------------------------------------------------------

