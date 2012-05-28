
#include "Time.h"

#include <Windows.h>

namespace Time {

F8 ACORE_DLL_EXPORT getTime(){
	LARGE_INTEGER pc;
	QueryPerformanceCounter(&pc);
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return static_cast<F8>(pc.QuadPart) / static_cast<F8>(freq.QuadPart);
}

}