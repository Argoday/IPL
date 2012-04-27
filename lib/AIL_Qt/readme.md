# AIL_Qt - Image Library integration with Qt

## Example Usage

### Convert from a QImage
Data::DataManager dataManager;  
QImage qImage;
auto image = Image::Convert::fromQt\<Pixel::PixelRGBi1u\>(&dataManager,qImage);  

### Convert to a QImage
Image::Image\<Pixel::PixelRGBi1u\> image;  
QImage image = Image::Convert::toQt(image);  

### Read a QImage from a file
std::string fromFileName = "foo.bmp";  
QImage image = Image::IO::readQt(fromFileName);  

### Write a QImage to a file
std::string toFileName = "bar.jpg";  
QImage image;  
Image::IO::writeQt(image,toFileName);

## Example Program
See ./lib/AIL_IO and ./exe/ImageConvert

## Dependencies

./lib/AIL  
