
#ifndef AIL_PNG__AIL_png_H
#define AIL_PNG__AIL_png_H

#include <ACore.h>

#ifdef BUILD_DLL
	#ifdef AIL_PNG_BUILD
		#define AIL_PNG_DLL_EXPORT __declspec(dllexport)
	#else
		#define AIL_PNG_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AIL_PNG_DLL_EXPORT
#endif

#endif
//$(LIBPNG_DIR)\projects\vstudio\x64\Release-Library
//libpng15.lib;zlib.lib;