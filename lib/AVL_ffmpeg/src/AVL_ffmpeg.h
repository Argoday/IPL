
#ifndef AVL_FFMPEG__AVL_ffmpeg_H
#define AVL_FFMPEG__AVL_ffmpeg_H

#include <ACore.h>

#ifdef BUILD_DLL
	#ifdef AVL_FFMPEG_BUILD
		#define AVL_FFMPEG_DLL_EXPORT __declspec(dllexport)
	#else
		#define AVL_FFMPEG_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AVL_FFMPEG_DLL_EXPORT
#endif

#endif
