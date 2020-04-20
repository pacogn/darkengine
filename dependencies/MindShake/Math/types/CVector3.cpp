//-------------------------------------
#include <Common/Math/configMathLib.h>
#include <Common/Math/math_funcs.h>
//-------------------------------------
#include "CVector2.h"
#include "CVector3.h"
#include "CQuaternion.h"
//-------------------------------------
#include <Math/random/FastRand2.h>
//-------------------------------------


//-------------------------------------
namespace MindShake
{

    //---------------------------------
    const CVector3 CVector3::kZERO(0.0f);
    const CVector3 CVector3::kONE(1.0f);
    const CVector3 CVector3::kUNIT_X(1, 0, 0);
    const CVector3 CVector3::kUNIT_Y(0, 1, 0);
    const CVector3 CVector3::kUNIT_Z(0, 0, 1);
    const CVector3 CVector3::kNEGATIVE_UNIT_X(-1, 0, 0);
    const CVector3 CVector3::kNEGATIVE_UNIT_Y(0, -1, 0);
    const CVector3 CVector3::kNEGATIVE_UNIT_Z(0, 0, -1);

    //---------------------------------
    CVector3::CVector3(const CVector2 &_v2)
    {
        x = _v2.x;
        y = _v2.y;
        z = 0;
    }

    //---------------------------------
    CVector3::CVector3(const CVector2 &_v2, float _z)
    {
        x = _v2.x;
        y = _v2.y;
        z = _z;
    }

    //---------------------------------
    CVector3 &
    CVector3::operator = (const CVector2 &_v2)
    {
        x = _v2.x;
        y = _v2.y;
        z = 0;

        return *this;
    }

    //---------------------------------
    void
    CVector3::Set(const CVector2 &_v2)
    {
        x = _v2.x;
        y = _v2.y;
        z  = 0;
    }

    //---------------------------------
    void
    CVector3::Set(const CVector2 &_v2, float _z)
    {
        x = _v2.x;
        y = _v2.y;
        z = _z;
    }

    //---------------------------------

    //---------------------------------
    void
    CVector3::Swap(CVector3 &_other)
    {
        MindShake::Swap(x, _other.x);
        MindShake::Swap(y, _other.y);
        MindShake::Swap(z, _other.z);
    }

    //---------------------------------

    //---------------------------------
    bool
    CVector3::IsEqual(const CVector3 &_other, float _tolerance) const
    {
    return
            MindShake::IsEqual(x, _other.x, _tolerance) &&
            MindShake::IsEqual(y, _other.y, _tolerance) &&
            MindShake::IsEqual(z, _other.z, _tolerance);
    }

    //---------------------------------
    bool
    CVector3::IsNotEqual(const CVector3 &_other, float _tolerance) const
    {
        return
            MindShake::IsNotEqual(x, _other.x, _tolerance) ||
            MindShake::IsNotEqual(y, _other.y, _tolerance) ||
            MindShake::IsNotEqual(z, _other.z, _tolerance);
    }

    //---------------------------------

    //---------------------------------
    void
    CVector3::operator /= (const CVector3 &_other)
    {
        if(IsNotZero(_other.x))
            x /= _other.x;

        if(IsNotZero(_other.y))
            y /= _other.y;

        if(IsNotZero(_other.z))
            z /= _other.z;
    }

    //---------------------------------
    void
    CVector3::operator /= (float _value)
    {
        float   inv;

        if(IsNotZero(_value))
        {
            inv = 1.0f / _value;
            x *= inv;
            y *= inv;
            z *= inv;
        }
    }

    //---------------------------------
    float
    CVector3::AbsDotProduct(const CVector3 &_other) const
    {
        return MindShake::Abs(x * _other.x) + MindShake::Abs(y * _other.y) + MindShake::Abs(z * _other.z);
    }

    //---------------------------------
    float
    CVector3::PerpendicularDotProduct(const CVector3 &_other) const
    {
        return MindShake::DotProduct(*this, MindShake::GetPerpendicular(_other));
    }

    //---------------------------------
    CVector3
    CVector3::CrossProduct(const CVector3 &_other) const
    {
        return CVector3(
            y * _other.z - z * _other.y,
            z * _other.x - x * _other.z,
            x * _other.y - y * _other.x);
    }

