
#ifndef AAL_QT__AAL_Qt_H
#define AAL_QT__AAL_Qt_H

#include <ACore.h>

#ifdef BUILD_DLL
	#ifdef AAL_QT_BUILD
		#define AAL_QT_DLL_EXPORT __declspec(dllexport)
	#else
		#define AAL_QT_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AAL_QT_DLL_EXPORT
#endif

#endif
