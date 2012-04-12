
#ifndef ACORE__ACore_H
#define ACORE__ACore_H

#ifdef BUILD_DLL
	#ifdef ACORE_BUILD
		#define ACORE_DLL_EXPORT __declspec(dllexport)
	#else
		#define ACORE_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define ACORE_DLL_EXPORT
#endif

#endif