    //---------------------------------
    float
    CVector3::GetLength() const
    {
        return MindShake::Sqrt(x*x + y*y + z*z);
    }

    //---------------------------------
    float
    CVector3::GetInverseLength() const
    {
        return MindShake::InvSqrt(x*x + y*y + z*z);
    }

    //---------------------------------
    float
    CVector3::GetFastInverseLength() const
    {
        return MindShake::FastInvSqrt(x*x + y*y + z*z);
    }

    //---------------------------------
    void
    CVector3::SetLength(float _length)
    {
        Normalize();
        x *= _length;
        y *= _length;
        z *= _length;
    }

    //---------------------------------
    void
    CVector3::SetMinLength(float _length)
    {
        float   len;
        float   aux = 0;

        len = MindShake::Sqrt(x*x + y*y + z*z);
        if(len < _length)
        {
            if(len != 0.0f)
                aux = (_length / len);

            x *= aux;
            y *= aux;
            z *= aux;
        }
    }

    //---------------------------------
    void
    CVector3::SetMaxLength(float _length)
    {
        float   len;
        float   aux = 0;

        len = MindShake::Sqrt(x*x + y*y + z*z);
        if(len > _length)
        {
            if(len != 0.0f)
                aux = (_length / len);

            x *= aux;
            y *= aux;
            z *= aux;
        }
    }

    //---------------------------------
    void
    CVector3::ClampLength(float _min, float _max)
    {
        float   len;
        float   aux;

        aux = MindShake::Sqrt(x*x + y*y + z*z);
        len = MindShake::Clamp(aux, _min, _max);
// No vale la pena
//      if(len != aux)
        {
            if(aux != 0.0f)
                aux = (len / aux);

            x *= aux;
            y *= aux;
            z *= aux;
        }
    }

    //---------------------------------
    void
    CVector3::Normalize()
    {
        float invLength;

        invLength = MindShake::InvSqrt(x*x + y*y + z*z);
        x *= invLength;
        y *= invLength;
        z *= invLength;
    }

    //---------------------------------
    float
    CVector3::NormalizeAndGetLength()
    {
        float   len;
        float   aux = 0;

        len = MindShake::Sqrt(x*x + y*y + z*z);
        if(len != 0.0f)
            aux = 1.0f / len;

        x *= aux;
        y *= aux;
        z *= aux;

        return len;
    }

    //---------------------------------
    CVector3
    CVector3::GetNormalized() const
    {
        float   invLength;
        float   nx, ny, nz;

        invLength = MindShake::InvSqrt(x*x + y*y + z*z);
        nx = x * invLength;
        ny = y * invLength;
        nz = z * invLength;

        return CVector3(nx, ny, nz);
    }

    //---------------------------------
    void
    CVector3::FastNormalize()
    {
        float invLength;

        invLength = MindShake::FastInvSqrt(x*x + y*y + z*z);
        x *= invLength;
        y *= invLength;
        z *= invLength;
    }

    //---------------------------------
    CVector3
    CVector3::GetFastNormalized() const
    {
        float   invLength;
        float   nx, ny, nz;

        invLength = MindShake::FastInvSqrt(x*x + y*y + z*z);
        nx = x * invLength;
        ny = y * invLength;
        nz = z * invLength;

        return CVector3(nx, ny, nz);
    }

    //---------------------------------
    CVector3
    CVector3::GetPerpendicular() const
    {
        CVector3 perp;

        perp = this->CrossProduct(CVector3::kUNIT_X);

        // Check Length
        if(perp.GetSquaredLength() < Float32::SQR_EPSILON)
        {
            perp = this->CrossProduct(CVector3::kUNIT_Y);
        }
        else
            perp.Normalize();

        return perp;
    }

    //---------------------------------
    CVector3
    CVector3::GetProjection(const CVector3 &_from) const
    {
        float   dotProduct;
        float   sqrLength;
        float   aux;

        dotProduct = DotProduct(_from);
        sqrLength  = GetSquaredLength();
        if(sqrLength >= Float32::ZERO_EPSILON)
            aux = dotProduct / sqrLength;
        else 
            aux = 0.0f;

        return CVector3(aux * x, aux * y, aux * z);
    }

