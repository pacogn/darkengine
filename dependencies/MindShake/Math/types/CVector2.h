#pragma once

//-------------------------------------
#include <Common/Math/constants.h>
//-------------------------------------
#include <cstddef>
#include <cassert>
//-------------------------------------


//-------------------------------------
namespace MindShake
{

    //---------------------------------
    class CVector2
    {
        public:
                            CVector2()                                          = default;
                            CVector2(const CVector2 &_other)                    = default;
                            ~CVector2()                                         = default;

            explicit        CVector2(float _v)                                  { x = _v; y = _v; }
                            CVector2(float _x, float _y)                        { x = _x; y = _y; }

            template <typename T>
            explicit        CVector2(const T *_ptr)                             { assert(_ptr != nullptr); x = float(_ptr[0]), y = float(_ptr[1]); }

            CVector2 &      operator = (float _v)                               { x = _v; y = _v; return *this; }
            CVector2 &      operator = (const CVector2 &_other)                 = default;

            void            Reset()                                             { x =  0;       y =  0;       }
            void            Set(float _v)                                       { x = _v;       y = _v;       }
            void            Set(float _x, float _y)                             { x = _x;       y = _y;       }
            void            Set(const CVector2 &_other)                         { x = _other.x; y = _other.y; }

            float           operator [] (size_t _i) const                       { assert(_i < 2); return *(&x + _i); }
            float &         operator [] (size_t _i)                             { assert(_i < 2); return *(&x + _i); }

            float *         GetPtr()                                            { return &x; }
            const float *   GetPtr() const                                      { return &x; }

            void            Swap(CVector2 &_other);

            bool            operator == (const CVector2 &_other) const          { return ((x == _other.x) && (y == _other.y)); }
            bool            operator != (const CVector2 &_other) const          { return ((x != _other.x) || (y != _other.y)); }

            bool            IsEqual   (const CVector2 &_other, float _tolerance = Float32::EPSILON) const;
            bool            IsNotEqual(const CVector2 &_other, float _tolerance = Float32::EPSILON) const;

            bool            operator < (const CVector2 &_other) const           { return (x < _other.x) && (y < _other.y); }
            bool            operator > (const CVector2 &_other) const           { return (x > _other.x) && (y > _other.y); }

            const CVector2 &operator + () const                                 { return *this; }
            CVector2        operator - () const                                 { return CVector2(-x, -y); }

            void            operator += (float _v)                              { x += _v;       y += _v;       }
            void            operator += (const CVector2 &_other)                { x += _other.x; y += _other.y; }
            void            operator -= (float _v)                              { x -= _v;       y -= _v;       }
            void            operator -= (const CVector2 &_other)                { x -= _other.x; y -= _other.y; }
            void            operator *= (float _v)                              { x *= _v;       y *= _v;       }
            void            operator *= (const CVector2 &_other)                { x *= _other.x; y *= _other.y; }
            void            operator /= (float _v);
            void            operator /= (const CVector2 &_other);

            float           DotProduct(const CVector2 &_other) const            { return x * _other.x + y * _other.y; }
            float           AbsDotProduct(const CVector2 &_other) const;
            float           PerpendicularDotProduct (const CVector2 &_other) const  { return x * _other.y - y * _other.x; } // Left Handed
            float           PerpendicularDotProductR(const CVector2 &_other) const  { return y * _other.x - x * _other.y; } // Right Handed

            float           CrossProduct(const CVector2 &_other) const          { return x * _other.y - y * _other.x; }

            float           GetLength() const;
            float           GetSquaredLength() const                            { return x * x + y * y; }
            float           GetInverseLength() const;
            float           GetFastInverseLength() const;

            void            SetLength(float _length);
            void            SetMinLength(float _length);
            void            SetMaxLength(float _length);
            void            ClampLength(float _min, float _max);

            void            Normalize();
            float           NormalizeAndGetLength();
            CVector2        GetNormalized() const;
            void            FastNormalize();
            CVector2        GetFastNormalized() const;

            CVector2        GetVector(const CVector2 &_other) const             { return CVector2(_other.x - x, _other.y - y); }
            CVector2        GetMidPoint(const CVector2 &_other) const           { return CVector2((x + _other.x) * 0.5f, (y + _other.y) * 0.5f); }

            float           GetDistance(const CVector2 &_other) const           { return GetVector(_other).GetLength(); }
            float           GetSquaredDistance(const CVector2 &_other) const    { return GetVector(_other).GetSquaredLength(); }

