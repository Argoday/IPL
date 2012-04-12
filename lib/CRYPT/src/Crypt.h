
#ifndef CRYPT__Crypt_H
#define CRYPT__Crypt_H

#ifdef BUILD_DLL
	#ifdef CRYPT_BUILD
		#define CRYPT_DLL_EXPORT __declspec(dllexport)
	#else
		#define CRYPT_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define CRYPT_DLL_EXPORT
#endif

#endif