    //---------------------------------
    CVector3
    CVector3::GetProjectionUnit(const CVector3 &_from) const
    {
        float   dotProduct;

        dotProduct = DotProduct(_from);

        return CVector3(dotProduct * x, dotProduct * y, dotProduct * z);
    }

    //---------------------------------
    void
    CVector3::Reflect(const CVector3 &_normal)
    {
        *this -= (2.0f * DotProduct(_normal) * _normal);
    }

    //---------------------------------
    void
    CVector3::Reflect(const CVector3 &_normal, float _elasticity)
    {
        *this -= ((1.0f + _elasticity) * DotProduct(_normal) * _normal);
    }

    //---------------------------------
    CVector3
    CVector3::GetReflected(const CVector3 &_normal) const
    {
        return CVector3(*this - (2.0f * this->DotProduct(_normal) * _normal));
    }

    //---------------------------------
    CVector3
    CVector3::GetReflected(const CVector3 &_normal, float _elasticity) const
    {
        return CVector3(*this - ((1.0f + _elasticity) * DotProduct(_normal) * _normal));
    }

    //---------------------------------
    void
    CVector3::Refract(const CVector3 &_normal, float _ratioOfRefraction)
    {
        float       cosI, cosT2, coeff;

        cosI   = -DotProduct(_normal);
        cosT2  = 1.0f - _ratioOfRefraction * _ratioOfRefraction * (1.0f - cosI * cosI);

        coeff  = _ratioOfRefraction * cosI - MindShake::Sqrt(MindShake::Abs(cosT2));
        *this *= _ratioOfRefraction;
        *this += coeff * _normal;

        // If the angle is too oblique, it will not penetrate the material.
        *this *= (cosT2 > 0);
    }

    //---------------------------------
    void
    CVector3::FastRefract(const CVector3 &_normal, float _coeff)
    {
        *this += (_normal * -_coeff);
    }

    //---------------------------------
    CVector3
    CVector3::GetRefracted(const CVector3 &_normal, float _ratioOfRefraction) const
    {
        float       cosI, cosT2, coeff;
        CVector3    result;

        cosI   = -DotProduct(_normal);
        cosT2  = 1.0f - _ratioOfRefraction * _ratioOfRefraction * (1.0f - cosI * cosI);

        coeff  = _ratioOfRefraction * cosI - MindShake::Sqrt(MindShake::Abs(cosT2));
        result = _ratioOfRefraction * *this + coeff * _normal;

        // If the angle is too oblique, it will not penetrate the material.
        return result * (cosT2 > 0);
    }

    //---------------------------------
    CVector3
    CVector3::GetFastRefracted(const CVector3 &_normal, float _coeff) const
    {
        return (_normal * -_coeff) + *this;
    }

    //---------------------------------

    //---------------------------------
    CVector3
    CVector3::GetRandomDeviant(float _angle, const CVector3 &_up) const
    {
        CVector3    newUp;
        CQuaternion q;

        if(_up == CVector3::kZERO)
            newUp = this->GetPerpendicular();
        else
            newUp = _up;

        // Rotate up vector by random amount around this
        q.FromAngleAxis(MindShake::FastRand2::UnitRandom() * MindShake::Float32::TWO_PI, *this);
        newUp = q * newUp;

        // Finally rotate this by given angle around randomised up
        q.FromAngleAxis(_angle, newUp);

        return q * (*this);
    }

    //---------------------------------
    float
    CVector3::GetAngleBetween(const CVector3 &_other) const
    {
        // signed angle
        return MindShake::ATan2(-PerpendicularDotProduct(_other), DotProduct(_other)) * Float32::RADTODEG;

        // unsigned angle
        // float lenProduct;
        // float _;

        // lenProduct = GetLength() * dest.Length();

        // // Divide by zero check
        // if(lenProduct < Float32::EPSILON)
            // lenProduct = Float32::EPSILON;

        // f = DotProduct(dest) / lenProduct;

        // f = MindShake::Clamp(f, (float)-1.0f, 1.0f);

        // return MindShake::ACos(f);
    }

    //---------------------------------
    void
    CVector3::Rotate(float _angle, const CVector3 &_up)
    {
        CVector3    newUp;
        CQuaternion q;

        if(_up == CVector3::kZERO)
            newUp = this->GetPerpendicular();
        else
            newUp = _up;

        q.FromAngleAxis(_angle * Float32::DEGTORAD, newUp);

        *this = q * (*this);
    }

