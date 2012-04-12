
#ifndef ANET_CURL__ACURL_H
#define ANET_CURL__ACURL_H

#include "ANET_curl.h"
#include <vector>

#pragma warning( disable : 4251 ) //TODO: Leverage light-weight Vector class from ACore to remove using std::string across DLL boundries

namespace ACURL {

struct ANET_CURL_DLL_EXPORT MemoryStruct {
	char *memory;
	size_t size;
};
struct ANET_CURL_DLL_EXPORT HeaderStruct {
	std::vector<std::string> memory;
};

size_t ANET_CURL_DLL_EXPORT write_data(void *ptr, size_t size, size_t nmemb, void *headers);
size_t ANET_CURL_DLL_EXPORT WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);

}

#endif
