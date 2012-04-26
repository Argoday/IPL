# Argoday Library
[Wiki](http://www.argoday.com/wiki/ALIB "Argoday Wiki")

## Overview

Argoday Library (ALIB) contains lots of functionality in seperate modules:

### Lib
* ACore - Argoday Core Library
  * Basic helper functionality
* AIL - Argoday Image Library
  * A template metaprogramming based Image library
* AAL - Argoday Audio Library
  * A library to work with Audio
* AVL - Argoday Video Library
  * A library to work with Video
* AML - Argoday Media Library
  * A library to work with Media (Audio and Video)
* \<AName\>_\<Name\> - Library Extension
  * Adds support for \<AName\> to interact with library \<Name\>

### Exe
* ImageConvert - Calls AIL_IO to convert image files
* FrameDump - Calls AML_ffmpeg to dump frames from a video file
* MediaPlayer - Uses AML_ffmpeg to decode video and uses AML_Qt for display
* QPaint - Qt based paint program to test AIL functionality


## Dependencies

ALIB compiles using MSVC 2011 Beta and relies on:

Qt - qt-everywhere-opensource-src-4.7.3  
LibPNG - lpng1510  
FFMPEG - ffmpeg-git-41a097a-win64-dev  

## License

Copyright (c) 2012 argoday@argoday.com

Argoday Library is licensed under the "Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)" license, see http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode
