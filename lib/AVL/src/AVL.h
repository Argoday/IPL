
#ifndef AVL__AVL_H
#define AVL__AVL_H

#ifdef BUILD_DLL
	#ifdef AVL_BUILD
		#define AVL_DLL_EXPORT __declspec(dllexport)
	#else
		#define AVL_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AVL_DLL_EXPORT
#endif

#endif
