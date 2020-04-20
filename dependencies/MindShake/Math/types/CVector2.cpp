//-------------------------------------
#include <Common/Math/configMathLib.h>
#include <Common/Math/math_funcs.h>
//-------------------------------------
#include "CVector2.h"
//-------------------------------------
#include <Math/random/FastRand2.h>
//-------------------------------------


//-------------------------------------
namespace MindShake 
{

    //---------------------------------
    const CVector2  CVector2::kZERO(0.0f);
    const CVector2  CVector2::kONE(1.0f);
    const CVector2  CVector2::kUNIT_X(1, 0);
    const CVector2  CVector2::kUNIT_Y(0, 1);
    const CVector2  CVector2::kNEGATIVE_UNIT_X(-1, 0);
    const CVector2  CVector2::kNEGATIVE_UNIT_Y( 0, -1);
    //---------------------------------

    //---------------------------------
    void
    CVector2::Swap(CVector2 &_other)
    {
        MindShake::Swap(x, _other.x);
        MindShake::Swap(y, _other.y);
    }

    //---------------------------------

    //---------------------------------
    bool
    CVector2::IsEqual(const CVector2 &_other, float _tolerance) const
    {
        return MindShake::IsEqual(x, _other.x, _tolerance) &&
               MindShake::IsEqual(y, _other.y, _tolerance);
    }

    //---------------------------------
    bool
    CVector2::IsNotEqual(const CVector2 &_other, float _tolerance) const
    {
        return MindShake::IsNotEqual(x, _other.x, _tolerance) ||
               MindShake::IsNotEqual(y, _other.y, _tolerance);
    }

    //---------------------------------

    //---------------------------------
    void
    CVector2::operator /=(const CVector2 &_other)
    {
        if(IsNotZero(_other.x))
            x /= _other.x;

        if(IsNotZero(_other.y))
            y /= _other.y;
    }

    //---------------------------------
    void
    CVector2::operator /=(float _value)
    {
        float   inv;

        if(IsNotZero(_value))
        {
            inv = 1.0f / _value;
            x *= inv;
            y *= inv;
        }
    }

    // OJO: En MindShake la Y esta invertida, por lo que habrá que sumarle 180 grados a este valor
    //---------------------------------
    float
    CVector2::GetAngleBetween(const CVector2 &_other) const
    {
        // Signed angle
        return MindShake::ATan2(-PerpendicularDotProduct(_other), DotProduct(_other)) * Float32::RADTODEG;

        // unsigned angle
    //      float mod;
    //
    //      mod = GetLength() * _other.Length();
    //      if(MindShake::Abs(mod) > 0.00001f)
    //          mod = MindShake::DotProduct(*this, _other) / mod;
    //      else
    //          return -1.0f;
    //
    //      if(mod >=  1.0f) mod =  1.0f;
    //      if(mod <= -1.0f) mod = -1.0f;
    //
    //      return MindShake::ACos(mod) * Float32::RADTODEG;
    }

    //---------------------------------
    float
    CVector2::AbsDotProduct(const CVector2 &_other) const
    {
        return MindShake::Abs(x * _other.x) + MindShake::Abs(y * _other.y);
    }

    //---------------------------------
    float
    CVector2::GetLength() const
    {
        return MindShake::Sqrt(x*x + y*y);
    }

    //---------------------------------
    float
    CVector2::GetInverseLength() const
    {
        return MindShake::InvSqrt(x*x + y*y);
    }

    //---------------------------------
    float
    CVector2::GetFastInverseLength() const
    {
        return MindShake::FastInvSqrt(x*x + y*y);
    }

    //---------------------------------
    void
    CVector2::SetLength(float _length)
    {
        Normalize();
        x *= _length;
        y *= _length;
    }

    //---------------------------------
    void
    CVector2::SetMinLength(float _length)
    {
        float   len;
        float   aux = 0;

        len = MindShake::Sqrt(x*x + y*y);
        if(len < _length)
        {
            if(len != 0.0f)
                aux = (_length / len);

            x *= aux;
            y *= aux;
        }
    }

