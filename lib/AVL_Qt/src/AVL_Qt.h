
#ifndef AVL_QT__AVL_Qt_H
#define AVL_QT__AVL_Qt_H

#ifdef BUILD_DLL
	#ifdef AVL_QT_BUILD
		#define AVL_QT_DLL_EXPORT __declspec(dllexport)
	#else
		#define AVL_QT_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AVL_QT_DLL_EXPORT
#endif

#endif
