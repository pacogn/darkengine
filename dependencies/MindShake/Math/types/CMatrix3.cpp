//-------------------------------------
#include <Common/Math/configMathLib.h>
#include <Common/Math/math_funcs.h>
//-------------------------------------
#include "CMatrix3.h"
#include "CVector4.h"
#include "CVector3.h"
#include "CVector2.h"
//-------------------------------------
#include <cassert>
//-------------------------------------

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    const CMatrix3  CMatrix3::kZERO    (0,0,0, 0,0,0, 0,0,0);
    const CMatrix3  CMatrix3::kIDENTITY(1,0,0, 0,1,0, 0,0,1);
    //---------------------------------

    //---------------------------------
    CMatrix3::CMatrix3(float _00, float _01, float _02,
                       float _10, float _11, float _12,
                       float _20, float _21, float _22)
    {
        m[0][0] = _00;
        m[0][1] = _01;
        m[0][2] = _02;
        m[1][0] = _10;
        m[1][1] = _11;
        m[1][2] = _12;
        m[2][0] = _20;
        m[2][1] = _21;
        m[2][2] = _22;
    }

    //---------------------------------

    //---------------------------------
    bool
    CMatrix3::operator == (const CMatrix3 &_other) const
    {
        for(size_t i = 0; i < 3*3; ++i)
        {
            if(v[i] != _other.v[i])
                return false;
        }

        return true;
    }

    //---------------------------------
    bool
    CMatrix3::operator != (const CMatrix3 &_other) const
    {
        for(size_t i = 0; i < 3*3; ++i)
        {
            if(v[i] != _other.v[i])
                return true;
        }

        return false;
    }

    //---------------------------------
    bool
    CMatrix3::IsEqual(const CMatrix3 &_other, float _tolerance) const
    {
        for(size_t i = 0; i < 3*3; ++i)
        {
            if(MindShake::IsNotEqual(v[i], _other.v[i], _tolerance))
                return false;
        }

        return true;
    }

    //---------------------------------
    bool
    CMatrix3::IsNotEqual(const CMatrix3 &_other, float _tolerance) const
    {
        for(size_t i = 0; i < 3*3; ++i)
        {
            if(MindShake::IsNotEqual(v[i], _other.v[i], _tolerance))
                return true;
        }

        return false;
    }

    //---------------------------------

    //---------------------------------
    void
    CMatrix3::Swap(CMatrix3 &_rOther)
    {
        for(size_t i = 0; i < 3*3; ++i)
            MindShake::Swap(v[i], _rOther.v[i]);
    }

    //---------------------------------
    void
    CMatrix3::SetColumn(size_t col, const CVector3 &_vec)
    {
        assert(col < 3);
        m[0][col] = _vec.x;
        m[1][col] = _vec.y;
        m[2][col] = _vec.z;
    }

    //---------------------------------
    void
    CMatrix3::SetColumns(const CVector3 &_v1, const CVector3 &_v2, const CVector3 &_v3)
    {
        m[0][0] = _v1.x;
        m[1][0] = _v1.y;
        m[2][0] = _v1.z;

        m[0][1] = _v2.x;
        m[1][1] = _v2.y;
        m[2][1] = _v2.z;

        m[0][2] = _v3.x;
        m[1][2] = _v3.y;
        m[2][2] = _v3.z;
    }

    //---------------------------------
    CVector3
    CMatrix3::GetColumn(size_t col) const
    {
        assert(col < 3);
        return CVector3(m[0][col], m[1][col], m[2][col]);
    }

    //---------------------------------
    void
    CMatrix3::FromAxes(const CVector3 &_xAxis, const CVector3 &_yAxis, const CVector3 &_zAxis)
    {
        SetColumns(_xAxis, _yAxis, _zAxis);
    }

    //---------------------------------
    // arithmetic operations
    //---------------------------------

    //---------------------------------
    CMatrix3
    CMatrix3::operator + (const CMatrix3 &_other) const
    {
        CMatrix3 result;

        for(size_t i = 0; i < 3*3; ++i)
        {
            result.v[i] = v[i] + _other.v[i];
        }

        return result;
    }

    //---------------------------------
    CMatrix3
    CMatrix3::operator - (const CMatrix3 &_other) const
    {
        CMatrix3 result;

        for(size_t i = 0; i < 3*3; ++i)
        {
            result.v[i] = v[i] - _other.v[i];
        }

        return result;
    }

    //---------------------------------
    CMatrix3
    CMatrix3::operator - () const
    {
        CMatrix3 result;

        for(size_t i = 0; i < 3*3; ++i)
        {
            result.v[i] = -v[i];
        }

        return result;
    }

    //---------------------------------
    CMatrix3
    CMatrix3::operator * (const CMatrix3 &_other) const
    {
        CMatrix3 prod;

        for(size_t row = 0; row < 3; ++row)
        {
            for(size_t col = 0; col < 3; ++col)
            {
                prod.m[row][col] =
                    m[row][0] * _other.m[0][col] +
                    m[row][1] * _other.m[1][col] +
                    m[row][2] * _other.m[2][col];
            }
        }

        return prod;
    }

    //---------------------------------
    CVector2
    CMatrix3::operator * (const CVector2 &_vec2) const
    {
        return CVector2(
            m[0][0] * _vec2.x + m[0][1] * _vec2.y,
            m[1][0] * _vec2.x + m[1][1] * _vec2.y
        );
    }

    //---------------------------------
    CVector3
    CMatrix3::operator * (const CVector3 &_vec3) const
    {
        return CVector3(
            m[0][0] * _vec3.x + m[0][1] * _vec3.y + m[0][2] * _vec3.z,
            m[1][0] * _vec3.x + m[1][1] * _vec3.y + m[1][2] * _vec3.z,
            m[2][0] * _vec3.x + m[2][1] * _vec3.y + m[2][2] * _vec3.z
        );
    }

    //---------------------------------
    CVector4
    CMatrix3::operator * (const CVector4 &_vec4) const
    {
        return CVector4(
            m[0][0] * _vec4.x + m[0][1] * _vec4.y + m[0][2] * _vec4.z,
            m[1][0] * _vec4.x + m[1][1] * _vec4.y + m[1][2] * _vec4.z,
            m[2][0] * _vec4.x + m[2][1] * _vec4.y + m[2][2] * _vec4.z,
            1.0f
        );
    }

    //---------------------------------
    CMatrix3
    CMatrix3::operator * (float _value) const
    {
        CMatrix3 result;

        for(size_t i = 0; i < 3*3; ++i)
        {
            result.v[i] = v[i] * _value;
        }

        return result;
    }

    //---------------------------------

    //---------------------------------
    void
    CMatrix3::Transpose()
    {
        float   tmp1, tmp2, tmp3;

        tmp1    = m[0][1];
        tmp2    = m[0][2];
        tmp3    = m[1][2];

        m[0][1] = m[1][0];
        m[0][2] = m[2][0];
        m[1][2] = m[2][1];

        m[1][0] = tmp1;
        m[2][0] = tmp2;
        m[2][1] = tmp3;
    }

    //---------------------------------
    CMatrix3
    CMatrix3::GetTransposed() const
    {
        CMatrix3    transpose;

        for(size_t row = 0; row < 3; ++row)
        {
            for(size_t col = 0; col < 3; ++col)
                transpose.m[row][col] = m[col][row];
        }

        return transpose;
    }

    //---------------------------------
    bool
    CMatrix3::Invert(double _tolerance) 
    {
        CMatrix3 inverse;
        size_t  i;
        double  det, invDet;

        inverse.m[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
        inverse.m[0][1] = m[0][2] * m[2][1] - m[0][1] * m[2][2];
        inverse.m[0][2] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
        inverse.m[1][0] = m[1][2] * m[2][0] - m[1][0] * m[2][2];
        inverse.m[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
        inverse.m[1][2] = m[0][2] * m[1][0] - m[0][0] * m[1][2];
        inverse.m[2][0] = m[1][0] * m[2][1] - m[1][1] * m[2][0];
        inverse.m[2][1] = m[0][1] * m[2][0] - m[0][0] * m[2][1];
        inverse.m[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];

        det = double(m[0][0]) * inverse.m[0][0] + double(m[0][1]) * inverse.m[1][0] + double(m[0][2]) * inverse.m[2][0];
        if(MindShake::IsZero(det, _tolerance))
            return false;

        invDet = 1.0 / det;
        for(i=0; i<3*3; ++i)
        {
            v[i] = float(inverse.v[i] * invDet);
        }

        return true;
    }

    //---------------------------------
    // Invert a 3x3 using cofactors.  This is about 8 times faster than
    // the Numerical Recipes code which uses Gaussian elimination.
    //---------------------------------
    bool
    CMatrix3::GetInverse(CMatrix3 &_rInverse, double _tolerance) const
    {
        size_t  i;
        double  det, invDet;

        _rInverse.m[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
        _rInverse.m[0][1] = m[0][2] * m[2][1] - m[0][1] * m[2][2];
        _rInverse.m[0][2] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
        _rInverse.m[1][0] = m[1][2] * m[2][0] - m[1][0] * m[2][2];
        _rInverse.m[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
        _rInverse.m[1][2] = m[0][2] * m[1][0] - m[0][0] * m[1][2];
        _rInverse.m[2][0] = m[1][0] * m[2][1] - m[1][1] * m[2][0];
        _rInverse.m[2][1] = m[0][1] * m[2][0] - m[0][0] * m[2][1];
        _rInverse.m[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];

        det = double(m[0][0]) * _rInverse.m[0][0] + double(m[0][1]) * _rInverse.m[1][0] + double(m[0][2]) * _rInverse.m[2][0];
        if(MindShake::IsZero(det, _tolerance))
            return false;

        invDet = 1.0 / det;
        for(i=0; i<3*3; ++i)
        {
            _rInverse.v[i] = float(_rInverse.v[i] * invDet);
        }

        return true;
    }

    //---------------------------------
    CMatrix3
    CMatrix3::GetInverse(double _tolerance) const
    {
        CMatrix3 inverse;

        if(GetInverse(inverse, _tolerance))
            return inverse;

        // Incorrect result
        return *this;
    }

    //---------------------------------
    float
    CMatrix3::GetDeterminant() const
    {
        float   cofactor00;
        float   cofactor10;
        float   cofactor20;
        float   det;

        cofactor00 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
        cofactor10 = m[1][2] * m[2][0] - m[1][0] * m[2][2];
        cofactor20 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

        det = (m[0][0] * cofactor00) + (m[0][1] * cofactor10) + (m[0][2] * cofactor20);

        return det;
    }

    //---------------------------------

    // Orthogonal Q (Rotation)
    // Diagonal D (Scaling)
    // Upper triangular U stored as (u01, u02, u12) (Shear)
    //---------------------------------
    void
    CMatrix3::QDUDecomposition(CMatrix3 &_matQ, CVector3 &_vecD, CVector3 &_vecU) const
    {
        size_t      row, col;
        float       invLength;
        float       dot;
        float       det;
        float       invD0;
        CMatrix3    matR;

        invLength    = MindShake::InvSqrt(m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]);
        _matQ[0][0]  = m[0][0] * invLength;
        _matQ[1][0]  = m[1][0] * invLength;
        _matQ[2][0]  = m[2][0] * invLength;
                     
        dot          = _matQ[0][0] * m[0][1] + _matQ[1][0] * m[1][1] + _matQ[2][0] * m[2][1];
        _matQ[0][1]  = m[0][1]-dot * _matQ[0][0];
        _matQ[1][1]  = m[1][1]-dot * _matQ[1][0];
        _matQ[2][1]  = m[2][1]-dot * _matQ[2][0];

        invLength     = MindShake::InvSqrt(_matQ[0][1] * _matQ[0][1] + _matQ[1][1] * _matQ[1][1] + _matQ[2][1] * _matQ[2][1]);        
        _matQ[0][1]  *= invLength;
        _matQ[1][1]  *= invLength;
        _matQ[2][1]  *= invLength;

        dot          = _matQ[0][0] * m[0][2] + _matQ[1][0] * m[1][2] + _matQ[2][0] * m[2][2];
        _matQ[0][2]  = m[0][2]-dot * _matQ[0][0];
        _matQ[1][2]  = m[1][2]-dot * _matQ[1][0];
        _matQ[2][2]  = m[2][2]-dot * _matQ[2][0];

        dot          = _matQ[0][1] * m[0][2] + _matQ[1][1] * m[1][2] + _matQ[2][1] * m[2][2];
        _matQ[0][2] -= dot * _matQ[0][1];
        _matQ[1][2] -= dot * _matQ[1][1];
        _matQ[2][2] -= dot * _matQ[2][1];

        invLength    = MindShake::InvSqrt(_matQ[0][2] * _matQ[0][2] + _matQ[1][2] * _matQ[1][2] + _matQ[2][2] * _matQ[2][2]);
        _matQ[0][2] *= invLength;
        _matQ[1][2] *= invLength;
        _matQ[2][2] *= invLength;

        // guarantee that orthogonal matrix has determinant 1 (no reflections)
        det = _matQ[0][0] * _matQ[1][1] * _matQ[2][2] + _matQ[0][1] * _matQ[1][2] * _matQ[2][0] +
              _matQ[0][2] * _matQ[1][0] * _matQ[2][1] - _matQ[0][2] * _matQ[1][1] * _matQ[2][0] -
              _matQ[0][1] * _matQ[1][0] * _matQ[2][2] - _matQ[0][0] * _matQ[1][2] * _matQ[2][1];

        if(det < 0.0f)
        {
            for(row = 0; row < 3; row++)
            {
                for(col = 0; col < 3; col++)
                {
                    _matQ[row][col] = -_matQ[row][col];
                }
            }
        }

        // build "right" matrix R
        matR[0][0] = _matQ[0][0] * m[0][0] + _matQ[1][0] * m[1][0] + _matQ[2][0] * m[2][0];
        matR[0][1] = _matQ[0][0] * m[0][1] + _matQ[1][0] * m[1][1] + _matQ[2][0] * m[2][1];
        matR[1][1] = _matQ[0][1] * m[0][1] + _matQ[1][1] * m[1][1] + _matQ[2][1] * m[2][1];
        matR[0][2] = _matQ[0][0] * m[0][2] + _matQ[1][0] * m[1][2] + _matQ[2][0] * m[2][2];
        matR[1][2] = _matQ[0][1] * m[0][2] + _matQ[1][1] * m[1][2] + _matQ[2][1] * m[2][2];
        matR[2][2] = _matQ[0][2] * m[0][2] + _matQ[1][2] * m[1][2] + _matQ[2][2] * m[2][2];

        // the scaling component
        _vecD.x = matR[0][0];
        _vecD.y = matR[1][1];
        _vecD.z = matR[2][2];

        // the shear component
        invD0   = 1.0f / _vecD.x;
        _vecU.x = matR[0][1] * invD0;
        _vecU.y = matR[0][2] * invD0;
        _vecU.z = matR[1][2] / _vecD.y;
    }

    //---------------------------------

    // Based on QDUDecomposition 
    //---------------------------------
    void
    CMatrix3::ExtractScale(CVector3 &_scale) const
    {
        size_t      row, col;
        float       invLength;
        float       dot;
        float       det;
        CMatrix3    matQ;

        invLength   = MindShake::InvSqrt(m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]);
        matQ[0][0]  = m[0][0] * invLength;
        matQ[1][0]  = m[1][0] * invLength;
        matQ[2][0]  = m[2][0] * invLength;
                     
        dot         = matQ[0][0] * m[0][1] + matQ[1][0] * m[1][1] + matQ[2][0] * m[2][1];
        matQ[0][1]  = m[0][1]-dot * matQ[0][0];
        matQ[1][1]  = m[1][1]-dot * matQ[1][0];
        matQ[2][1]  = m[2][1]-dot * matQ[2][0];

        invLength    = MindShake::InvSqrt(matQ[0][1] * matQ[0][1] + matQ[1][1] * matQ[1][1] + matQ[2][1] * matQ[2][1]);        
        matQ[0][1]  *= invLength;
        matQ[1][1]  *= invLength;
        matQ[2][1]  *= invLength;

        dot         = matQ[0][0] * m[0][2] + matQ[1][0] * m[1][2] + matQ[2][0] * m[2][2];
        matQ[0][2]  = m[0][2]-dot * matQ[0][0];
        matQ[1][2]  = m[1][2]-dot * matQ[1][0];
        matQ[2][2]  = m[2][2]-dot * matQ[2][0];

        dot         = matQ[0][1] * m[0][2] + matQ[1][1] * m[1][2] + matQ[2][1] * m[2][2];
        matQ[0][2] -= dot * matQ[0][1];
        matQ[1][2] -= dot * matQ[1][1];
        matQ[2][2] -= dot * matQ[2][1];

        invLength   = MindShake::InvSqrt(matQ[0][2] * matQ[0][2] + matQ[1][2] * matQ[1][2] + matQ[2][2] * matQ[2][2]);
        matQ[0][2] *= invLength;
        matQ[1][2] *= invLength;
        matQ[2][2] *= invLength;

        // guarantee that orthogonal matrix has determinant 1 (no reflections)
        det = matQ[0][0] * matQ[1][1] * matQ[2][2] + matQ[0][1] * matQ[1][2] * matQ[2][0] +
              matQ[0][2] * matQ[1][0] * matQ[2][1] - matQ[0][2] * matQ[1][1] * matQ[2][0] -
              matQ[0][1] * matQ[1][0] * matQ[2][2] - matQ[0][0] * matQ[1][2] * matQ[2][1];

        if(det < 0.0f)
        {
            for(row = 0; row < 3; row++)
            {
                for(col = 0; col < 3; col++)
                {
                    matQ[row][col] = -matQ[row][col];
                }
            }
        }

        // the scaling component
        _scale.x = matQ[0][0] * m[0][0] + matQ[1][0] * m[1][0] + matQ[2][0] * m[2][0];
        _scale.y = matQ[0][1] * m[0][1] + matQ[1][1] * m[1][1] + matQ[2][1] * m[2][1];
        _scale.z = matQ[0][2] * m[0][2] + matQ[1][2] * m[1][2] + matQ[2][2] * m[2][2];
    }

    //-----------------------------
    // check magnitude of local axes
    //-----------------------------
    bool
    CMatrix3::HasScale() const
    {
        float   t;

        t = m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0];
        if(MindShake::IsNotEqual(t, 1.0f, Float32::EPSILON))
            return true;

        t = m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1];
        if(MindShake::IsNotEqual(t, 1.0f, Float32::EPSILON))
            return true;

        t = m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2];
        if(MindShake::IsNotEqual(t, 1.0f, Float32::EPSILON))
            return true;

        return false;
    }

    //---------------------------------

    //---------------------------------
    // Let(x,y,z) be the unit-length axis and let A be an angle of rotation.
    // The rotation matrix is R = I + sin(A)*P +(1-Cos(A))*P^2 where
    // I is the identity and
    //
    //       +-        -+
    //   P = |  0 -z +y |
    //       | +z  0 -x |
    //       | -y +x  0 |
    //       +-        -+
    //
    // If A > 0, R represents a counterclockwise rotation about the axis in
    // the sense of looking from the tip of the axis vector towards the
    // origin.  Some algebra will show that
    //
    //   cos(A) =(trace(R)-1)/2  and  R - R^t = 2*Sin(A)*P
    //
    // In the event that A = pi, R-R^t = 0 which prevents us from extracting
    // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
    // P^2 =(R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
    // z^2-1.  We can solve these for axis(x,y,z).  Because the angle is pi,
    // it does not matter which sign you choose on the square roots.
    //---------------------------------
    void
    CMatrix3::ToAxisAngle(CVector3 &_rAxis, float &_rAngle) const
    {
        float   trace;
        float   fCos;
        float   halfInverse;

        trace = m[0][0] + m[1][1] + m[2][2];
        fCos  = 0.5f * (trace-1.0f);

        _rAngle = MindShake::ACos(fCos);                                        // [0, PI]

        if(_rAngle > 0.0f)
        {
            if(_rAngle < Float32::PI)
            {
                _rAxis.x = m[2][1]-m[1][2];
                _rAxis.y = m[0][2]-m[2][0];
                _rAxis.z = m[1][0]-m[0][1];
                _rAxis.Normalize();
            }
            else
            {
                // angle is PI
                if(m[0][0] >= m[1][1])
                {
                    // r00 >= r11
                    if(m[0][0] >= m[2][2])
                    {
                        // r00 is maximum diagonal term
                        _rAxis.x = 0.5f * MindShake::Sqrt(m[0][0] - m[1][1] - m[2][2] + 1.0f);
                        halfInverse = 0.5f / _rAxis.x;

                        _rAxis.y = halfInverse * m[0][1];
                        _rAxis.z = halfInverse * m[0][2];
                    }
                    else
                    {
                        // r22 is maximum diagonal term
                        _rAxis.z = 0.5f * MindShake::Sqrt(m[2][2] - m[0][0] - m[1][1] + 1.0f);
                        halfInverse = 0.5f / _rAxis.z;

                        _rAxis.x = halfInverse * m[0][2];
                        _rAxis.y = halfInverse * m[1][2];
                    }
                }
                else
                {
                    // r11 > r00
                    if(m[1][1] >= m[2][2])
                    {
                        // r11 is maximum diagonal term
                        _rAxis.y = 0.5f * MindShake::Sqrt(m[1][1] - m[0][0] - m[2][2] + 1.0f);
                        halfInverse  = 0.5f / _rAxis.y;

                        _rAxis.x = halfInverse * m[0][1];
                        _rAxis.z = halfInverse * m[1][2];
                    }
                    else
                    {
                        // r22 is maximum diagonal term
                        _rAxis.z = 0.5f * MindShake::Sqrt(m[2][2] - m[0][0] - m[1][1] + 1.0f);
                        halfInverse = 0.5f / _rAxis.z;

                        _rAxis.x = halfInverse * m[0][2];
                        _rAxis.y = halfInverse * m[1][2];
                    }
                }
            }
        }
        else
        {
            // The angle is 0 and the matrix is the identity.  Any axis will
            // work, so just use the x-axis.
            _rAxis.x = 1.0f;
            _rAxis.y = 0.0f;
            _rAxis.z = 0.0f;
        }
    }

    //---------------------------------
    void
    CMatrix3::FromAxisAngle(const CVector3 &_axis, float _angle)
    {
        float   fCos, fSin;
        float   oneMinusCos;
        float   x2, y2, z2;
        float   xym, xzm, yzm;
        float   xSin, ySin, zSin;

        fCos = MindShake::Cos(_angle);
        fSin = MindShake::Sin(_angle);

        oneMinusCos = 1.0f - fCos;

        x2   = _axis.x * _axis.x;
        y2   = _axis.y * _axis.y;
        z2   = _axis.z * _axis.z;

        xym  = _axis.x * _axis.y * oneMinusCos;
        xzm  = _axis.x * _axis.z * oneMinusCos;
        yzm  = _axis.y * _axis.z * oneMinusCos;

        xSin = _axis.x * fSin;
        ySin = _axis.y * fSin;
        zSin = _axis.z * fSin;

        m[0][0] = x2 * oneMinusCos + fCos;
        m[0][1] = xym - zSin;
        m[0][2] = xzm + ySin;

        m[1][0] = xym + zSin;
        m[1][1] = y2 * oneMinusCos + fCos;
        m[1][2] = yzm - xSin;

        m[2][0] = xzm - ySin;
        m[2][1] = yzm + xSin;
        m[2][2] = z2  * oneMinusCos + fCos;
    }

    //---------------------------------

    //---------------------------------
    bool
    CMatrix3::ToEulerAnglesXYZ(float &_yaw, float &_pitch, float &_roll) const
    {
        float angle;

        _pitch = float(MindShake::ASin(m[0][2]));
        //_pitch = -MindShake::ASin(m[0][2]);
        //float cosPitch = MindShake::Cos(_pitch);
        //float inv_cos_cosPitch = 1.0f / cosPitch;

        if(_pitch < Float32::HALF_PI)
        {
            if(_pitch > -Float32::HALF_PI)
            {
                _yaw  = MindShake::ATan2(-m[1][2], m[2][2]);
                _roll = MindShake::ATan2(-m[0][1], m[0][0]);                
                //_yaw  = atan2(m[1][2] * cosPitch, m[2][2] * cosPitch);
                //_roll = atan2(m[0][1] * cosPitch, m[0][0] * cosPitch);

                return true;
            }
            else
            {
                // WARNING.  Not a unique solution.
                angle  = MindShake::ATan2(m[1][0], m[1][1]);
                _roll = 0.0f;  // any angle works
                _yaw  = _roll - angle;

                return false;
            }
        }
        else
        {
            // WARNING.  Not a unique solution.
            angle = MindShake::ATan2(m[1][0], m[1][1]);
            _roll = 0.0f;  // any angle works
            _yaw  = angle - _roll;

            return false;
        }

    }

    //---------------------------------
    void
    CMatrix3::FromAngleX(float _angle)
    {
        float fCos, fSin;

        fCos = MindShake::Cos(_angle);
        fSin = MindShake::Sin(_angle);

        m[0][0] = 1.0f;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;

        m[1][0] = 0.0f;
        m[1][1] = fCos;
        m[1][2] = -fSin;

        m[2][0] = 0.0f;
        m[2][1] = fSin;
        m[2][2] = fCos;
    }

    //---------------------------------
    void
    CMatrix3::FromAngleY(float _angle)
    {
        float fCos, fSin;

        fCos = MindShake::Cos(_angle);
        fSin = MindShake::Sin(_angle);

        m[0][0] = fCos;
        m[0][1] = 0.0f;
        m[0][2] = fSin;

        m[1][0] = 0.0f;
        m[1][1] = 1.0f;
        m[1][2] = 0.0f;

        m[2][0] = -fSin;
        m[2][1] = 0.0f;
        m[2][2] = fCos;
    }

    //---------------------------------
    void
    CMatrix3::FromAngleZ(float _angle)
    {
        float fCos, fSin;

        fCos = MindShake::Cos(_angle);
        fSin = MindShake::Sin(_angle);

        m[0][0] = fCos;
        m[0][1] = -fSin;
        m[0][2] = 0.0f;

        m[1][0] = fSin;
        m[1][1] = fCos;
        m[1][2] = 0.0f;

        m[2][0] = 0.0f;
        m[2][1] = 0.0f;
        m[2][2] = 1.0f;
    }

    //---------------------------------

    //---------------------------------
    void
    CMatrix3::FromEulerAnglesXYZ(float _yaw, float _pitch, float _roll)
    {
        float fCos, fSin;

        fCos = MindShake::Cos(_yaw);
        fSin = MindShake::Sin(_yaw);
        CMatrix3 matX(
                    1.0f, 0.0f, 0.0f,
                    0.0f, fCos, -fSin,
                    0.0f, fSin, fCos);

        fCos = MindShake::Cos(_pitch);
        fSin = MindShake::Sin(_pitch);
        CMatrix3 matY(
                    fCos, 0.0f, fSin,
                    0.0f, 1.0f, 0.0f,
                    -fSin, 0.0f, fCos);

        fCos = MindShake::Cos(_roll);
        fSin = MindShake::Sin(_roll);
        CMatrix3 matZ(
                    fCos, -fSin, 0.0f,
                    fSin, fCos, 0.0f,
                    0.0f, 0.0f, 1.0f);

        *this = matX * (matY * matZ);
    }

    //---------------------------------
    CVector3
    operator * (const CVector3 &_vec, const CMatrix3 &_matrix)
    {
        return CVector3(
            _vec.x * _matrix.m[0][0] + _vec.y * _matrix.m[1][0] + _vec.z * _matrix.m[2][0],
            _vec.x * _matrix.m[0][1] + _vec.y * _matrix.m[1][1] + _vec.z * _matrix.m[2][1],
            _vec.x * _matrix.m[0][2] + _vec.y * _matrix.m[1][2] + _vec.z * _matrix.m[2][2]
        );
    }

    //---------------------------------
    CMatrix3
    operator * (float _value, const CMatrix3 &_matrix)
    {
        CMatrix3 result;

        for (size_t i = 0; i < 3 * 3; ++i) {
            result.v[i] = _matrix.v[i] * _value;
        }

        return result;
    }

} // end of namespace