    //---------------------------------
    void
    CVector2::SetMaxLength(float _length)
    {
        float   len;
        float   aux = 0;

        len = MindShake::Sqrt(x*x + y*y);
        if(len > _length)
        {
            if(len != 0.0f)
                aux = (_length / len);

            x *= aux;
            y *= aux;
        }
    }

    //---------------------------------
    void
    CVector2::ClampLength(float _min, float _max)
    {
        float   len;
        float   aux;

        aux = MindShake::Sqrt(x*x + y*y);
        len = MindShake::Clamp(aux, _min, _max);
    // No vale la pena
    //      if(len != aux)
        {
            if(aux != 0.0f)
                aux = (len / aux);

            x *= aux;
            y *= aux;
        }
    }

    //---------------------------------
    void
    CVector2::Normalize()
    {
        float   aux;

        aux = MindShake::InvSqrt(x*x + y*y);
        x *= aux;
        y *= aux;
    }

    //---------------------------------
    float
    CVector2::NormalizeAndGetLength()
    {
        float   len;
        float   aux = 0;

        len = MindShake::Sqrt(x*x + y*y);
        if(IsNotZero(len))
            aux = 1.0f / len;

        x *= aux;
        y *= aux;

        return len;
    }

    //---------------------------------
    CVector2
    CVector2::GetNormalized() const
    {
        float   invLength;
        float   nx, ny;

        invLength = MindShake::InvSqrt(x*x + y*y);
        nx = x * invLength;
        ny = y * invLength;

        return CVector2(nx, ny);
    }

    //---------------------------------
    void
    CVector2::FastNormalize()
    {
        float   invLength;

        invLength = MindShake::FastInvSqrt(x*x + y*y);
        x *= invLength;
        y *= invLength;
    }

    //---------------------------------
    CVector2
    CVector2::GetFastNormalized() const
    {
        float   invLength;
        float   nx, ny;

        invLength = MindShake::FastInvSqrt(x*x + y*y);
        nx = x * invLength;
        ny = y * invLength;

        return CVector2(nx, ny);
    }

    // TODO: Revisar si ahora Y esta invertida (he cambiado la direccion de rotación)
    //---------------------------------
    void
    CVector2::Rotate(float _angle)
    {
        float s, c;
        float nx, ny;

        // MindShake rota al revés
        _angle *= -Float32::DEGTORAD;
        s = MindShake::Sin(_angle);
        c = MindShake::Cos(_angle);

        nx = c * x - s * y;
        ny = c * y + s * x;

        x = nx;
        y = ny;
    }

    // TODO: Revisar si ahora Y esta invertida (he cambiado la direccion de rotación)
    //---------------------------------
    CVector2
    CVector2::GetRotated(float _angle) const
    {
        float s, c;
        float nx, ny;

        // MindShake rota al revés
        _angle *= -Float32::DEGTORAD;
        s = MindShake::Sin(_angle);
        c = MindShake::Cos(_angle);

        nx = c * x - s * y;
        ny = c * y + s * x;

        return CVector2(nx, ny);
    }

    // TODO: Revisar si ahora Y esta invertida (he cambiado la direccion de rotación)
    //---------------------------------
    void
    CVector2::Advance(float _angle, float _distance)
    {
        float incX, incY;

        // MindShake rota al revés, pero aquí no afecta
        _angle *= Float32::DEGTORAD;
        incX = MindShake::Cos(_angle) * _distance;
        incY = MindShake::Sin(_angle) * _distance;

        x -= incX;
        y += incY;
    }

    // TODO: Revisar si ahora Y esta invertida (he cambiado la direccion de rotación)
    //---------------------------------
    CVector2
    CVector2::GetAdvanced(float _angle, float _distance)
    {
        float incX, incY;

        // MindShake rota al revés, pero aquí no afecta
        _angle *= Float32::DEGTORAD;
        incX = MindShake::Cos(_angle) * _distance;
        incY = MindShake::Sin(_angle) * _distance;

        return CVector2(x - incX, y + incY);
    }

