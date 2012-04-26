
setlocal & pushd

set PKG=%CD%\..\..\pkg
set QTDIR=%PKG%\qt-everywhere-opensource-src-4.7.3
set CURL_DIR=%PKG%\curl-7.21.7
set LIBPNG_DIR=%PKG%\lpng1510
set LIBFFMPEG_DIR=%PKG%\ffmpeg-git-41a097a-win64-dev

set ALIB=%CD%

start "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE\devenv.exe" %CD%/ALIB.sln /useenv

popd & endlocal
