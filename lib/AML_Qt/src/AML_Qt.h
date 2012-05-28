
#ifndef AML_QT__AML_Qt_H
#define AML_QT__AML_Qt_H

#include <ACore.h>

#ifdef BUILD_DLL
	#ifdef AML_QT_BUILD
		#define AML_QT_DLL_EXPORT __declspec(dllexport)
	#else
		#define AML_QT_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AML_QT_DLL_EXPORT
#endif

#endif
