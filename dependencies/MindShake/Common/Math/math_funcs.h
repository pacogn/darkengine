#pragma once

//-------------------------------------
#include "constants.h"
//-------------------------------------
#include <cmath>
#include <type_traits>
//-------------------------------------

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    // Sign functions
    //---------------------------------

    //---------------------------------
    template <typename T>
    inline T        Abs(T _val)                             { return (_val < T(0)) ?  -_val :   _val; }

    //---------------------------------
    template <typename T>
    inline T        Sign(T _val)                            { return (_val > 0) ? T(1) : T(-1); }

    //---------------------------------
    template <typename T>
    inline bool     DifferentSign(T _val1, T _val2)         { return (_val1 * _val2 < T(0)) ? true : false; }


    //---------------------------------
    // Round functions
    //---------------------------------
#if defined(_MSC_VER) && (_MSC_VER < 1800)
    #define kTrunc(x)   ((x >  0) ? floor (x) : ceil(x))
    #define kTruncF(x)  ((x >  0) ? floorf(x) : ceilf(x))

    #define kRound(x)   ((x >= 0) ? floor (x + 0.5)  : ceil (x - 0.5))
    #define kRoundF(x)  ((x >= 0) ? floorf(x + 0.5f) : ceilf(x - 0.5f))
#else
    #define kTrunc(x)   trunc (x)
    #define kTruncF(x)  truncf(x)

    #define kRound(x)   round (x)
    #define kRoundF(x)  roundf(x)
