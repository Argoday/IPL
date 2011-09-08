
#ifndef AIO_JSON__AIO_json_H
#define AIO_JSON__AIO_json_H

#ifdef BUILD_DLL
	#ifdef AIO_JSON_BUILD
		#define AIO_JSON_DLL_EXPORT __declspec(dllexport)
	#else
		#define AIO_JSON_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define AIO_JSON_DLL_EXPORT
#endif

#endif