            CVector2        GetPerpendicular () const                           { return CVector2(-y,  x); } // Left Handed
            CVector2        GetPerpendicularR() const                           { return CVector2( y, -x); } // Right Handed
            CVector2        GetProjection(const CVector2 &_from) const;         // Returns _from projected over this vector
            CVector2        GetProjectionUnit(const CVector2 &_from) const;     // If our vector is unitary, this method is faster than GetProjection

            void            Reflect(const CVector2 &_normal);
            void            Reflect(float _normalX, float _normalY)                                 { Reflect(CVector2(_normalX, _normalY)); }
            void            Reflect(const CVector2 &_normal, float _elasticity);                    // _elasticity [0, 1] -> 0 = no reflexion, 1 = total reflexion
            void            Reflect(float _normalX, float _normalY, float _elasticity)              { Reflect(CVector2(_normalX, _normalY), _elasticity); }

            CVector2        GetReflected(const CVector2 &_normal) const;
            CVector2        GetReflected(float _normalX, float _normalY) const                      { return GetReflected(CVector2(_normalX, _normalY)); }
            CVector2        GetReflected(const CVector2 &_normal, float _elasticity) const;         // _elasticity [0, 1] -> 0 = no reflexion, 1 = total reflexion
            CVector2        GetReflected(float _normalX, float _normalY, float _elasticity) const   { return GetReflected(CVector2(_normalX, _normalY), _elasticity); }

            void            Refract(const CVector2 &_normal, float _ratioOfRefraction);
            void            FastRefract(const CVector2 &_normal, float _coeff);
            CVector2        GetRefracted(const CVector2 &_normal, float _ratioOfRefraction) const;
            CVector2        GetFastRefracted(const CVector2 &_normal, float _coeff) const;

            CVector2        GetRandomDeviant(float _angle) const;

            float           GetAngleBetween(const CVector2 &_other) const;      // Degrees

            void            Rotate(float _angle);                               // In degrees

            CVector2        GetRotated(float _angle) const;                     // In degrees

            void            Advance(float _angle, float _distance=1.0f);        // In degrees
            CVector2        GetAdvanced(float _angle, float _distance=1.0f);    // In degrees

            void            SetMin(const CVector2 &_other);
            void            SetMin(float _x, float _y);
            void            SetMax(const CVector2 &_other);
            void            SetMax(float _x, float _y);
            void            Abs();
            void            Floor();
            void            Ceil();
            void            Expand();
            void            Round();
            void            Trunc();
            void            Frac();
            void            Clamp(float _min=0.0f, float _max=1.0f);

            bool            IsZeroLength() const;
            bool            IsNaN() const;

            CVector2        GetXX() const                                       { return CVector2(x);    }
            CVector2        GetXY() const                                       { return *this;          }
            CVector2        GetYX() const                                       { return CVector2(y, x); }
            CVector2        GetYY() const                                       { return CVector2(y);    }

        public:
#pragma pack(push, 1)
            float   x, y;
#pragma pack(pop)

        public:
            static const CVector2   kZERO;
            static const CVector2   kONE;
            static const CVector2   kUNIT_X;
            static const CVector2   kUNIT_Y;
            static const CVector2   kNEGATIVE_UNIT_X;
            static const CVector2   kNEGATIVE_UNIT_Y;
    };

    //---------------------------------
    inline CVector2 operator + (const CVector2 &_v1, const CVector2 &_v2)       { return CVector2(_v1.x + _v2.x, _v1.y + _v2.y); }
    inline CVector2 operator + (const CVector2 &_v1, float           _v2)       { return CVector2(_v1.x + _v2,   _v1.y + _v2);   }
    inline CVector2 operator + (float           _v1, const CVector2 &_v2)       { return CVector2(_v1   + _v2.x, _v1   + _v2.y); }

    inline CVector2 operator - (const CVector2 &_v1, const CVector2 &_v2)       { return CVector2(_v1.x - _v2.x, _v1.y - _v2.y); }
    inline CVector2 operator - (const CVector2 &_v1, float           _v2)       { return CVector2(_v1.x - _v2,   _v1.y - _v2);   }
    inline CVector2 operator - (float           _v1, const CVector2 &_v2)       { return CVector2(_v1   - _v2.x, _v1   - _v2.y); }

