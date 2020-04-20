#pragma once

#include <cstdint>

//-------------------------------------
namespace MindShake {

	//---------------------------------
	struct FastRand2 {
        static uint32_t mSeed;

        inline static int Rand(uint32_t _seed = 0) { 
            if(_seed != 0) 
                mSeed = _seed;

            mSeed = (214013 * mSeed + 2531011); 
            return (mSeed >> 16) & 0x7fff; 
        } 

        inline static int32_t GetRandom(int32_t _max) {
            if(_max != 0)
                return Rand() % _max;
            
            return 0;
        }

        inline static int32_t GetRandom(int32_t _min, int32_t _max) {
            if((_max - _min + 1) != 0)
                return (Rand() % (_max - _min + 1)) + _min;

            return 0;
        }

        inline static float	GetRandom(float _min, float _max) {
            return (UnitRandom() * (_max - _min)) + _min;
        }

        inline static float UnitRandom() {
            return Rand() * (1.0f / float(0x7fff));
        }
	};

} // end of namespace