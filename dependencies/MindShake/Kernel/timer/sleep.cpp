#include "sleep.h"
#include <Common/Core/platform.h>
#include <stdio.h>
//-------------------------------------
#if defined(TARGET_PLATFORM_WINDOWS)
    #define WIN32_LEAN_AND_MEAN 1
    #include <Windows.h>
#else
    #include <time.h>
    #include <sys/types.h>
    #include <sys/errno.h>
#endif

#if defined(TARGET_PLATFORM_MACOSX)
    #include <libkern/OSTypes.h>
    #include <Carbon/Carbon.h>
#endif

//-------------------------------------
// TARGET_PLATFORM_IPHONE code is in sleep.mm
#if !defined(TARGET_PLATFORM_IPHONE)

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    void
    SleepMillis(uint32_t _millis)
    {
        #if defined(_WIN32)
            ::SleepEx(_millis, true);

        #elif defined(TARGET_PLATFORM_IPHONE)
            // This code is in sleep.mm

        #elif defined(TARGET_PLATFORM_MACOSX)
            uint64_t    counter;
            uint64_t    finish;

            Microseconds((UnsignedWide *) &counter);
            finish = counter + uint64_t(_millis * 1000);
            while(counter < finish)
                Microseconds((UnsignedWide *) &counter);
        #else
            timespec timeOut;
            timeOut.tv_sec  = static_cast<time_t>(_millis / 1000);
            timeOut.tv_nsec = static_cast<long>(_millis % 1000) * 1e+6;

            timespec timeRemaining;
            while (true)
            {
                int ret = ::nanosleep(&timeOut, &timeRemaining);
                if (ret == -1 && errno == EINTR)
                {
                    timeOut.tv_sec  = timeRemaining.tv_sec;
                    timeOut.tv_nsec = timeRemaining.tv_nsec;
                }
                else
                {
                    return;
                }
            }
        #endif
    }

} // end of namespace

#endif
