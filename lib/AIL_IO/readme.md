# AIL_IO - Image Input/Output

## Example Usage

### Read an Image from a file
Data::DataManager dataManager;  
std::string fromFileName = "foo.jpg";  
auto image = Image::IO::read\<Pixel::PixelRGBi1u\>(&dataManager,fromFileName);

### Write an Image to a file
std::string toFileName = "bar.jpg";  
Image::IO::write(image,toFileName);

## Example Program
See ./exe/ImageConvert

## Dependencies

./lib/AIL  
./lib/AIL_Qt  
./lib/AIL_IO  