    //---------------------------------
    void
    CVector3::RotateAboutX(float _angle)
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
    CVector3::RotateAboutY(float _angle)
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
    CVector3::RotateAboutZ(float _angle)
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
    CVector3
    CVector3::GetRotated(float _angle, const CVector3 &_up) const
    {
        CVector3    aux;

        aux = *this;
        aux.Rotate(_angle, _up);

        return aux;
    }

    //---------------------------------
    CVector3
    CVector3::GetRotateAboutX(float _angle)
    {
        CVector3    aux(*this);

        aux.RotateAboutX(_angle);

        return aux;
    }

    //---------------------------------
    CVector3
    CVector3::GetRotateAboutY(float _angle)
    {
        CVector3    aux(*this);

        aux.RotateAboutY(_angle);

        return aux;
    }

    //---------------------------------
    CVector3
    CVector3::GetRotateAboutZ(float _angle)
    {
        CVector3    aux(*this);

        aux.RotateAboutZ(_angle);

        return aux;
    }

    //---------------------------------
    void
    CVector3::Advance(float _angle, const CVector3 &_up, float _distance)
    {
        CVector3    aux;

        aux = *this;
        aux.Rotate(_angle, _up);
        aux *= _distance;

        *this += aux;
    }

    //---------------------------------
    CVector3
    CVector3::GetAdvanced(float _angle, const CVector3 &_up, float _distance) const
    {
        CVector3    aux;

        aux = *this;
        aux.Rotate(_angle, _up);
        aux *= _distance;

        aux += *this;

        return aux;
    }

    //---------------------------------

    //---------------------------------
    void
    CVector3::SetMin(const CVector3 &_other)
    {
        if(_other.x < x) x = _other.x;
        if(_other.y < y) y = _other.y;
        if(_other.z < z) z = _other.z;
    }

    //---------------------------------
    void
    CVector3::SetMin(float _x, float _y, float _z)
    {
        if (_x < x) x = _x;
        if (_y < y) y = _y;
        if (_z < z) z = _z;
    }

    //---------------------------------
    void
    CVector3::SetMax(const CVector3 &_other)
    {
        if(_other.x > x) x = _other.x;
        if(_other.y > y) y = _other.y;
        if(_other.z > z) z = _other.z;
    }

    //---------------------------------
    void
    CVector3::SetMax(float _x, float _y, float _z)
    {
        if (_x > x) x = _x;
        if (_y > y) y = _y;
        if (_z > z) z = _z;
    }

    //---------------------------------
    void
    CVector3::Abs()
    {
        x = MindShake::Abs(x);
        y = MindShake::Abs(y);
        z = MindShake::Abs(z);
    }

    //---------------------------------
    void
    CVector3::Floor()
    {
        x = MindShake::Floor(x);
        y = MindShake::Floor(y);
        z = MindShake::Floor(z);
    }

    //---------------------------------
    void
    CVector3::Ceil()
    {
        x = MindShake::Ceil(x);
        y = MindShake::Ceil(y);
        z = MindShake::Ceil(z);
    }

    //---------------------------------
    void
    CVector3::Expand()
    {
        x = MindShake::Expand(x);
        y = MindShake::Expand(y);
        z = MindShake::Expand(z);
    }

    //---------------------------------
    void
    CVector3::Round()
    {
        x = MindShake::Round(x);
        y = MindShake::Round(y);
        z = MindShake::Round(z);
    }

    //---------------------------------
    void
    CVector3::Trunc()
    {
        x = MindShake::Trunc(x);
        y = MindShake::Trunc(y);
        z = MindShake::Trunc(z);
    }

    //---------------------------------
    void
    CVector3::Frac()
    {
        x = MindShake::Frac(x);
        y = MindShake::Frac(y);
        z = MindShake::Frac(z);
    }

    //---------------------------------
    void
    CVector3::Clamp(float _min, float _max)
    {
        x = MindShake::Clamp(x, _min, _max);
        y = MindShake::Clamp(y, _min, _max);
        z = MindShake::Clamp(z, _min, _max);
    }

    //---------------------------------

    //---------------------------------
    bool
    CVector3::IsZeroLength() const
    {
        float sqlen;

        sqlen = x*x + y*y + z*z;

        return (sqlen < Float32::SQR_EPSILON);
    }

