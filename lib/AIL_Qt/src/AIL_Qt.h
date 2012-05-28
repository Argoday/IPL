
#ifndef AIL_QT__AIL_Qt_H
#define AIL_QT__AIL_Qt_H

#include <ACore.h>

#ifdef BUILD_DLL
	#ifdef AIL_QT_BUILD
		#define AIL_QT_DLL_EXPORT __declspec(dllexport)
	#else
		#define AIL_QT_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AIL_QT_DLL_EXPORT
#endif

#endif