    //---------------------------------
    CVector2
    CVector2::GetProjection(const CVector2 &_from) const
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

        return CVector2(aux * x, aux * y);
    }

    //---------------------------------
    CVector2
    CVector2::GetProjectionUnit(const CVector2 &_from) const
    {
        float   dotProduct;

        dotProduct = DotProduct(_from);

        return CVector2(dotProduct * x, dotProduct * y);
    }

    //---------------------------------
    void
    CVector2::Reflect(const CVector2 &_normal) 
    { 
        *this -= (2.0f * DotProduct(_normal) * _normal); 
    }

    //---------------------------------
    void
    CVector2::Reflect(const CVector2 &_normal, float _elasticity) 
    { 
        *this -= ((1.0f + _elasticity) * DotProduct(_normal) * _normal); 
    }
    //---------------------------------
    CVector2
    CVector2::GetReflected(const CVector2 &_normal) const
    {
        return CVector2(*this - (2.0f * DotProduct(_normal) * _normal));
    }

    //---------------------------------
    CVector2
    CVector2::GetReflected(const CVector2 &_normal, float _elasticity) const
    {
        return CVector2(*this - ((1.0f + _elasticity) * DotProduct(_normal) * _normal));
    }

    //---------------------------------
    void
    CVector2::Refract(const CVector2 &_normal, float _ratioOfRefraction)
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
    CVector2::FastRefract(const CVector2 &_normal, float _coeff)
    {
        *this += (_normal * -_coeff);
    }

    //---------------------------------
    CVector2
    CVector2::GetRefracted(const CVector2 &_normal, float _ratioOfRefraction) const
    {
        float       cosI, cosT2, coeff;
        CVector2    result;

        cosI   = -DotProduct(_normal);
        cosT2  = 1.0f - _ratioOfRefraction * _ratioOfRefraction * (1.0f - cosI * cosI);

        coeff  = _ratioOfRefraction * cosI - MindShake::Sqrt(MindShake::Abs(cosT2));
        result = _ratioOfRefraction * *this + coeff * _normal;

        // If the angle is too oblique, it will not penetrate the material.
        return result * (cosT2 > 0);
    }

    //---------------------------------
    CVector2
    CVector2::GetFastRefracted(const CVector2 &_normal, float _coeff) const
    {
        return (_normal * -_coeff) + *this;
    }

    //---------------------------------

    //---------------------------------
    CVector2
    CVector2::GetRandomDeviant(float angle) const
    {
        float cosa, sina;

        angle *=  MindShake::FastRand2::UnitRandom() * MindShake::Float32::TWO_PI;
        cosa = Cos(angle);
        sina = Sin(angle);

        return CVector2(cosa * x - sina * y, sina * x + cosa * y);
    }

    //---------------------------------
    bool
    CVector2::IsZeroLength() const
    {
        float sqlen = (x * x) + (y * y);

        return (sqlen < (1e-06 * 1e-06));
    }

    //---------------------------------
    bool
    CVector2::IsNaN() const
    {
        return MindShake::IsNaN(x) || MindShake::IsNaN(y);
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    void
    CVector2::SetMin(const CVector2 &_other)
    {
        if(x > _other.x)
            x = _other.x;

        if(y > _other.y)
            y = _other.y;
    }

    //---------------------------------
    void
    CVector2::SetMin(float _x, float _y)
    {
        if(x > _x)
            x = _x;

        if(y > _y)
            y = _y;
    }

    //---------------------------------
    void
    CVector2::SetMax(const CVector2 &_other)
    {
        if(x < _other.x)
            x = _other.x;

        if(y < _other.y)
            y = _other.y;
    }

    //---------------------------------
    void
    CVector2::SetMax(float _x, float _y)
    {
        if(x < _x)
            x = _x;

        if(y < _y)
            y = _y;
    }

    //---------------------------------
    void
    CVector2::Abs()
    {
        x = MindShake::Abs(x);
        y = MindShake::Abs(y);
    }

    //---------------------------------
    void
    CVector2::Floor()
    {
        x = MindShake::Floor(x);
        y = MindShake::Floor(y);
    }

    //---------------------------------
    void
    CVector2::Ceil()
    {
        x = MindShake::Ceil(x);
        y = MindShake::Ceil(y);
    }

    //---------------------------------
    void
    CVector2::Expand()
    {
        x = MindShake::Expand(x);
        y = MindShake::Expand(y);
    }

    //---------------------------------
    void
    CVector2::Round()
    {
        x = MindShake::Round(x);
        y = MindShake::Round(y);
    }

    //---------------------------------
    void
    CVector2::Trunc()
    {
        x = MindShake::Trunc(x);
        y = MindShake::Trunc(y);
    }

    //---------------------------------
    void
    CVector2::Frac()
    {
        x = MindShake::Frac(x);
        y = MindShake::Frac(y);
    }

    //---------------------------------
    void
    CVector2::Clamp(float _min, float _max)
    {
        x = MindShake::Clamp(x, _min, _max);
        y = MindShake::Clamp(y, _min, _max);
    }

    //---------------------------------

    //---------------------------------
    CVector2
    operator /(const CVector2 &_v1, const CVector2 &_v2)
    {
        CVector2    v(0);

        if(_v2.x != 0.0f)
            v.x = _v1.x / _v2.x;

        if(_v2.y != 0.0f)
            v.y = _v1.y / _v2.y;

        return v;
    }

    //---------------------------------
    CVector2
    operator /(float  _v1, const CVector2 &_v2)
    {
        CVector2    v(0);

        if(_v2.x != 0.0f)
            v.x = _v1 / _v2.x;

        if(_v2.y != 0.0f)
            v.y = _v1 / _v2.y;

        return v;
    }

    //---------------------------------
    CVector2
    operator /(const CVector2 &_v1, float _v2)
    {
        CVector2    v;
        float       aux;

        if(_v2 != 0.0f)
        {
            aux = 1.0f / _v2;
            v.x = _v1.x * aux;
            v.y = _v1.y * aux;

            return v;
        }

        return CVector2(0);
    }

    //---------------------------------
    //---------------------------------

    //---------------------------------
    float
    AbsDotProduct(const CVector2 &_v1, const CVector2 &_v2)
    {
        return MindShake::Abs(_v1.x * _v2.x) + MindShake::Abs(_v1.y * _v2.y);
    }

    //---------------------------------
    CVector2
    GetProjection(const CVector2 &_from, const CVector2 &_to)
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

        return CVector2(aux * _to.x, aux * _to.y);
    }

    //---------------------------------
    CVector2
    GetProjectionUnit(const CVector2 &_from, const CVector2 &_to)
    {
        float   dotProduct;

        dotProduct = _to.DotProduct(_from);

        return CVector2(dotProduct * _to.x, dotProduct * _to.y);
    }

    //---------------------------------
    CVector2
    GetReflected(const CVector2 &_vector, const CVector2 &_normal)
    {
        return _vector - (2.0f * DotProduct(_vector, _normal) * _normal);
    }

    //---------------------------------
    CVector2    
    GetReflected(const CVector2 &_vector, const CVector2 &_normal, float _elasticity)
    {
        return _vector - ((1.0f + _elasticity) * DotProduct(_vector, _normal) * _normal);
    }

    // At the output _ratioOfRefraction is inverted (1 / _ratioOfRefraction)
    //---------------------------------
    CVector2
    GetRefracted(const CVector2 &_vector, const CVector2 &_normal, float _ratioOfRefraction)
    {
        float       cosI, cosT2, coeff;
        CVector2    result;

        cosI   = DotProduct(-_vector, _normal);
        cosT2  = 1.0f - _ratioOfRefraction * _ratioOfRefraction * (1.0f - cosI * cosI);

        coeff  = _ratioOfRefraction * cosI - MindShake::Sqrt(MindShake::Abs(cosT2));
        result = _ratioOfRefraction * _vector + coeff * _normal;

        // If the angle is too oblique, it will not penetrate the material.
        return result * (cosT2 > 0);
    }

    //---------------------------------
    CVector2
    GetFastRefracted(const CVector2 &_vector, const CVector2 &_normal, float _coeff)
    {
        return (_normal * -_coeff) + _vector;
    }

    // OJO: En MindShake la Y esta invertida, por lo que habrá que sumarle 180 grados a este valor
    //---------------------------------
    float
    GetAngleBetween(const CVector2 &_v1, const CVector2 &_v2)
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
    CVector2
    Serp(const CVector2 &_v1, const CVector2 &_v2, float _theta)
    {
        float aux;

        aux = (1.0f - ::MindShake::Cos(_theta * Float32::PI)) * 0.5f;

        return _v1 * (1.0f - aux) + _v2*aux;
    }

    //---------------------------------
    CVector2
    Min(const CVector2 &_v1, const CVector2 &_v2)
    {
        return CVector2(MindShake::Min(_v1.x, _v2.x), MindShake::Min(_v1.y, _v2.y));
    }

    //---------------------------------
    CVector2
    Max(const CVector2 &_v1, const CVector2 &_v2)
    {
        return CVector2(MindShake::Max(_v1.x, _v2.x), MindShake::Max(_v1.y, _v2.y));
    }

    //---------------------------------
    CVector2
    Abs(const CVector2 &_v1)
    {
        return CVector2(MindShake::Abs(_v1.x), MindShake::Abs(_v1.y));
    }

    //---------------------------------
    CVector2
    Floor(const CVector2 &_v1)
    {
        return CVector2(MindShake::Floor(_v1.x), MindShake::Floor(_v1.y));
    }

    //---------------------------------
    CVector2
    Ceil(const CVector2 &_v1)
    {
        return CVector2(MindShake::Ceil(_v1.x), MindShake::Ceil(_v1.y));
    }

    //---------------------------------
    CVector2
    Expand(const CVector2 &_v1)
    {
        return CVector2(MindShake::Expand(_v1.x), MindShake::Expand(_v1.y));
    }

    //---------------------------------
    CVector2
    Round(const CVector2 &_v1)
    {
        return CVector2(MindShake::Round(_v1.x), MindShake::Round(_v1.y));
    }

    //---------------------------------
    CVector2
    Trunc(const CVector2 &_v1)
    {
        return CVector2(MindShake::Trunc(_v1.x), MindShake::Trunc(_v1.y));
    }

    //---------------------------------
    CVector2
    Frac(const CVector2 &_v1)
    {
        return CVector2(MindShake::Frac(_v1.x), MindShake::Frac(_v1.y));
    }

    //---------------------------------
    CVector2
    Clamp(const CVector2 &_v1, float _min, float _max)
    {
        return CVector2(MindShake::Clamp(_v1.x, _min, _max), MindShake::Clamp(_v1.y, _min, _max));
    }

    //---------------------------------
    CVector2
    GetDirectionVector(float _angle)
    {
        CVector2    result;

        _angle  *= Float32::DEGTORAD;
        result.x = MindShake::Cos(_angle);
        result.y = MindShake::Sin(_angle);

        return result;
    }

    //---------------------------------
    CVector2
    GetDirectionVector(float _angle, float _correctAngle)
    {
        CVector2    result;
        float       angle;

        angle    = (_angle - _correctAngle) * Float32::DEGTORAD;
        result.x = MindShake::Cos(angle);
        result.y = MindShake::Sin(angle);

        return result;
    }

} // end of namespace
