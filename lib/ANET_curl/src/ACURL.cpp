
#include "ACURL.h"

namespace ACURL {

size_t write_data(void *ptr, size_t size, size_t nmemb, void *headers) {
	static_cast<HeaderStruct *>(headers)->memory.push_back(std::string((const char *)ptr,size*nmemb));
	return size*nmemb;
}

size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data){
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	char * tempPtr = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (tempPtr == NULL) {
		//std::cout<<"not enough memory (realloc returned NULL)\n"; //TODO: Workout generic error reporting solution
		exit(EXIT_FAILURE);
	}
	mem->memory = tempPtr;

	memcpy(&(mem->memory[mem->size]), ptr, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

}
