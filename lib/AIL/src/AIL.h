
#ifndef AIL__AIL_H
#define AIL__AIL_H

#ifdef BUILD_DLL
	#ifdef AIL_BUILD
		#define AIL_DLL_EXPORT __declspec(dllexport)
	#else
		#define AIL_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AIL_DLL_EXPORT
#endif

#endif
