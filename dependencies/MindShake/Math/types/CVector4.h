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
    class CVector3;
    //---------------------------------

    //---------------------------------
    class alignas(16) CVector4
    {
        public:
                            CVector4()                                          = default;
                            CVector4(const CVector4 &_other)                    = default;
                            ~CVector4()                                         = default;

            explicit        CVector4(float _v)                                  { x = _v; y = _v; z = _v; w = _v; }
                            CVector4(float _x, float _y, float _z, float _w)    { x = _x; y = _y; z = _z; w = _w; }

                            template <typename T>
            explicit        CVector4(const T *_ptr)                             { assert(_ptr != nullptr); x = float(_ptr[0]), y = float(_ptr[1]), z = float(_ptr[2]), w = float(_ptr[3]); }
                            CVector4(const CVector2 &_v2);
                            CVector4(const CVector2 &_v2, float _z);
                            CVector4(const CVector2 &_v2, float _z, float _w);
                            CVector4(const CVector3 &_v3);
                            CVector4(const CVector3 &_v3, float _w);

            CVector4 &      operator = (float _v)                               { x = _v; y = _v; z = _v; w = _v; return *this; }
            CVector4 &      operator = (const CVector3 &_v3);
            CVector4 &      operator = (const CVector4 &_other)                 = default;

            void            Reset()                                             { x = 0;  y = 0;  z = 0;  w = 0;  }
            void            Set(float _v)                                       { x = _v; y = _v; z = _v; w = _v; }
            void            Set(float _x, float _y, float _z, float _w)         { x = _x; y = _y; z = _z; w = _w; }
            void            Set(const CVector2 &_v2);
            void            Set(const CVector2 &_v2, float _z);
            void            Set(const CVector2 &_v2, float _z, float _w);
            void            Set(const CVector3 &_v3);
            void            Set(const CVector3 &_v3, float _w);
            void            Set(const CVector4 &_other)                         { x = _other.x; y = _other.y; z = _other.z; w = _other.w; }

            float           operator [] (size_t _i) const                       { assert(_i < 4); return *(&x + _i); }
            float &         operator [] (size_t _i)                             { assert(_i < 4); return *(&x + _i); }

            float *         GetPtr()                                            { return &x; }
            const float *   GetPtr() const                                      { return &x; }

            void            Swap(CVector4 &_rOther);

            bool            operator == (const CVector4 &_other) const          { return (x == _other.x) && (y == _other.y) && (z == _other.z) && (w == _other.w); }
            bool            operator != (const CVector4 &_other) const          { return (x != _other.x) || (y != _other.y) || (z != _other.z) || (w != _other.w); }

            bool            IsEqual   (const CVector4 &_other, float _tolerance = Float32::EPSILON) const;
            bool            IsNotEqual(const CVector4 &_other, float _tolerance = Float32::EPSILON) const;

            bool            operator < (const CVector4 &_other) const           { return (x < _other.x) && (y < _other.y) && (z < _other.z) && (w < _other.w); }
            bool            operator > (const CVector4 &_other) const           { return (x > _other.x) && (y > _other.y) && (z > _other.z) && (w > _other.w); }

            const CVector4 &operator + () const                                 { return *this; }
            CVector4        operator - () const                                 { return CVector4(-x, -y, -z, -w);  }

            void            operator += (float _v)                              { x += _v;       y += _v;       z += _v;       w += _v;       }
            void            operator += (const CVector4 &_other)                { x += _other.x; y += _other.y; z += _other.z; w += _other.w; }
            void            operator -= (float _v)                              { x -= _v;       y -= _v;       z -= _v;       w -= _v;       }
            void            operator -= (const CVector4 &_other)                { x -= _other.x; y -= _other.y; z -= _other.z; w -= _other.w; }
            void            operator *= (float _v)                              { x *= _v;       y *= _v;       z *= _v;       w *= _v;       }
            void            operator *= (const CVector4 &_other)                { x *= _other.x; y *= _other.y; z *= _other.z; w *= _other.w; }
            void            operator /= (float _value);
            void            operator /= (const CVector4 &_other);

            float           DotProduct(const CVector4 &_other) const            { return x * _other.x + y * _other.y + z * _other.z + w * _other.w; }
            float           AbsDotProduct(const CVector4 &_other) const;

            float           GetLength() const;
            float           GetSquaredLength() const                            { return x * x + y * y + z * z + w * w; }
            float           GetInverseLength() const;
            float           GetFastInverseLength() const;

            void            SetLength(float _length);
            void            SetMinLength(float _length);
            void            SetMaxLength(float _length);
            void            ClampLength(float _min, float _max);

            void            Normalize();
            float           NormalizeAndGetLength();
            CVector4        GetNormalized() const;
            void            FastNormalize();
            CVector4        GetFastNormalized() const;

            CVector4        GetVector(const CVector4 &_other) const             { return CVector4(_other.x - x, _other.y - y, _other.z - z, _other.w - w); }
            CVector4        GetMidPoint(const CVector4& _other) const           { return CVector4((x + _other.x) * 0.5f, (y + _other.y) * 0.5f, (z + _other.z) * 0.5f, (w + _other.w) * 0.5f);
}

            float           GetDistance(const CVector4 &_other) const           { return GetVector(_other).GetLength(); }
            float           GetSquaredDistance(const CVector4 &_other) const    { return GetVector(_other).GetSquaredLength(); }

            void            Reflect(const CVector4 & _normal);
            CVector4        GetReflected(const CVector4 & _normal) const;

            void            Rotate(float _angle, const CVector4 &_axis);                // In degrees
            void            RotateAboutX(float _angle);                                 // In degrees
            void            RotateAboutY(float _angle);                                 // In degrees
            void            RotateAboutZ(float _angle);                                 // In degrees

            CVector4        GetRotated(float _angle, const CVector4 &_axis) const;      // In degrees
            CVector4        GetRotateAboutX(float _angle);                              // In degrees
            CVector4        GetRotateAboutY(float _angle);                              // In degrees
            CVector4        GetRotateAboutZ(float _angle);                              // In degrees

            void            SetMin(const CVector4 &_other);
            void            SetMax(const CVector4 &_other);
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

            CVector3        GetXYZ() const;

        public:
#pragma pack(push, 1)
            float x, y, z, w;
#pragma pack(pop)

        public:
            static const CVector4 kZERO;
            static const CVector4 kONE;
            static const CVector4 kUNIT_X;
            static const CVector4 kUNIT_Y;
            static const CVector4 kUNIT_Z;
            static const CVector4 kUNIT_W;
            static const CVector4 kNEGATIVE_UNIT_X;
            static const CVector4 kNEGATIVE_UNIT_Y;
            static const CVector4 kNEGATIVE_UNIT_Z;
            static const CVector4 kNEGATIVE_UNIT_W;

    };

    //---------------------------------
    inline CVector4 operator + (const CVector4 &_v1, const CVector4 &_v2)       { return CVector4(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z, _v1.w + _v2.w); }
    inline CVector4 operator + (const CVector4 &_v1, float           _v2)       { return CVector4(_v1.x + _v2,   _v1.y + _v2,   _v1.z + _v2,   _v1.w + _v2);   }
    inline CVector4 operator + (float           _v1, const CVector4 &_v2)       { return CVector4(_v1   + _v2.x, _v1   + _v2.y, _v1   + _v2.z, _v1   + _v2.w); }

    inline CVector4 operator - (const CVector4 &_v1, const CVector4 &_v2)       { return CVector4(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z, _v1.w - _v2.w); }
    inline CVector4 operator - (const CVector4 &_v1, float           _v2)       { return CVector4(_v1.x - _v2,   _v1.y - _v2,   _v1.z - _v2,   _v1.w - _v2);   }
    inline CVector4 operator - (float           _v1, const CVector4 &_v2)       { return CVector4(_v1   - _v2.x, _v1   - _v2.y, _v1   - _v2.z, _v1   - _v2.w); }

    inline CVector4 operator * (const CVector4 &_v1, const CVector4 &_v2)       { return CVector4(_v1.x * _v2.x, _v1.y * _v2.y, _v1.z * _v2.z, _v1.w * _v2.w); }
    inline CVector4 operator * (const CVector4 &_v1, float           _v2)       { return CVector4(_v1.x * _v2,   _v1.y * _v2,   _v1.z * _v2,   _v1.w * _v2);   }
    inline CVector4 operator * (float           _v1, const CVector4 &_v2)       { return CVector4(_v1   * _v2.x, _v1   * _v2.y, _v1   * _v2.z, _v1   * _v2.w); }

    CVector4        operator / (const CVector4 &_v1, const CVector4 &_v2);
    CVector4        operator / (const CVector4 &_v1, float           _v2);
    CVector4        operator / (float           _v1, const CVector4 &_v2);
}
