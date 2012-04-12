
#ifndef AIL_FFMPEG__AIL_ffmpeg_H
#define AIL_FFMPEG__AIL_ffmpeg_H

#ifdef BUILD_DLL
	#ifdef AIL_FFMPEG_BUILD
		#define AIL_FFMPEG_DLL_EXPORT __declspec(dllexport)
	#else
		#define AIL_FFMPEG_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AIL_FFMPEG_DLL_EXPORT
#endif

#endif
