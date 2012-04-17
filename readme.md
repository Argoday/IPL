# Argoday Library
[Wiki](http://www.argoday.com/wiki/ALIB "Argoday Wiki")

## Overview

Argoday Library (ALIB) contains lots of functionality in seperate modules:

### Exe
* ImageConvert - Calls AIL_IO to convert image files
* FrameDump - Calls ffmpeg to dump frames from a video file
* QPaint - Qt based paint program to test AIL functionality

### Lib
* ACore - Argoday Core Library
  * Basic helper functionality
* AIL - Argoday Image Library
  * A template metaprogramming based image library
* AIL_<Name> - Argoday Image Library Extension
  * Adds support for AIL to interact with library <Name>
* AIO_<Name> - Argoday Input / Output Extension
  * Adds support for ALIB to input / output format <Name>
* Crypt - Cryptrography Library
  * Library of various cryptrography ciphers

## Dependencies

ALIB compiles using MSVC 2011 Beta and relies on:

Qt - qt-everywhere-opensource-src-4.7.3  
Curl - curl-7.21.7  
LibPNG - lpng1510  
FFMPEG - ffmpeg-git-41a097a-win64-dev  

## License

Copyright (c) 2012 argoday@argoday.com

Argoday Library is licensed under the "Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)" license, see http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode
