#pragma once

//-------------------------------------
#include <Common/Math/constants.h>
//-------------------------------------
#include <cassert>
#include <cstddef>
//-------------------------------------


//-------------------------------------
namespace MindShake
{

    //---------------------------------
    class CVector2;

    //---------------------------------
    class CVector3
    {
        public:
                            CVector3()                                          = default;
                            CVector3(const CVector3 &_other)                    = default;
                            ~CVector3()                                         = default;

            explicit        CVector3(float _v)                                  { x = _v; y = _v; z = _v; }
                            CVector3(float _x, float _y, float _z)              { x = _x; y = _y; z = _z; }

            template <typename T>
            explicit        CVector3(const T *_ptr)                             { assert(_ptr != nullptr); x = float(_ptr[0]), y = float(_ptr[1]), z = float(_ptr[2]); }
                            CVector3(const CVector2 &_v2);
                            CVector3(const CVector2 &_v2, float _z);

            CVector3 &      operator = (float _v)                               { x = _v; y = _v; z = _v; return *this; }
            CVector3 &      operator = (const CVector2 &_v2);
            CVector3 &      operator = (const CVector3 &_other)                 = default;

            void            Reset()                                             { x = 0;  y = 0;  z = 0;  }
            void            Set(float _v)                                       { x = _v; y = _v; z = _v; }
            void            Set(float _x, float _y, float _z)                   { x = _x; y = _y; z = _z; }
            void            Set(const CVector2 &_v2);
            void            Set(const CVector2 &_v2, float _z);
            void            Set(const CVector3 &_other)                         { x = _other.x; y = _other.y; z = _other.z; }

            float           operator [] (size_t _i) const                       { assert(_i < 3); return *(&x + _i); }
            float &         operator [] (size_t _i)                             { assert(_i < 3); return *(&x + _i); }

            float *         GetPtr()                                            { return &x; }
            const float *   GetPtr() const                                      { return &x; }

            void            Swap(CVector3 &_other);

            bool            operator == (const CVector3 &_other) const          { return (x == _other.x) && (y == _other.y) && (z == _other.z); }
            bool            operator != (const CVector3 &_other) const          { return (x != _other.x) || (y != _other.y) || (z != _other.z); }

            bool            IsEqual   (const CVector3 &_other, float _tolerance = Float32::EPSILON) const;
            bool            IsNotEqual(const CVector3 &_other, float _tolerance = Float32::EPSILON) const;

            bool            operator < (const CVector3 &_other) const           { return (x < _other.x) && (y < _other.y) && (z < _other.z); }
            bool            operator > (const CVector3 &_other) const           { return (x > _other.x) && (y > _other.y) && (z > _other.z); }

            const CVector3 &operator + () const                                 { return *this; }
            CVector3        operator - () const                                 { return CVector3(-x, -y, -z); }

            void            operator += (float _v)                              { x += _v;       y += _v;       z += _v;       }
            void            operator += (const CVector3 &_other)                { x += _other.x; y += _other.y; z += _other.z; }
            void            operator -= (float _v)                              { x -= _v;       y -= _v;       z -= _v;       }
            void            operator -= (const CVector3 &_other)                { x -= _other.x; y -= _other.y; z -= _other.z; }
            void            operator *= (float _v)                              { x *= _v;       y *= _v;       z *= _v;       }
            void            operator *= (const CVector3 &_other)                { x *= _other.x; y *= _other.y; z *= _other.z; }
            void            operator /= (float _value);
            void            operator /= (const CVector3 &_other);

            float           DotProduct(const CVector3 &_other) const            { return (x * _other.x) + (y * _other.y) + (z * _other.z); }
            float           AbsDotProduct(const CVector3 &_other) const;
            float           PerpendicularDotProduct(const CVector3 &_other) const;

            CVector3        CrossProduct(const CVector3 &_other) const;

            float           GetLength() const;
            float           GetSquaredLength() const                            { return x * x + y * y + z * z; }
            float           GetInverseLength() const;
            float           GetFastInverseLength() const;

            void            SetLength(float _length);
            void            SetMinLength(float _length);
            void            SetMaxLength(float _length);
            void            ClampLength(float _min, float _max);

            void            Normalize();
            float           NormalizeAndGetLength();
            CVector3        GetNormalized() const;
            void            FastNormalize();
            CVector3        GetFastNormalized() const;

            CVector3        GetVector(const CVector3 &_other) const             { return CVector3(_other.x - x, _other.y - y, _other.z - z); }
            CVector3        GetMidPoint(const CVector3& _other) const           { return CVector3((x + _other.x) * 0.5f, (y + _other.y) * 0.5f, (z + _other.z) * 0.5f); }

            float           GetDistance(const CVector3 &_other) const           { return GetVector(_other).GetLength(); }
            float           GetSquaredDistance(const CVector3 &_other) const    { return GetVector(_other).GetSquaredLength(); }

            CVector3        GetPerpendicular() const;
            CVector3        GetProjection(const CVector3 &_from) const;         // Returns _from projected over this vector
            CVector3        GetProjectionUnit(const CVector3 &_from) const;     // If our vector is unitary, this method is faster than GetProjection

            void            Reflect(const CVector3 &_normal);
            void            Reflect(float _normalX, float _normalY, float _normalZ)                                 { Reflect(CVector3(_normalX, _normalY, _normalZ)); }
            void            Reflect(const CVector3 &_normal, float _elasticity);                                    // _elasticity [0, 1] -> 0 = no reflexion, 1 = total reflexion
            void            Reflect(float _normalX, float _normalY, float _normalZ, float _elasticity)              { Reflect(CVector3(_normalX, _normalY, _normalZ), _elasticity); }
            
            CVector3        GetReflected(const CVector3 &_normal) const;
            CVector3        GetReflected(float _normalX, float _normalY, float _normalZ) const                      { return GetReflected(CVector3(_normalX, _normalY, _normalZ)); }
            CVector3        GetReflected(const CVector3 &_normal, float _elasticity) const;                         // _elasticity [0, 1] -> 0 = no reflexion, 1 = total reflexion
            CVector3        GetReflected(float _normalX, float _normalY, float _normalZ, float _elasticity) const   { return GetReflected(CVector3(_normalX, _normalY, _normalZ), _elasticity); }

            void            Refract(const CVector3 &_normal, float _ratioOfRefraction);
            void            FastRefract(const CVector3 &_normal, float _coeff);
            CVector3        GetRefracted(const CVector3 &_normal, float _ratioOfRefraction) const;
            CVector3        GetFastRefracted(const CVector3 &_normal, float _coeff) const;

            CVector3        GetRandomDeviant(float _angle, const CVector3 &_up = kZERO) const;

            float           GetAngleBetween(const CVector3 &_other) const;                                  // Degrees

            void            Rotate(float _angle, const CVector3 &_up = kZERO);                              // In degrees
            void            RotateAboutX(float _angle);                                                     // In degrees
            void            RotateAboutY(float _angle);                                                     // In degrees
            void            RotateAboutZ(float _angle);                                                     // In degrees

            CVector3        GetRotated(float _angle, const CVector3 &_up = kZERO) const;                    // In degrees
            CVector3        GetRotateAboutX(float _angle);                                                  // In degrees
            CVector3        GetRotateAboutY(float _angle);                                                  // In degrees
            CVector3        GetRotateAboutZ(float _angle);                                                  // In degrees

            void            Advance(float _angle, const CVector3 &_up = kZERO, float _distance=1.0f);       // In degrees
            CVector3        GetAdvanced(float _angle, const CVector3 &_up = kZERO, float _distance=1.0f) const; // In degrees

            void            SetMin(const CVector3 &_other);
            void            SetMin(float _x, float _y, float _z);
            void            SetMax(const CVector3 &_other);
            void            SetMax(float _x, float _y, float _z);
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

            CVector2        GetXX() const;
            CVector2        GetXY() const;
            CVector2        GetXZ() const;

            CVector2        GetYX() const;
            CVector2        GetYY() const;
            CVector2        GetYZ() const;

            CVector2        GetZX() const;
            CVector2        GetZY() const;
            CVector2        GetZZ() const;

            CVector3        GetXXX() const;
            CVector3        GetXXY() const;
            CVector3        GetXXZ() const;
            CVector3        GetXYX() const;
            CVector3        GetXYY() const;
            CVector3        GetXYZ() const;
            CVector3        GetXZX() const;
            CVector3        GetXZY() const;
            CVector3        GetXZZ() const;

            CVector3        GetYXX() const;
            CVector3        GetYXY() const;
            CVector3        GetYXZ() const;
            CVector3        GetYYX() const;
            CVector3        GetYYY() const;
            CVector3        GetYYZ() const;
            CVector3        GetYZX() const;
            CVector3        GetYZY() const;
            CVector3        GetYZZ() const;

            CVector3        GetZXX() const;
            CVector3        GetZXY() const;
            CVector3        GetZXZ() const;
            CVector3        GetZYX() const;
            CVector3        GetZYY() const;
            CVector3        GetZYZ() const;
            CVector3        GetZZX() const;
            CVector3        GetZZY() const;
            CVector3        GetZZZ() const;

        public:
#pragma pack(push, 1)
            float   x, y, z;
#pragma pack(pop)

        public:
            static const CVector3   kZERO;
            static const CVector3   kONE;
            static const CVector3   kUNIT_X;
            static const CVector3   kUNIT_Y;
            static const CVector3   kUNIT_Z;
            static const CVector3   kNEGATIVE_UNIT_X;
            static const CVector3   kNEGATIVE_UNIT_Y;
            static const CVector3   kNEGATIVE_UNIT_Z;
    };