    inline CVector2 operator * (const CVector2 &_v1, const CVector2 &_v2)       { return CVector2(_v1.x * _v2.x, _v1.y * _v2.y); }
    inline CVector2 operator * (const CVector2 &_v1, float           _v2)       { return CVector2(_v1.x * _v2,   _v1.y * _v2);   }
    inline CVector2 operator * (float           _v1, const CVector2 &_v2)       { return CVector2(_v1   * _v2.x, _v1   * _v2.y); }

    CVector2        operator / (const CVector2 &_v1, const CVector2 &_v2);
    CVector2        operator / (const CVector2 &_v1, float           _v2);
    CVector2        operator / (float           _v1, const CVector2 &_v2);

    inline float    DotProduct(const CVector2    &_v1, const CVector2 &_v2)             { return _v1.x * _v2.x + _v1.y * _v2.y; }
    float           AbsDotProduct(const CVector2 &_v1, const CVector2 &_v2);
    inline float    PerpendicularDotProduct (const CVector2 &_v1, const CVector2 &_v2)  { return _v1.x * _v2.y - _v1.y * _v2.x; } // Left Handed
    inline float    PerpendicularDotProductR(const CVector2 &_v1, const CVector2 &_v2)  { return _v1.y * _v2.x - _v1.x * _v2.y; } // Right Handed

    inline float    CrossProduct(const CVector2 &_v1, const CVector2 &_v2)      { return _v1.x * _v2.y - _v1.y * _v2.x; }
    inline CVector2 CrossProduct(const CVector2 &_v, float _value)              { return CVector2( _value * _v.y, -_value * _v.x); }
    inline CVector2 CrossProduct(float _value, const CVector2 &_v)              { return CVector2(-_value * _v.y,  _value * _v.x); }

    inline CVector2 GetVector(const CVector2 &_v1, const CVector2 &_v2)         { return CVector2(_v2.x - _v1.x, _v2.y - _v1.y); }
    inline CVector2 GetMidPoint(const CVector2 &_v1, const CVector2 &_v2)       { return (_v1 + _v2) * 0.5f; }

    inline float    GetDistance(const CVector2 &_v1, const CVector2 &_v2)        { return GetVector(_v1, _v2).GetLength(); }
    inline float    GetSquaredDistance(const CVector2 &_v1, const CVector2 &_v2) { return GetVector(_v1, _v2).GetSquaredLength(); }

    inline CVector2 GetPerpendicular(const CVector2 &_vector)                   { return CVector2(-_vector.y,  _vector.x); } // Left Handed
    inline CVector2 GetPerpendicularR(const CVector2 &_vector)                  { return CVector2( _vector.y, -_vector.x); } // Right Handed
    
    CVector2        GetProjection(const CVector2 &_from, const CVector2 &_to);      // Returns _from projected over _to vector
    CVector2        GetProjectionUnit(const CVector2 &_from, const CVector2 &_to);  // If _to vector is unitary, this method is faster than GetProjection
    
    CVector2        GetReflected(const CVector2 &_vector, const CVector2 &_normal);
    CVector2        GetReflected(const CVector2 &_vector, const CVector2 &_normal, float _elasticity);  // _elasticity [0, 1] 0 = no reflexion, 1 = total reflexion
    
    CVector2        GetRefracted(const CVector2 &_vector, const CVector2 &_normal, float _ratioOfRefraction);
    CVector2        GetFastRefracted(const CVector2 &_vector, const CVector2 &_normal, float _coeff);

    float           GetAngleBetween(const CVector2 &_v1, const CVector2 &_v2);

    inline CVector2 Lerp(const CVector2 &_v1, const CVector2 &_v2, float _theta) { return _v1 + ((_v2 - _v1) * _theta);}
    CVector2        Serp(const CVector2 &_v1, const CVector2 &_v2, float _theta);

    CVector2        Min   (const CVector2 &_v1, const CVector2 &_v2);
    CVector2        Max   (const CVector2 &_v1, const CVector2 &_v2);
    CVector2        Abs   (const CVector2 &_v1);
    CVector2        Floor (const CVector2 &_v1);
    CVector2        Ceil  (const CVector2 &_v1);
    CVector2        Expand(const CVector2 &_v1);
    CVector2        Round (const CVector2 &_v1);
    CVector2        Trunc (const CVector2 &_v1);
    CVector2        Frac  (const CVector2 &_v1);
    CVector2        Clamp (const CVector2 &_v1, float _min=0.0f, float _max=1.0f);

    CVector2        GetDirectionVector(float _angle);
    CVector2        GetDirectionVector(float _angle, float _correctAngle);

} // end of namespace
