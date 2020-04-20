#pragma once

#include <Common/Core/platform.h>

#if defined(kDefinedCplusplus11)

#define kUSE_CChronoTimer

#include <stdint.h>
#include <chrono>

#if defined(kPreferMonotonicTimer) && (kPreferMonotonicTimer == 1)
    #define kClock      steady_clock
#else
    #define kClock      high_resolution_clock
#endif

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    class CChronoTimer
    {
        public:
                        CChronoTimer();

            void        Reset();

            double      GetTime()                                       { return GetTimeCounter()  * mResolution;   }
            double      GetDelta()                                      { return GetDeltaCounter() * mResolution;   }

            uint64_t    GetTimeCounter();
            uint64_t    GetDeltaCounter();

            double      ConvertCounterToTime(int64_t _counter) const    { return _counter * mResolution;            }

            double      GetFrequency() const                            { return mFrequency;                        }
            double      GetResolution() const                           { return mResolution;                       }

        public:
            static void WaitSeconds(double _seconds);
            static void WaitMillis(uint32_t _millis);

        protected:
            typedef std::chrono::kClock     Timer;

            Timer::time_point   mStartTime;
            Timer::time_point   mDeltaCounter;
            double              mFrequency;
            double              mResolution;
            Timer::duration     mTime;
    };

} // end of namespace

#endif
