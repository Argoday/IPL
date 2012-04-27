# AIL_PNG - Image Input/Output for format LibPNG

## Example Usage

### Read an Image from a file
Data::DataManager dataManager;  
std::string fromFileName = "foo.png";  
auto image = Image::IO::readPNG\<Pixel::PixelRGBi1u\>(&dataManager,fromFileName);

### Write an Image to a file
std::string toFileName = "bar.png";  
Image::IO::writePNG(image,toFileName);

## Example Program
See ./lib/AIL_IO and ./exe/ImageConvert

## Dependencies

./lib/AIL  