    //---------------------------------
    bool
    CVector3::IsNaN() const
    {
        return MindShake::IsNaN(x) || MindShake::IsNaN(y) || MindShake::IsNaN(z);
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    CVector2
    CVector3::GetXX() const {
        return CVector2(x, x);
    }

    //---------------------------------
    CVector2
    CVector3::GetXY() const {
        return CVector2(x, y);
    }

    //---------------------------------
    CVector2
    CVector3::GetXZ() const {
        return CVector2(x, z);
    }

    //---------------------------------
    CVector2
    CVector3::GetYX() const {
        return CVector2(y, x);
    }

    //---------------------------------
    CVector2
    CVector3::GetYY() const {
        return CVector2(y, y);
    }

    //---------------------------------
    CVector2
    CVector3::GetYZ() const {
        return CVector2(y, z);
    }

    //---------------------------------
    CVector2
    CVector3::GetZX() const {
        return CVector2(z, x);
    }

    //---------------------------------
    CVector2
    CVector3::GetZY() const {
        return CVector2(z, y);
    }

    //---------------------------------
    CVector2
    CVector3::GetZZ() const {
        return CVector2(z, z);
    }

    //---------------------------------
    CVector3
    CVector3::GetXXX() const
    {
        return CVector3(x);
    }

    //---------------------------------
    CVector3
    CVector3::GetXXY() const
    {
        return CVector3(x, x, y);
    }

    //---------------------------------
    CVector3
    CVector3::GetXXZ() const
    {
        return CVector3(x, x, z);
    }

    //---------------------------------
    CVector3
    CVector3::GetXYX() const
    {
        return CVector3(x, y, x);
    }


    //---------------------------------
    CVector3
    CVector3::GetXYY() const
    {
        return CVector3(x, y, y);
    }


    //---------------------------------
    CVector3
    CVector3::GetXYZ() const
    {
        return *this;
    }


    //---------------------------------
    CVector3
    CVector3::GetXZX() const
    {
        return CVector3(x, z, x);
    }


    //---------------------------------
    CVector3
    CVector3::GetXZY() const
    {
        return CVector3(x, z, y);
    }


    //---------------------------------
    CVector3
    CVector3::GetXZZ() const
    {
        return CVector3(x, z, z);
    }


    //---------------------------------
    CVector3
    CVector3::GetYXX() const
    {
        return CVector3(y, x, x);
    }


    //---------------------------------
    CVector3
    CVector3::GetYXY() const
    {
        return CVector3(y, x, y);
    }


    //---------------------------------
    CVector3
    CVector3::GetYXZ() const
    {
        return CVector3(y, x, z);
    }


    //---------------------------------
    CVector3
    CVector3::GetYYX() const
    {
        return CVector3(y, y, x);
    }


    //---------------------------------
    CVector3
    CVector3::GetYYY() const
    {
        return CVector3(y, y, y);
    }


    //---------------------------------
    CVector3
    CVector3::GetYYZ() const
    {
        return CVector3(y, y, z);
    }



    //---------------------------------
    CVector3
    CVector3::GetYZX() const
    {
        return CVector3(y, z, x);
    }


    //---------------------------------
    CVector3
    CVector3::GetYZY() const
    {
        return CVector3(y, z, y);
    }


    //---------------------------------
    CVector3
    CVector3::GetYZZ() const
    {
        return CVector3(y, z, z);
    }


    //---------------------------------
    CVector3
    CVector3::GetZXX() const
    {
        return CVector3(z, x, x);
    }


    //---------------------------------
    CVector3
    CVector3::GetZXY() const
    {
        return CVector3(z, x, y);
    }


    //---------------------------------
    CVector3
    CVector3::GetZXZ() const
    {
        return CVector3(z, x, z);
    }


    //---------------------------------
    CVector3
    CVector3::GetZYX() const
    {
        return CVector3(z, y, x);
    }


    //---------------------------------
    CVector3
    CVector3::GetZYY() const
    {
        return CVector3(z, y, y);
    }


    //---------------------------------
    CVector3
    CVector3::GetZYZ() const
    {
        return CVector3(z, y, z);
    }


    //---------------------------------
    CVector3
    CVector3::GetZZX() const
    {
        return CVector3(z, z, x);
    }


    //---------------------------------
    CVector3
    CVector3::GetZZY() const
    {
        return CVector3(z, z, y);
    }


    //---------------------------------
    CVector3
    CVector3::GetZZZ() const
    {
        return CVector3(z, z, z);
    }

    //---------------------------------

    //---------------------------------
    CVector3
    operator /(const CVector3 &_v1, const CVector3 &_v2)
    {
        CVector3    v(0);

        if(_v2.x != 0.0f)
            v.x = _v1.x / _v2.x;

        if(_v2.y != 0.0f)
            v.y = _v1.y / _v2.y;

        if(_v2.z != 0.0f)
            v.z = _v1.z / _v2.z;

        return v;
    }

    //---------------------------------
    CVector3
    operator /(float     _v1, const CVector3 &_v2)
    {
        CVector3    v(0);

        if(_v2.x != 0.0f)
            v.x = _v1 / _v2.x;

        if(_v2.y != 0.0f)
            v.y = _v1 / _v2.y;

        if(_v2.z != 0.0f)
            v.z = _v1 / _v2.z;

        return v;
    }

    //---------------------------------
    CVector3
    operator /(const CVector3 &_v1, float    _v2)
    {
        CVector3    v;
        float       aux;

        if(_v2 != 0.0f)
        {
            aux = 1.0f / _v2;
            v.x = _v1.x * aux;
            v.y = _v1.y * aux;
            v.z = _v1.z * aux;

            return v;
        }

        return CVector3(0);
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    float
    AbsDotProduct(const CVector3 &_v1, const CVector3 &_v2)
    {
        return MindShake::Abs(_v1.x * _v2.x) + MindShake::Abs(_v1.y * _v2.y) + MindShake::Abs(_v1.z * _v2.z);
    }

    //---------------------------------
    float
    PerpendicularDotProduct(const CVector3 &_v1, const CVector3 &_v2) 
    { 
        return DotProduct(_v1, GetPerpendicular(_v2)); 
    }
    
    //---------------------------------
    CVector3
    CrossProduct(const CVector3 &_v1, const CVector3 &_v2)
    {
        return CVector3(
            _v1.y * _v2.z - _v1.z * _v2.y,
            _v1.z * _v2.x - _v1.x * _v2.z,
            _v1.x * _v2.y - _v1.y * _v2.x);
    }

    //---------------------------------
    CVector3
    GetPerpendicular(const CVector3 &_vector)
    {
        CVector3 perp;

        perp = _vector.CrossProduct(CVector3::kUNIT_X);

        // Check Length
        if(perp.GetSquaredLength() < Float32::EPSILON)
            perp = _vector.CrossProduct(CVector3::kUNIT_Y);

        perp.Normalize();

        return perp;
    }

    //---------------------------------
    CVector3
    GetProjection(const CVector3 &_from, const CVector3 &_to)
    {
        float   dotProduct;
        float   sqrLength;
        float   aux;

        dotProduct = _to.DotProduct(_from);
        sqrLength  = _to.GetSquaredLength();
        if(sqrLength >= Float32::ZERO_EPSILON)
            aux = dotProduct / sqrLength;
        else
            aux = 0.0f;

        return CVector3(aux * _to.x, aux * _to.y, aux * _to.z);
    }

    //---------------------------------
    CVector3
    GetProjectionUnit(const CVector3 &_from, const CVector3 &_to)
    {
        float   dotProduct;

        dotProduct = _to.DotProduct(_from);

        return CVector3(dotProduct * _to.x, dotProduct * _to.y, dotProduct * _to.z);
    }

    //---------------------------------
    CVector3
    GetReflected(const CVector3 &_vector, const CVector3 &_normal)
    {
        return _vector - (2.0f * DotProduct(_vector, _normal) * _normal);
    }

    //---------------------------------
    CVector3
    GetReflected(const CVector3 &_vector, const CVector3 &_normal, float _elasticity)
    {
        return _vector - ((1.0f + _elasticity) * DotProduct(_vector, _normal) * _normal);
    }

    // At the output _ratioOfRefraction is inverted (1 / _ratioOfRefraction)
    //---------------------------------
    CVector3
    GetRefracted(const CVector3 &_vector, const CVector3 &_normal, float _ratioOfRefraction)
    {
        float       cosI, cosT2, coeff;
        CVector3    result;

        cosI   = DotProduct(-_vector, _normal);
        cosT2  = 1.0f - _ratioOfRefraction * _ratioOfRefraction * (1.0f - cosI * cosI);

        coeff  = _ratioOfRefraction * cosI - MindShake::Sqrt(MindShake::Abs(cosT2));
        result = _ratioOfRefraction * _vector + coeff * _normal;

        // If the angle is too oblique, it will not penetrate the material.
        return result * (cosT2 > 0);
    }

    //---------------------------------
    CVector3
    GetFastRefracted(const CVector3 &_vector, const CVector3 &_normal, float _coeff)
    {
        return (_normal * -_coeff) + _vector;
    }

    //---------------------------------
    float
    GetAngleBetween(const CVector3 &_v1, const CVector3 &_v2)
    {
        // signed angle
        return MindShake::ATan2(-PerpendicularDotProduct(_v1, _v2), DotProduct(_v1, _v2)) * Float32::RADTODEG;

        // unsigned angle
    //      float mod;
    //
    //      mod = _v1.GetLength() * _v2.Length();
    //      if(MindShake::Abs(mod) > Float32::EPSILON)
    //          mod = DotProduct(_v1, _v2) / mod;
    //      else
    //          return -1.0f;
    //
    //      mod = MindShake::Clamp(mod, -1.0f, 1.0f);
    //
    //      return MindShake::ACos(mod) * Float32::RADTODEG;
    }

    //---------------------------------
    CVector3
    Serp(const CVector3 &_v1, const CVector3 &_v2, float _theta)
    {
        float aux;

        aux = (1.0f - ::cosf(_theta * Float32::PI)) * 0.5f;

        return _v1*(1.0f - aux) + _v2*aux;
    }

    //---------------------------------
    CVector3
    Min(const CVector3 &_v1, const CVector3 &_v2)
    {
        return CVector3(MindShake::Min(_v1.x, _v2.x), MindShake::Min(_v1.y, _v2.y), MindShake::Min(_v1.z, _v2.z));
    }

    //---------------------------------
    CVector3
    Max(const CVector3 &_v1, const CVector3 &_v2)
    {
        return CVector3(MindShake::Max(_v1.x, _v2.x), MindShake::Max(_v1.y, _v2.y), MindShake::Max(_v1.z, _v2.z));
    }

    //---------------------------------
    CVector3
    Abs(const CVector3 &_v1)
    {
        return CVector3(MindShake::Abs(_v1.x), MindShake::Abs(_v1.y), MindShake::Abs(_v1.z));
    }

    //---------------------------------
    CVector3
    Floor(const CVector3 &_v1)
    {
        return CVector3(MindShake::Floor(_v1.x), MindShake::Floor(_v1.y), MindShake::Floor(_v1.z));
    }

    //---------------------------------
    CVector3
    Ceil(const CVector3 &_v1)
    {
        return CVector3(MindShake::Ceil(_v1.x), MindShake::Ceil(_v1.y), MindShake::Ceil(_v1.z));
    }

    //---------------------------------
    CVector3
    Expand(const CVector3 &_v1)
    {
        return CVector3(MindShake::Expand(_v1.x), MindShake::Expand(_v1.y), MindShake::Expand(_v1.z));
    }

    //---------------------------------
    CVector3
    Round(const CVector3 &_v1)
    {
        return CVector3(MindShake::Round(_v1.x), MindShake::Round(_v1.y), MindShake::Round(_v1.z));
    }

    //---------------------------------
    CVector3
    Trunc(const CVector3 &_v1)
    {
        return CVector3(MindShake::Trunc(_v1.x), MindShake::Trunc(_v1.y), MindShake::Trunc(_v1.z));
    }

    //---------------------------------
    CVector3
    Frac(const CVector3 &_v1)
    {
        return CVector3(MindShake::Frac(_v1.x), MindShake::Frac(_v1.y), MindShake::Frac(_v1.z));
    }

    //---------------------------------
    CVector3
    Clamp(const CVector3 &_v1, float _min, float _max)
    {
        return CVector3(MindShake::Clamp(_v1.x, _min, _max), MindShake::Clamp(_v1.y, _min, _max), MindShake::Clamp(_v1.z, _min, _max));
    }

} // end of namespace