#endif

    #define kExpand(x)  ((x >= 0) ? ceil (x) : floor (x))
    #define kExpandF(x) ((x >= 0) ? ceilf(x) : floorf(x))

    // floor:  Toward -INf (less or equal)
    // ceil:   Toward +INF (greater or equal)
    // expand: > 0 toward +INF | < 0 toward -INF
    // round:   To nearest integer
    // trunc:  Integer part
    // frac:   Fractional part

    // value   floor   ceil    expand   round   trunc   frac
    // -----   -----   -----   -----   -----   -----   -----
    //  2.3     2.0     3.0     3.0     2.0     2.0     0.3
    //  3.8     3.0     4.0     4.0     4.0     3.0     0.8
    //  5.5     5.0     6.0     6.0     6.0     5.0     0.5
    // -2.3    -3.0    -2.0    -3.0    -2.0    -2.0     0.3
    // -3.8    -4.0    -3.0    -4.0    -4.0    -3.0     0.8
    // -5.5    -6.0    -5.0    -6.0    -6.0    -5.0     0.5

    //---------------------------------
    inline float    Floor(float  _val)                      { return floorf(_val);      }
    inline double   Floor(double _val)                      { return floor (_val);      }

    inline float    Ceil(float  _val)                       { return ceilf(_val);       }
    inline double   Ceil(double _val)                       { return ceil (_val);       }

    inline float    Expand(float  _val)                     { return kExpandF(_val);    }
    inline double   Expand(double _val)                     { return kExpand (_val);    }

    inline float    Round(float  _val)                      { return kRoundF(_val);     }
    inline double   Round(double _val)                      { return kRound (_val);     }

    inline float    Trunc(float  _val)                      { return kTruncF(_val);     }
    inline double   Trunc(double _val)                      { return kTrunc (_val);     }

    template <typename T>
    inline T        Frac(T _v)                              { return Abs(_v - Trunc(_v));       }

    template<typename T>
    inline typename std::enable_if<std::is_integral<T>::value>::type 
    Mod(T _numer, T _denom)                                 { return _numer % _denom;           }
    inline float    Mod(float  _numer, float  _denom)       { return fmodf(_numer, _denom);     }
    inline double   Mod(double _numer, double _denom)       { return fmod (_numer, _denom);     }


    //---------------------------------
    // Circular Diff
    //---------------------------------

    template <typename T>
    inline typename std::enable_if<std::is_signed<T>::value, T>::type
    CircularDiff(T _v1, T _v2, size_t _max) {
        T       diff;
        size_t  halfMax;

        halfMax = _max >> 1;

        diff    = Mod(_v1 - _v2 + _max + halfMax, T(_max));
        diff   -= halfMax;

        return diff;
    }

    template <typename T>
    inline typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value, T>::type 
    CircularMod(T _val, size_t _max)     { 
        while(_val < 0) _val += _max; 

        return _val % _max; 
    }


    //---------------------------------
    // Compare / check functions
    //---------------------------------

    //---------------------------------
    inline bool     IsZero(float  _val, float  _eps=Float32::ZERO_EPSILON)                  { return ((_val  > -_eps) && (_val  < _eps)); }
    inline bool     IsZero(double _val, double _eps=Float64::ZERO_EPSILON)                  { return ((_val  > -_eps) && (_val  < _eps)); }

    //---------------------------------
    inline bool     IsNotZero(float  _val, float  _eps=Float32::ZERO_EPSILON)               { return ((_val <= -_eps) || (_val >= _eps)); }
    inline bool     IsNotZero(double _val, double _eps=Float64::ZERO_EPSILON)               { return ((_val <= -_eps) || (_val >= _eps)); }

    //---------------------------------
    inline bool     IsEqual(float  _v1, float  _v2, float  _eps=Float32::ZERO_EPSILON)      { return (Abs(_v2 - _v1) <= _eps) ? true : false; }
    inline bool     IsEqual(double _v1, double _v2, double _eps=Float64::ZERO_EPSILON)      { return (Abs(_v2 - _v1) <= _eps) ? true : false; }

    //---------------------------------
    inline bool     IsNotEqual(float  _v1, float  _v2, float  _eps=Float32::ZERO_EPSILON)   { return (Abs(_v2 - _v1) <= _eps) ? false : true; }
    inline bool     IsNotEqual(double _v1, double _v2, double _eps=Float64::ZERO_EPSILON)   { return (Abs(_v2 - _v1) <= _eps) ? false : true; }

    //---------------------------------
    template <typename T1, typename T2>
    inline auto     Min(const T1 &_A, const T2 &_B) -> decltype(_A + _B)    { return (_A <= _B) ? _A : _B; }

    template <typename T1, typename T2>
    inline auto     Max(const T1 &_A, const T2 &_B) -> decltype(_A + _B)    { return (_A >  _B) ? _A : _B; }

    //---------------------------------
    template <typename T>
    inline T        Clamp(T _val, T _min=T(0), T _max=T(1)) {
		if(_val < _min) return _min;
		if(_val > _max) return _max;

		return _val;
    }

    // std::isnan() is C99, not supported by all compilers
    // However NaN always fails this next test, no other number does.
    //---------------------------------
    template <typename T>
    inline bool     IsNaN(T _v)                             { return (_v != _v);        }

    //---------------------------------
    union FloatInt
    {
        int32_t	    i;
        float	    f;
    };
    inline bool     IsInf(float  _v) {
        FloatInt    aux;
		aux.f  = _v;
		return ((aux.i & 0x7f800000) == 0x7f800000);
    }

    union DoubleInt
    {
        uint64_t	i;
        double	    f;
    };
    inline bool     IsInf(double _v) {
        DoubleInt   aux;
		aux.f  = _v;
		return ((aux.i & 0x7ff0000000000000ULL) == 0x7ff0000000000000ULL);
    }


    //---------------------------------
    // Power functions
    //---------------------------------

    //---------------------------------
    template <typename T>
    inline T        Pow(T _val, uint32_t _power) {
		T res = T(1);

		while(_power != 0) {
			if(_power & 1)
				res *= _val;

			_val *= _val;
			_power >>= 1;
		}

		return res;
	}

    template <typename T>
    inline T        Pow(T _val, float _power)               { return powf(float(_val), _power); }

    template <typename T>
    inline T        Pow(T _val, double _power)              { return pow(double(_val), _power); }

    //---------------------------------
    template <typename T>
    inline T        Sqr(T _v)                               { return _v * _v;           }

    //---------------------------------
    inline float    Sqrt(float  _v)                         { return sqrtf(_v);         }
    inline double   Sqrt(double _v)                         { return sqrt (_v);         }

    //---------------------------------
    inline float    InvSqrt(float  _v)                      { return (_v > Float32::ZERO_EPSILON) ? 1.0f / sqrtf(_v) : 0.0f; }
    inline double   InvSqrt(double _v)                      { return (_v > Float64::ZERO_EPSILON) ? 1.0f / sqrt (_v) : 0.0f; }

    //---------------------------------
    inline float    FastInvSqrt(float _v) {
		float       y;
        FloatInt    tmp;

		if(IsZero(_v)) return 0.0f;

		tmp.f = _v;
		tmp.i = 0x5f3759df - (tmp.i >> 1);
		y	  = tmp.f;

		return y * (1.5f - 0.5f * _v * y * y);
	}

    //---------------------------------
    inline bool     IsInBase(int32_t _base, int32_t _number) {
		while(_number > _base) {
			if((_number % _base) != 0)
				return false;

			_number /= _base;
		}

		if(_number == 1)
			return true;

		return false;
	}

    // Fast power of two checking
    //---------------------------------
    inline bool     IsPowerOfTwo(const uint32_t _val)       { return ((_val & (_val-1)) == 0);  }

    // Gets closest power of two given a number
    //---------------------------------
    inline uint32_t   GetClosestPowerOfTwo(const uint32_t _val) {
		uint32_t result = 1;

		while(result < _val)
			result += result;

		if((_val << 2) < (result * 3))
			result >>= 1;

		return result;
	}

    //---------------------------------
    inline uint32_t   NextPowerOfTwo(uint32_t  _val) {
		_val = _val - 1;
		_val |= (_val >> 1);
		_val |= (_val >> 2);
		_val |= (_val >> 4);
		_val |= (_val >> 8);
		_val |= (_val >>16);

		return _val + 1;
	}

    //---------------------------------
    inline uint32_t   PriorPowerOfTwo(uint32_t _val) {
		_val |= (_val >> 1);
		_val |= (_val >> 2);
		_val |= (_val >> 4);
		_val |= (_val >> 8);
		_val |= (_val >>16);

		return _val - (_val >> 1);
	}


    //---------------------------------
    // Trigonometric functions
    //---------------------------------
    inline float    Cos(float  _v)                          { return cosf(_v);              }
    inline double   Cos(double _v)                          { return cos (_v);              }

    inline float    CosG(float  _v)                         { return cosf(_v * Float32::DEGTORAD);  }
    inline double   CosG(double _v)                         { return cos (_v * Float64::DEGTORAD);  }

    inline float    ACos(float  _v)                         { return acosf(_v);             }
    inline double   ACos(double _v)                         { return acos (_v);             }

    //---------------------------------
    inline float    Sin(float  _v)                          { return sinf(_v);              }
    inline double   Sin(double _v)                          { return sin (_v);              }

    inline float    SinG(float  _v)                         { return sinf(_v * Float32::DEGTORAD);  }
    inline double   SinG(double _v)                         { return sin (_v * Float64::DEGTORAD);  }

    inline float    ASin(float  _v)                         { return asinf(_v);             }
    inline double   ASin(double _v)                         { return asin (_v);             }

    //---------------------------------
    inline float    Tan(float  _v)                          { return tanf(_v);              }
    inline double   Tan(double _v)                          { return tan (_v);              }

    inline float    TanG(float  _v)                         { return tanf(_v * Float32::DEGTORAD);  }
    inline double   TanG(double _v)                         { return tan (_v * Float64::DEGTORAD);  }

    inline float    ATan(float  _v)                         { return atanf(_v);             }
    inline double   ATan(double _v)                         { return atan (_v);             }

    //---------------------------------
    inline float    ATan2(float  _y, float  _x)             { return atan2f(_y, _x);        }
    inline double   ATan2(double _y, double _x)             { return atan2 (_y, _x);        }

    //---------------------------------
	inline float
	Cotan(float _v) {
		float	t = tanf(_v);
		if(IsNotZero(t))
			return 1.0f / t;

		return Float32::POS_INFINITY;
	}

	inline double
	Cotan(double _v) {
		double	t = tan(_v);
		if(IsNotZero(t))
			return 1.0 / t;

		return Float64::POS_INFINITY;
	}

	inline float	CotanG(float  _v)						{ return Cotan(_v * Float32::DEGTORAD);	}
	inline double	CotanG(double _v)						{ return Cotan(_v * Float64::DEGTORAD);	}

    //---------------------------------
	inline float
	Sec(float _v) {
		float	c = cosf(_v);
		if(IsNotZero(c))
			return 1.0f / c;

		return Float32::POS_INFINITY;
	}

	inline double
	Sec(double _v) {
		double	c = cos(_v);
		if(IsNotZero(c))
			return 1.0 / c;

		return Float64::POS_INFINITY;
	}

	inline float	SecG(float	_v)							{ return Sec(_v * Float32::DEGTORAD);	}
	inline double	SecG(double _v)							{ return Sec(_v * Float64::DEGTORAD);	}

    //---------------------------------
	inline float
	Cosec(float _v) {
		float	s = sinf(_v);
		if(IsNotZero(s))
			return 1.0f / s;

		return Float32::POS_INFINITY;
	}

	inline double
	Cosec(double _v) {
		double	s = sin(_v);
		if(IsNotZero(s))
			return 1.0 / s;

		return Float64::POS_INFINITY;
	}

    inline float    CosecG(float  _v)                       { return Cosec(_v * Float32::DEGTORAD); }
    inline double   CosecG(double _v)                       { return Cosec(_v * Float64::DEGTORAD); }


    //---------------------------------
    // Interpolation
    //---------------------------------

    //---------------------------------
    inline float    Lerp(float _start, float _end, float _t)        { return _start + (_end - _start) * _t;             }
    inline float    InvLerp(float _start, float _end, float _value) { return (_value - _start) / (_end - _start);   }

    inline float    Remap(float _inMin, float _inMax, float _outMin, float _outMax, float _value)   { 
        float t = InvLerp(_inMin, _inMax, _value);    
        return Lerp(_outMin, _outMax, t); 
    }

	inline float	RemapClamp(float _inMin, float _inMax, float _outMin, float _outMax, float _value)	{ 
        return Clamp(Remap(_inMin, _inMax, _outMin, _outMax, _value));
    }

    /// From simplex noise
    //---------------------------------
    inline float    Sigma(float _start, float _end, float _t)   { 
        return _start + (_end - _start) * _t * _t * _t * (_t * (_t * 6 - 15) + 10);   
    }

    /// From original perlin noise
    inline float    SigmaP(float _start, float _end, float _t)  { 
        return _start + (_end - _start) * _t * _t * (3 - 2 * _t);     
    }


    //---------------------------------
    // Other functions
    //---------------------------------

    //---------------------------------
    template <typename T>
    inline void     Swap(T &_A, T &_B) {
		T	tmp;

		tmp = _A;
		_A	= _B;
		_B  = tmp;
	}

    template <typename T>
    inline void     SwapInvert(T &_A, T &_B) {
		T	tmp;

		tmp = -_A;
		_A	= -_B;
		_B  = tmp;
	}

    //---------------------------------
    inline uint32_t   BitReverse(uint32_t _val) {
		_val = ((_val>>16) & 0x0000ffffUL) | ((_val<<16) & 0xffff0000UL);
		_val = ((_val>> 8) & 0x00ff00ffUL) | ((_val<< 8) & 0xff00ff00UL);
		_val = ((_val>> 4) & 0x0f0f0f0fUL) | ((_val<< 4) & 0xf0f0f0f0UL);
		_val = ((_val>> 2) & 0x33333333UL) | ((_val<< 2) & 0xccccccccUL);
		return	 ((_val>> 1) & 0x55555555UL) | ((_val<< 1) & 0xaaaaaaaaUL);
    }

} // end of namespace
