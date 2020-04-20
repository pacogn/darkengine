#include "CChronoTimer.h"

#if defined(kUSE_CChronoTimer)

#include <Kernel/timer/sleep.h>

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    CChronoTimer::CChronoTimer()
    {
        mFrequency  = 1e+9;
        mResolution = 1.0 / mFrequency;
        Reset();
    }

    //---------------------------------
    void
    CChronoTimer::Reset()
    {
        mStartTime    = Timer::now();
        mDeltaCounter = mStartTime;
        mTime         = std::chrono::seconds(0);
    }

    //---------------------------------
    uint64_t
    CChronoTimer::GetTimeCounter()
    {
        Timer::time_point   counter;

        counter    = Timer::now();
        mTime     += (counter - mStartTime);
        mStartTime = counter;

        return std::chrono::duration_cast<std::chrono::nanoseconds>(mTime).count();
    }

    //---------------------------------
    uint64_t
    CChronoTimer::GetDeltaCounter()
    {
        Timer::time_point   counter;
        Timer::duration     delta;

        counter = Timer::now();
        delta = (counter - mDeltaCounter);
        mDeltaCounter = counter;

        return std::chrono::duration_cast<std::chrono::nanoseconds>(delta).count();
    }

    //---------------------------------
    void
    CChronoTimer::WaitSeconds(double _seconds)
    {
        SleepSeconds(_seconds);
    }

    //---------------------------------
    void
    CChronoTimer::WaitMillis(uint32_t _millis)
    {
        SleepMillis(_millis);
    }

} // end of namespace

#endif
