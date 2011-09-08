
#ifndef [!output PROJECT_MACRO_NAME]__[!output PROJECT_NAME]_H
#define [!output PROJECT_MACRO_NAME]__[!output PROJECT_NAME]_H

#ifdef BUILD_DLL
	#ifdef [!output PROJECT_MACRO_NAME]_BUILD
		#define [!output PROJECT_MACRO_NAME]_DLL_EXPORT __declspec(dllexport)
	#else
		#define [!output PROJECT_MACRO_NAME]_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define [!output PROJECT_MACRO_NAME]_DLL_EXPORT
#endif

#endif
