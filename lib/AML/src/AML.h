
#ifndef AML__AML_H
#define AML__AML_H

#include <ACore.h>

#ifdef BUILD_DLL
	#ifdef AML_BUILD
		#define AML_DLL_EXPORT __declspec(dllexport)
	#else
		#define AML_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AML_DLL_EXPORT
#endif

#endif
