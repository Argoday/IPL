
#ifndef AML_FFMPEG__AML_ffmpeg_H
#define AML_FFMPEG__AML_ffmpeg_H

#include <ACore.h>

#ifdef BUILD_DLL
	#ifdef AML_FFMPEG_BUILD
		#define AML_FFMPEG_DLL_EXPORT __declspec(dllexport)
	#else
		#define AML_FFMPEG_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AML_FFMPEG_DLL_EXPORT
#endif

#endif
