#pragma once

//-------------------------------------
#include <string.h>
//-------------------------------------

#if defined(__APPLE__)
    #define stricmp     strcasecmp
    #define strnicmp    strncasecmp
#endif

#if defined(__MINGW32__)
    #define stricmp     strcasecmp
    #define strnicmp    strncasecmp
#endif

#if defined(linux) || defined(__linux__) || defined(ANDROID) || defined(__ANDROID__)
    #define stricmp     strcasecmp
    #define strnicmp    strncasecmp
#endif

#if defined(_MSC_VER)
    #define stricmp     _stricmp
    #define strnicmp    _strnicmp
    #define strupr(str) _strupr(str)
    #define strlwr(str) _strlwr(str)

    #if !defined(strdup)
        #define strdup  _strdup
    #endif
#endif

#if defined(__BORLANDC__)
#endif
