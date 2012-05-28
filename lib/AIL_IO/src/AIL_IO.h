
#ifndef AIL_IO__AIL_IO_H
#define AIL_IO__AIL_IO_H

#include <ACore.h>

#ifdef BUILD_DLL
	#ifdef AIL_IO_BUILD
		#define AIL_IO_DLL_EXPORT __declspec(dllexport)
	#else
		#define AIL_IO_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AIL_IO_DLL_EXPORT
#endif

#endif
//$(LIBPNG_DIR)\projects\vstudio\x64\Release-Library
//libpng15.lib;zlib.lib;