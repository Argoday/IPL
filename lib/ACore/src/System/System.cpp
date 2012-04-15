
#include "System.h"

#include <windows.h>

I4u getPageSize(){
	SYSTEM_INFO si;
	GetSystemInfo(&si);
 
	return si.dwPageSize;
}
