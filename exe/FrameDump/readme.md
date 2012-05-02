# FrameDump

## CLI

Takes a video file and spits out its frames into the local directory.  This is a testbed for AVL_ffmpeg and supports whatever video files FFMPEG can read and whatever image formats AIL_IO can write.

./FrameDump.exe \<SourceMovieName\> \<DestImageType\>

Example:  
./FrameDump.exe A.mpg png  

Expected Output:  
./000001.png  
./000002.png  
./000003.png  
...  
...  


## Dependencies

./lib/AIL_IO  
./lib/AVL_ffmpeg
