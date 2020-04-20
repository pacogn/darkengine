#include "sleep.h"
#include <Common/Core/platform.h>

#if defined(TARGET_PLATFORM_IPHONE)

#import <Foundation/NSThread.h>

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    void
    SleepMillis(uint32_t _millis)
    {
        [NSThread sleepForTimeInterval:(_millis / 1000.0)];
    }

} // end of namespace

#endif
