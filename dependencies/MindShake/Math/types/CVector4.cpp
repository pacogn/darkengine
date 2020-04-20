//-------------------------------------
#include <Common/Math/configMathLib.h>
#include <Common/Math/math_funcs.h>
//-------------------------------------
#include "CVector4.h"
#include "CVector3.h"
#include "CVector2.h"
//-------------------------------------


//-------------------------------------
namespace MindShake
{

    //---------------------------------
    const CVector4 CVector4::kZERO(0.0f);
    const CVector4 CVector4::kONE(1.0f);
    const CVector4 CVector4::kUNIT_X(1, 0, 0, 0);
    const CVector4 CVector4::kUNIT_Y(0, 1, 0, 0);
    const CVector4 CVector4::kUNIT_Z(0, 0, 1, 0);
    const CVector4 CVector4::kUNIT_W(0, 0, 0, 1);
    const CVector4 CVector4::kNEGATIVE_UNIT_X(-1,  0,  0,  0);
    const CVector4 CVector4::kNEGATIVE_UNIT_Y( 0, -1,  0,  0);
    const CVector4 CVector4::kNEGATIVE_UNIT_Z( 0,  0, -1,  0);
    const CVector4 CVector4::kNEGATIVE_UNIT_W( 0,  0,  0, -1);

    //---------------------------------
    CVector4::CVector4(const CVector2 &_v2)
        : x(_v2.x), y(_v2.y), z(0), w(1.0f)
    {
    }

    //---------------------------------
    CVector4::CVector4(const CVector2 &_v2, float _z)
        : x(_v2.x), y(_v2.y), z(_z), w(1.0f)
    {
    }

    //---------------------------------
    CVector4::CVector4(const CVector2 &_v2, float _z, float _w)
        : x(_v2.x), y(_v2.y), z(_z), w(_w)
    {
    }

    //---------------------------------
    CVector4::CVector4(const CVector3 &_v3)
        : x(_v3.x), y(_v3.y), z(_v3.z), w(1.0f)
    {
    }

    //---------------------------------
    CVector4::CVector4(const CVector3 &_v3, float _w)
        : x(_v3.x), y(_v3.y), z(_v3.z), w(_w)
    {
    }

    //---------------------------------

    //---------------------------------
    CVector4 &
    CVector4::operator = (const CVector3 &_v3)
    {
        x = _v3.x;
        y = _v3.y;
        z = _v3.z;
        w = 1.0f;

        return *this;
    }

    //---------------------------------
    void
    CVector4::Set(const CVector2 &_v2)
    {
        x = _v2.x;
        y = _v2.y;
        z = 0;
        w = 1;
    }

    //---------------------------------
    void
    CVector4::Set(const CVector2 &_v2, float _z)
    {
        x = _v2.x;
        y = _v2.y;
        z = _z;
        w = 1;
    }

    //---------------------------------
    void
    CVector4::Set(const CVector2 &_v2, float _z, float _w)
    {
        x = _v2.x;
        y = _v2.y;
        z = _z;
        w = _w;
    }

    //---------------------------------
    void
    CVector4::Set(const CVector3 &_v3)
    {
        x = _v3.x;
        y = _v3.y;
        z = _v3.z;
        w = 1;
    }

    //---------------------------------
    void
    CVector4::Set(const CVector3 &_v3, float _w)
    {
        x = _v3.x;
        y = _v3.y;
        z = _v3.z;
        w = _w;
    }

    //---------------------------------

    //---------------------------------
    void
    CVector4::Swap(CVector4 &_rOther)
    {
        MindShake::Swap(x, _rOther.x);
        MindShake::Swap(y, _rOther.y);
        MindShake::Swap(z, _rOther.z);
        MindShake::Swap(w, _rOther.w);
    }

    //---------------------------------

    //---------------------------------
    bool
    CVector4::IsEqual(const CVector4 &_other, float _tolerance) const
    {
        return
            MindShake::IsEqual(x, _other.x, _tolerance) &&
            MindShake::IsEqual(y, _other.y, _tolerance) &&
            MindShake::IsEqual(z, _other.z, _tolerance) &&
            MindShake::IsEqual(w, _other.w, _tolerance);
    }

    //---------------------------------
    bool
    CVector4::IsNotEqual(const CVector4 &_other, float _tolerance) const
    {
        return
            MindShake::IsNotEqual(x, _other.x, _tolerance) ||
            MindShake::IsNotEqual(y, _other.y, _tolerance) ||
            MindShake::IsNotEqual(z, _other.z, _tolerance) ||
            MindShake::IsNotEqual(w, _other.w, _tolerance);
    }

    //---------------------------------

    //---------------------------------
    void
    CVector4::operator /= (const CVector4 &_other)
    {
        if(_other.x != 0.0f)
            x /= _other.x;

        if(_other.y != 0.0f)
            y /= _other.y;

        if(_other.z != 0.0f)
            z /= _other.z;

        if(_other.w != 0.0f)
            w /= _other.w;
    }

    //---------------------------------
    void
    CVector4::operator /= (float _value)
    {
        float inv;

        if(IsNotZero(_value))
        {
            inv = 1.0f / _value;
            x *= inv;
            y *= inv;
            z *= inv;
            w *= inv;
        }
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    float
    CVector4::AbsDotProduct(const CVector4 &_other) const
    {
        return MindShake::Abs(x * _other.x) + MindShake::Abs(y * _other.y) + MindShake::Abs(z * _other.z) + MindShake::Abs(w * _other.w);
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    float
    CVector4::GetLength() const
    {
        return MindShake::Sqrt(x*x + y*y + z*z + w*w);
    }

    //---------------------------------
    float
    CVector4::GetInverseLength() const
    {
        return MindShake::InvSqrt(x*x + y*y + z*z + w*w);
    }

    //---------------------------------
    float
    CVector4::GetFastInverseLength() const
    {
        return MindShake::FastInvSqrt(x*x + y*y + z*z + w*w);
    }

    //---------------------------------
    void
    CVector4::SetLength(float _length)
    {
        Normalize();
        x *= _length;
        y *= _length;
        z *= _length;
        w *= _length;
    }

    //---------------------------------
    void
    CVector4::SetMinLength(float _length)
    {
        float   len;
        float   aux = 0;

        len = MindShake::Sqrt(x*x + y*y + z*z + w*w);
        if(len < _length)
        {
            if(len != 0.0f)
                aux = (_length / len);

            x *= aux;
            y *= aux;
            z *= aux;
            w *= aux;
        }
    }

    //---------------------------------
    void
    CVector4::SetMaxLength(float _length)
    {
        float   len;
        float   aux = 0;

        len = MindShake::Sqrt(x*x + y*y + z*z + w*w);
        if(len > _length)
        {
            if(len != 0.0f)
                aux = (_length / len);

            x *= aux;
            y *= aux;
            z *= aux;
            w *= aux;
        }
    }

    //---------------------------------
    void
    CVector4::ClampLength(float _min, float _max)
    {
        float   len;
        float   aux;

        aux = MindShake::Sqrt(x*x + y*y + z*z + w*w);
        len = MindShake::Clamp(aux, _min, _max);
// No vale la pena
//      if(len != aux)
        {
            if(aux != 0.0f)
                aux = (len / aux);

            x *= aux;
            y *= aux;
            z *= aux;
            w *= aux;
        }
    }

    //---------------------------------
    void
    CVector4::Normalize()
    {
        float invLength;

        invLength = MindShake::InvSqrt(x*x + y*y + z*z + w*w);
        x *= invLength;
        y *= invLength;
        z *= invLength;
        w *= invLength;
    }

    //---------------------------------
    float
    CVector4::NormalizeAndGetLength()
    {
        float   len;
        float   aux = 0;

        len = MindShake::Sqrt(x*x + y*y + z*z + w*w);
        if(len != 0.0f)
            aux = 1.0f / len;

        x *= aux;
        y *= aux;
        z *= aux;
        w *= aux;

        return len;
    }

    //---------------------------------
    CVector4
    CVector4::GetNormalized() const
    {
        float   invLength;
        float   nx, ny, nz, nw;

        invLength = MindShake::InvSqrt(x*x + y*y + z*z + w*w);
        nx = x * invLength;
        ny = y * invLength;
        nz = z * invLength;
        nw = w * invLength;

        return CVector4(nx, ny, nz, nw);
    }

    //---------------------------------
    void
    CVector4::FastNormalize()
    {
        float invLength;

        invLength = MindShake::FastInvSqrt(x*x + y*y + z*z + w*w);
        x *= invLength;
        y *= invLength;
        z *= invLength;
        w *= invLength;
    }

    //---------------------------------
    CVector4
    CVector4::GetFastNormalized() const
    {
        float   invLength;
        float   nx, ny, nz, nw;

        invLength = MindShake::FastInvSqrt(x*x + y*y + z*z + w*w);
        nx = x * invLength;
        ny = y * invLength;
        nz = z * invLength;
        nw = w * invLength;

        return CVector4(nx, ny, nz, nw);
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    void
    CVector4::Reflect(const CVector4 & _normal)
    {
        *this -= (2.0f * this->DotProduct(_normal) * _normal);
    }

    //---------------------------------
    CVector4
    CVector4::GetReflected(const CVector4 & _normal) const
    {
        return CVector4(*this - (2.0f * this->DotProduct(_normal) * _normal));
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    void
    CVector4::Rotate(float _angle, const CVector4 &_axis)
    {
        float   fSin, fCos;
        float   oneMinusCos;
        float   nx, ny, nz;

        _angle *= Float32::DEGTORAD;

        fSin        = sinf(_angle);
        fCos        = cosf(_angle);
        oneMinusCos = 1.0f - fCos;

        nx = x * (fCos + oneMinusCos * _axis.x * _axis.x) +
             y * (oneMinusCos * _axis.x * _axis.y - fSin * _axis.z) +
             z * (oneMinusCos * _axis.x * _axis.z + fSin * _axis.y);

        ny = x * (oneMinusCos * _axis.x * _axis.y + fSin * _axis.z) +
             y * (fCos + oneMinusCos * _axis.y * _axis.y) +
             z * (oneMinusCos * _axis.y * _axis.z - fSin * _axis.x);

        nz = x * (oneMinusCos * _axis.x * _axis.z - fSin * _axis.y) +
             y * (oneMinusCos * _axis.y * _axis.z + fSin * _axis.x) +
             z * (fCos + oneMinusCos * _axis.z * _axis.z);

        x = nx;
        y = ny;
        z = nz;
    }

    //---------------------------------
    void
    CVector4::RotateAboutX(float _angle)
    {
        float   fSin, fCos;
        float   ny, nz;

        _angle *= Float32::DEGTORAD;

        fSin = sinf(_angle);
        fCos = cosf(_angle);

        ny = fCos * y - fSin * z;
        nz = fCos * z + fSin * y;

        y = ny;
        z = nz;
    }

    //---------------------------------
    void
    CVector4::RotateAboutY(float _angle)
    {
        float   fSin, fCos;
        float   nx, nz;

        _angle *= Float32::DEGTORAD;

        fSin = sinf(_angle);
        fCos = cosf(_angle);

        nx = fCos * x + fSin * z;
        nz = fCos * z - fSin * x;

        x = nx;
        z = nz;
    }

    //---------------------------------
    void
    CVector4::RotateAboutZ(float _angle)
    {
        float   fSin, fCos;
        float   nx, ny;

        _angle *= Float32::DEGTORAD;

        fSin = sinf(_angle);
        fCos = cosf(_angle);

        nx = fCos * x - fSin * y;
        ny = fCos * y + fSin * x;

        x = nx;
        y = ny;
    }

    //---------------------------------
    CVector4
    CVector4::GetRotated(float _angle, const CVector4 &_axis) const
    {
        CVector4    aux(*this);

        aux.Rotate(_angle, _axis);

        return aux;
    }

    //---------------------------------
    CVector4
    CVector4::GetRotateAboutX(float _angle)
    {
        CVector4    aux(*this);

        aux.RotateAboutX(_angle);

        return aux;
    }

    //---------------------------------
    CVector4
    CVector4::GetRotateAboutY(float _angle)
    {
        CVector4    aux(*this);

        aux.RotateAboutY(_angle);

        return aux;
    }

    //---------------------------------
    CVector4
    CVector4::GetRotateAboutZ(float _angle)
    {
        CVector4    aux(*this);

        aux.RotateAboutZ(_angle);

        return aux;
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    void
    CVector4::SetMin(const CVector4 &_other)
    {
        if(_other.x < x) x = _other.x;
        if(_other.y < y) y = _other.y;
        if(_other.z < z) z = _other.z;
        if(_other.w < w) w = _other.w;
    }

    //---------------------------------
    void
    CVector4::SetMax(const CVector4 &_other)
    {
        if(_other.x > x) x = _other.x;
        if(_other.y > y) y = _other.y;
        if(_other.z > z) z = _other.z;
        if(_other.w > w) w = _other.w;
    }

    //---------------------------------
    void
    CVector4::Abs()
    {
        x = MindShake::Abs(x);
        y = MindShake::Abs(y);
        z = MindShake::Abs(z);
        w = MindShake::Abs(w);
    }

    //---------------------------------
    void
    CVector4::Floor()
    {
        x = MindShake::Floor(x);
        y = MindShake::Floor(y);
        z = MindShake::Floor(z);
        w = MindShake::Floor(w);
    }

    //---------------------------------
    void
    CVector4::Ceil()
    {
        x = MindShake::Ceil(x);
        y = MindShake::Ceil(y);
        z = MindShake::Ceil(z);
        w = MindShake::Ceil(w);
    }

    //---------------------------------
    void
    CVector4::Expand()
    {
        x = MindShake::Expand(x);
        y = MindShake::Expand(y);
        z = MindShake::Expand(z);
        w = MindShake::Expand(w);
    }

    //---------------------------------
    void
    CVector4::Round()
    {
        x = MindShake::Round(x);
        y = MindShake::Round(y);
        z = MindShake::Round(z);
        w = MindShake::Round(w);
    }

    //---------------------------------
    void
    CVector4::Trunc()
    {
        x = MindShake::Trunc(x);
        y = MindShake::Trunc(y);
        z = MindShake::Trunc(z);
        w = MindShake::Trunc(w);
    }

    //---------------------------------
    void
    CVector4::Frac()
    {
        x = MindShake::Frac(x);
        y = MindShake::Frac(y);
        z = MindShake::Frac(z);
        w = MindShake::Frac(w);
    }

    //---------------------------------
    void
    CVector4::Clamp(float _min, float _max)
    {
        x = MindShake::Clamp(x, _min, _max);
        y = MindShake::Clamp(y, _min, _max);
        z = MindShake::Clamp(z, _min, _max);
        w = MindShake::Clamp(w, _min, _max);
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    bool
    CVector4::IsZeroLength() const
    {
        float sqlen;

        sqlen = x*x + y*y + z*z + w*w;

        return (sqlen < Float32::SQR_EPSILON);
    }

    //---------------------------------
    bool
    CVector4::IsNaN() const
    {
        return MindShake::IsNaN(x) || MindShake::IsNaN(y) || MindShake::IsNaN(z) || MindShake::IsNaN(w);
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    CVector3
    CVector4::GetXYZ() const
    {
        return CVector3(x, y, z);
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    CVector4
    operator /(const CVector4 &_v1, const CVector4 &_v2)
    {
        CVector4    v(0);

        if(_v2.x != 0.0f)
            v.x = _v1.x / _v2.x;

        if(_v2.y != 0.0f)
            v.y = _v1.y / _v2.y;

        if(_v2.z != 0.0f)
            v.z = _v1.z / _v2.z;

        if(_v2.w != 0.0f)
            v.w = _v1.w / _v2.w;

        return v;
    }

    //---------------------------------
    CVector4
    operator /(float _v1, const CVector4 &_v2)
    {
        CVector4    v(0);

        if(_v2.x != 0.0f)
            v.x = _v1 / _v2.x;

        if(_v2.y != 0.0f)
            v.y = _v1 / _v2.y;

        if(_v2.z != 0.0f)
            v.z = _v1 / _v2.z;

        if(_v2.w != 0.0f)
            v.w = _v1 / _v2.w;

        return v;
    }

    //---------------------------------
    CVector4
    operator /(const CVector4 &_v1, float    _v2)
    {
        CVector4    v;
        float       aux;

        if(_v2 != 0.0f)
        {
            aux = 1.0f / _v2;
            v.x = _v1.x * aux;
            v.y = _v1.y * aux;
            v.z = _v1.z * aux;
            v.w = _v1.w * aux;

            return v;
        }

        return CVector4(0);
    }

} // end of namespace
