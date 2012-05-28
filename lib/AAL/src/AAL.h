
#ifndef AAL__AAL_H
#define AAL__AAL_H

#include <ACore.h>

#ifdef BUILD_DLL
	#ifdef AAL_BUILD
		#define AAL_DLL_EXPORT __declspec(dllexport)
	#else
		#define AAL_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AAL_DLL_EXPORT
#endif

#endif
