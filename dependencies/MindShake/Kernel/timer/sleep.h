#pragma once

#include <stdint.h>

//-------------------------------------
namespace MindShake
{

    void SleepMillis(uint32_t _millis);
    
    inline void SleepMillis(int32_t _millis)           { SleepMillis(uint32_t(_millis));             }

    inline void SleepSeconds(double  _seconds)         { SleepMillis(uint32_t(_seconds * 1000.0));   }
    inline void SleepSeconds(float   _seconds)         { SleepMillis(uint32_t(_seconds * 1000.0));   }
    inline void SleepSeconds(int32_t _seconds)         { SleepMillis(uint32_t(_seconds * 1000.0));   }

} // end of namespace