    //---------------------------------
    inline CVector3 operator + (const CVector3 &_v1, const CVector3 &_v2)       { return CVector3(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z); }
    inline CVector3 operator + (const CVector3 &_v1, float           _v2)       { return CVector3(_v1.x + _v2,   _v1.y + _v2,   _v1.z + _v2);   }
    inline CVector3 operator + (float           _v1, const CVector3 &_v2)       { return CVector3(_v1   + _v2.x, _v1   + _v2.y, _v1   + _v2.z); }

    inline CVector3 operator - (const CVector3 &_v1, const CVector3 &_v2)       { return CVector3(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z); }
    inline CVector3 operator - (const CVector3 &_v1, float           _v2)       { return CVector3(_v1.x - _v2,   _v1.y - _v2,   _v1.z - _v2);   }
    inline CVector3 operator - (float           _v1, const CVector3 &_v2)       { return CVector3(_v1   - _v2.x, _v1   - _v2.y, _v1   - _v2.z); }

    inline CVector3 operator * (const CVector3 &_v1, const CVector3 &_v2)       { return CVector3(_v1.x * _v2.x, _v1.y * _v2.y, _v1.z * _v2.z); }
    inline CVector3 operator * (const CVector3 &_v1, float           _v2)       { return CVector3(_v1.x * _v2,   _v1.y * _v2,   _v1.z * _v2);   }
    inline CVector3 operator * (float           _v1, const CVector3 &_v2)       { return CVector3(_v1   * _v2.x, _v1   * _v2.y, _v1   * _v2.z); }

    CVector3        operator / (const CVector3 &_v1, const CVector3 &_v2);
    CVector3        operator / (const CVector3 &_v1, float           _v2);
    CVector3        operator / (float           _v1, const CVector3 &_v2);

    inline float    DotProduct(const CVector3    &_v1, const CVector3 &_v2)     { return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z; }
    float           AbsDotProduct(const CVector3 &_v1, const CVector3 &_v2);
    float           PerpendicularDotProduct(const CVector3 &_v1, const CVector3 &_v2);

    CVector3        CrossProduct(const CVector3 &_v1, const CVector3 &_v2);

    inline CVector3 GetVector(const CVector3 &_v1, const CVector3 &_v2)         { return CVector3(_v2.x - _v1.x, _v2.y - _v1.y, _v2.z - _v1.z); }
    inline CVector3 GetMidPoint(const CVector3& _v1, const CVector3& _v2)       { return CVector3((_v1.x + _v2.x) * 0.5f, (_v1.y + _v2.y) * 0.5f, (_v1.z + _v2.z) * 0.5f); }

    inline float    GetDistance(const CVector3 &_v1, const CVector3 &_v2)        { return GetVector(_v1, _v2).GetLength(); }
    inline float    GetSquaredDistance(const CVector3 &_v1, const CVector3 &_v2) { return GetVector(_v1, _v2).GetSquaredLength(); }

    CVector3        GetPerpendicular(const CVector3 &_vector);
    
    CVector3        GetProjection(const CVector3 &_from, const CVector3 &_to);                                  // Returns _from projected over _to vector
    CVector3        GetProjectionUnit(const CVector3 &_from, const CVector3 &_to);                              // If _to vector is unitary, this method is faster than GetProjection
    
    CVector3        GetReflected(const CVector3 &_vector, const CVector3 &_normal);
    CVector2        GetReflected(const CVector3 &_vector, const CVector2 &_normal, float _elasticity);          // _elasticity [0, 1] 0 = no reflexion, 1 = total reflexion
    
    CVector3        GetRefracted(const CVector3 &_vector, const CVector3 &_normal, float _ratioOfRefraction);   // _ratioOfRefraction = indexOfRef1 / _indexOfRef2
    CVector3        GetFastRefracted(const CVector3 &_vector, const CVector3 &_normal, float _coeff);

    float           GetAngleBetween(const CVector3 &_v1, const CVector3 &_v2);

    inline CVector3 Lerp(const CVector3 &_v1, const CVector3 &_v2, float _theta) { return _v1 + ((_v2-_v1) * _theta); }
    CVector3        Serp(const CVector3 &_v1, const CVector3 &_v2, float _theta);

    CVector3        Min   (const CVector3 &_v1, const CVector3 &_v2);
    CVector3        Max   (const CVector3 &_v1, const CVector3 &_v2);
    CVector3        Abs   (const CVector3 &_v1);
    CVector3        Floor (const CVector3 &_v1);
    CVector3        Ceil  (const CVector3 &_v1);
    CVector3        Expand(const CVector3 &_v1);
    CVector3        Round (const CVector3 &_v1);
    CVector3        Trunc (const CVector3 &_v1);
    CVector3        Frac  (const CVector3 &_v1);
    CVector3        Clamp (const CVector3 &_v1, float _min=0.0f, float _max=1.0f);

} // end of namespace
