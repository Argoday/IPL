
#ifndef ANET_CURL__ANET_curl_H
#define ANET_CURL__ANET_curl_H

#ifdef BUILD_DLL
	#ifdef ANET_CURL_BUILD
		#define ANET_CURL_DLL_EXPORT __declspec(dllexport)
	#else
		#define ANET_CURL_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define ANET_CURL_DLL_EXPORT
#endif

#endif
