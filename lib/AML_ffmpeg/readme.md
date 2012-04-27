# AML_ffmpeg - Media Library Integration with FFMPEG

## Contents

### FFMPEGmediaPlayerAgent
A threaded Agent that:  
- Listens to a PlayerControl queue (see ./lib/AML)  
- Reads media files using FFMPEG  
- Outputs video onto a Video::Pipe (see ./lib/AVL)  
- Outputs audio onto a Audio::Pipe (see ./lib/AAL)  

## Example Usage
See ./exe/MediaPlayer and ./lib/AML_Qt

## Dependencies

./lib/AIL  
./lib/AAL  
./lib/AVL  
./lib/AML  
