#pragma once

// Find the active platform
//-------------------------------------
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
    #define TARGET_PLATFORM_WINDOWS

#elif defined(ANDROID) || defined(__ANDROID__)
    #define TARGET_PLATFORM_ANDROID

#elif defined(__linux__)
    #define TARGET_PLATFORM_LINUX

#elif defined(__APPLE__)
    #include <TargetConditionals.h>

    #if (TARGET_OS_IPHONE != 1) && (TARGET_OS_EMBEDDED == 0)
        #define TARGET_PLATFORM_MACOSX
    #else
        #if (TARGET_IPHONE_SIMULATOR == 1) && (TARGET_OS_EMBEDDED == 0)
            #define TARGET_PLATFORM_IPHONE
            #define TARGET_PLATFORM_IPHONE_SIMULATOR
        #endif

        #if (TARGET_OS_IPHONE == 1) && (TARGET_OS_EMBEDDED == 1)
            #define TARGET_PLATFORM_IPHONE
        #endif
#endif

#endif

#if (__cplusplus > 199711L) || (defined(_MSC_VER) && (_MSC_VER >= 1700))
    #define kDefinedCplusplus11
#endif
