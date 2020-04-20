//-------------------------------------
#include <Common/Math/configMathLib.h>
#include <Common/Math/math_funcs.h>
//-------------------------------------
#include "CMatrix2.h"
#include "CVector2.h"
//-------------------------------------

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    const CMatrix2  CMatrix2::kZERO    (0,0, 0,0);
    const CMatrix2  CMatrix2::kIDENTITY(1,0, 0,1);

    //---------------------------------
    CMatrix2::CMatrix2(float _radians)
    {
        float   fCos, fSin;

        fCos = Cos(_radians);
        fSin = Sin(_radians);

        m00  =  fCos;
        m01  = -fSin;
        m10  =  fSin;
        m11  =  fCos;
    }

    //---------------------------------

    //---------------------------------
    bool
    CMatrix2::operator == (const CMatrix2 &_other) const
    {
        for(size_t i = 0; i < 2*2; ++i)
        {
            if(v[i] != _other.v[i])
                return false;
        }

        return true;
    }

    //---------------------------------
    bool
    CMatrix2::operator != (const CMatrix2 &_other) const
    {
        for(size_t i = 0; i < 2*2; ++i)
        {
            if(v[i] != _other.v[i])
                return true;
        }

        return false;
    }

    //---------------------------------
    bool
    CMatrix2::IsEqual(const CMatrix2 &_other, float _tolerance) const
    {
        for(size_t i = 0; i < 2*2; ++i)
        {
            if(MindShake::IsNotEqual(v[i], _other.v[i], _tolerance))
                return false;
        }

        return true;
    }

    //---------------------------------
    bool
    CMatrix2::IsNotEqual(const CMatrix2 &_other, float _tolerance) const
    {
        for(size_t i = 0; i < 2*2; ++i)
        {
            if(MindShake::IsNotEqual(v[i], _other.v[i], _tolerance))
                return true;
        }

        return false;
    }

    //---------------------------------

    //---------------------------------
    CMatrix2
    CMatrix2::operator + (const CMatrix2 &_other) const
    {
        CMatrix2 result;

        for(size_t i = 0; i < 2*2; ++i)
        {
            result.v[i] = v[i] + _other.v[i];
        }

        return result;
    }

    //---------------------------------
    CMatrix2
    CMatrix2::operator - (const CMatrix2 &_other) const
    {
        CMatrix2 result;

        for(size_t i = 0; i < 2*2; ++i)
        {
            result.v[i] = v[i] - _other.v[i];
        }

        return result;
    }

    //---------------------------------
    CMatrix2
    CMatrix2::operator * (const CMatrix2 &_other) const
    {
        return CMatrix2(
                    m[0][0] * _other.m[0][0] + m[0][1] * _other.m[1][0],
                    m[0][0] * _other.m[0][1] + m[0][1] * _other.m[1][1],
                    m[1][0] * _other.m[0][0] + m[1][1] * _other.m[1][0],
                    m[1][0] * _other.m[0][1] + m[1][1] * _other.m[1][1]
                );
    }

    //---------------------------------
    CVector2
    CMatrix2::operator * (const CVector2 &_vec2) const
    {
        return CVector2(m00 * _vec2.x + m01 * _vec2.y, m10 * _vec2.x + m11 * _vec2.y);
    }

    //---------------------------------

    //---------------------------------
    bool
    CMatrix2::Invert(double _tolerance)
    {
        double  det;
        double  invDet;
        float   r00, r11;

        det = double(m00) * double(m11) - double(m01) * double(m10);
        if(MindShake::Abs(det) <= _tolerance)
            return false;

        invDet = 1.0 / det;

        r00 = float( m11 * invDet);
        m01 = float(-m01 * invDet);
        m10 = float(-m10 * invDet);
        r11 = float( m00 * invDet);

        m00 = r00;
        m11 = r11;

        return true;
    }

    //---------------------------------
    bool
    CMatrix2::GetInverse(CMatrix2 &_rInverse, double _tolerance) const
    {
        double  det;
        double  invDet;

        det = double(m00) * double(m11) - double(m01) * double(m10);
        if(MindShake::Abs(det) <= _tolerance)
            return false;

        invDet = 1.0 / det;

        _rInverse.m00 = float( m11 * invDet);
        _rInverse.m01 = float(-m01 * invDet);
        _rInverse.m10 = float(-m10 * invDet);
        _rInverse.m11 = float( m00 * invDet);

        return true;
    }

    //---------------------------------
    CMatrix2
    CMatrix2::GetInverse(double _tolerance) const
    {
        CMatrix2 inverse;

        if(GetInverse(inverse, _tolerance))
            return inverse;

        // Incorrect result
        return *this;
    }

    //---------------------------------

    //---------------------------------
    void
    CMatrix2::SetRotation(float _radians)
    {
        float   fCos, fSin;

        fCos = Cos(_radians);
        fSin = Sin(_radians);

        m00  =  fCos;
        m01  = -fSin;
        m10  =  fSin;
        m11  =  fCos;
    }

    //---------------------------------
    CMatrix2
    CMatrix2::Abs() const
    {
        return CMatrix2(MindShake::Abs(m00), MindShake::Abs(m01), MindShake::Abs(m10), MindShake::Abs(m11));
    }

    //---------------------------------
    CVector2
    CMatrix2::AxisX() const
    {
        return CVector2(m00, m10);
    }

    //---------------------------------
    CVector2
    CMatrix2::AxisY() const
    {
        return CVector2(m01, m11);
    }

} // end of namespace
