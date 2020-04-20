#pragma once

#include <stdio.h>

#if defined(_WIN32)
	#define snprintf	_snprintf

	#if !defined(vsnprintf) && !defined(NO_vsnprintf)
		#define vsnprintf	_vsnprintf
	#endif
#endif
