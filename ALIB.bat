
setlocal & pushd

set PKG=%CD%\..\..\pkg
set QTDIR=%PKG%\qt-everywhere-opensource-src-4.7.3
set BOOST_DIR=%PKG%\boost_1_40_0
set CURL_DIR=%PKG%\curl-7.21.7

set ALIB=%CD%

start "C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE\devenv.exe" %CD%/ALIB.sln /useenv

popd & endlocal
