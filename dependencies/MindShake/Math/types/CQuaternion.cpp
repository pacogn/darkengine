//-------------------------------------
#include <Common/Math/configMathLib.h>
//-------------------------------------
#include "CQuaternion.h"
#include "CMatrix3.h"
#include "CVector3.h"
//-------------------------------------
#include <Common/Math/math_funcs.h>
//-------------------------------------


//-------------------------------------
namespace MindShake
{

    //---------------------------------
    const CQuaternion CQuaternion::kZERO(0.0f, 0.0f, 0.0f, 0.0f);
    const CQuaternion CQuaternion::kIDENTITY(1.0f, 0.0f, 0.0f, 0.0f);
    //---------------------------------

    //---------------------------------
    bool
    CQuaternion::IsEqual(const CQuaternion &_other, float _t) const
    {
        //float cosine = DotProduct(_other);
        //float angle  = MindShake::ACos(cosine);

        //return (MindShake::Abs(angle) <= _t) || MindShake::IsEqual(angle, MindShake::Float32::PI, _t);
        float dot = DotProduct(_other);
        return MindShake::IsEqual(MindShake::Abs(dot), 1.0f, _t);
    }

    //---------------------------------

    //---------------------------------
    void
    CQuaternion::Swap(CQuaternion &_rOther)
    {
        MindShake::Swap(w, _rOther.w);
        MindShake::Swap(x, _rOther.x);
        MindShake::Swap(y, _rOther.y);
        MindShake::Swap(z, _rOther.z);
    }

    //---------------------------------

    //---------------------------------
    // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
    // article "CQuaternion Calculus and Fast Animation".
    //---------------------------------
    CQuaternion &
    CQuaternion::FromRotationMatrix(const CMatrix3 &_rRot)
    {
        float       trace;
        float       root;
        uint32_t    i, j, k;

        trace = _rRot[0][0] + _rRot[1][1] + _rRot[2][2];
        if(trace > 0.0f)
        {
            // |w| > 1/2, may as well choose w > 1/2
            root = MindShake::Sqrt(trace + 1.0f);  // 2w
            w = 0.5f * root;
            root = 0.5f / root;  // 1/(4w)
            x =(_rRot[2][1] - _rRot[1][2]) * root;
            y =(_rRot[0][2] - _rRot[2][0]) * root;
            z =(_rRot[1][0] - _rRot[0][1]) * root;
        }
        else
        {
            // |w| <= 1/2
            static uint32_t s_iNext[3] = { 1, 2, 0 };

            i = 0;
            if(_rRot[1][1] > _rRot[0][0])
                i = 1;
            if(_rRot[2][2] > _rRot[i][i])
                i = 2;

            j = s_iNext[i];
            k = s_iNext[j];

            root = MindShake::Sqrt(_rRot[i][i] - _rRot[j][j] - _rRot[k][k] + 1.0f);

            float * pQuat[3] = { &x, &y, &z };
            *pQuat[i] = 0.5f * root;

            root = 0.5f / root;
            w =(_rRot[k][j] - _rRot[j][k]) * root;

            *pQuat[j] = (_rRot[j][i] + _rRot[i][j]) * root;
            *pQuat[k] = (_rRot[k][i] + _rRot[i][k]) * root;
        }

        return *this;
    }

    //---------------------------------
    void
    CQuaternion::ToRotationMatrix(CMatrix3 &_rRot) const
    {
        float Tx  = 2.0f * x;
        float Ty  = 2.0f * y;
        float Tz  = 2.0f * z;
        float Twx = Tx * w;
        float Twy = Ty * w;
        float Twz = Tz * w;
        float Txx = Tx * x;
        float Txy = Ty * x;
        float Txz = Tz * x;
        float Tyy = Ty * y;
        float Tyz = Tz * y;
        float Tzz = Tz * z;

        _rRot[0][0] = 1.0f -(Tyy + Tzz);
        _rRot[0][1] = Txy - Twz;
        _rRot[0][2] = Txz + Twy;
        _rRot[1][0] = Txy + Twz;
        _rRot[1][1] = 1.0f -(Txx + Tzz);
        _rRot[1][2] = Tyz - Twx;
        _rRot[2][0] = Txz - Twy;
        _rRot[2][1] = Tyz + Twx;
        _rRot[2][2] = 1.0f -(Txx + Tyy);
    }

    //---------------------------------

    //---------------------------------
    // The quaternion representing the rotation is
    //   q = cos(A / 2) + sin(A / 2) * (x * i+y * j + z * k)
    //---------------------------------
    CQuaternion &
    CQuaternion::FromAngleAxis(float _angle, const CVector3 &_axis)
    {
        float halfAngle;
        float fSin;

        // assert:  axis[] is unit length

        halfAngle = (0.5f * _angle);
        fSin      = MindShake::Sin(halfAngle);

        w = MindShake::Cos(halfAngle);
        x = fSin * _axis.x;
        y = fSin * _axis.y;
        z = fSin * _axis.z;

        return *this;
    }

    //---------------------------------
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
    //---------------------------------
    void
    CQuaternion::ToAngleAxis(float &_rAngle, CVector3 &_rAxis) const
    {
        float sqrLength;
        float invLength;

        sqrLength = x*x + y*y + z*z;
        if(sqrLength > 0.0f)
        {
            invLength = MindShake::InvSqrt(sqrLength);

            _rAngle  = 2.0f * MindShake::ACos(w);
            _rAxis.x = x * invLength;
            _rAxis.y = y * invLength;
            _rAxis.z = z * invLength;
        }
        else
        {
            // angle is 0(mod 2*pi), so any axis will do
            _rAngle  = 0.0f;
            _rAxis.x = 1.0f;
            _rAxis.y = 0.0f;
            _rAxis.z = 0.0f;
        }
    }

    //---------------------------------

    //---------------------------------
    void
    CQuaternion::FromAxes(const CVector3 *_pAxis)
    {
        CMatrix3 rot;

        assert(_pAxis != nullptr);
        for(size_t iCol = 0; iCol < 3; iCol++)
        {
            rot[0][iCol] = _pAxis[iCol].x;
            rot[1][iCol] = _pAxis[iCol].y;
            rot[2][iCol] = _pAxis[iCol].z;
        }

        FromRotationMatrix(rot);
    }

    //---------------------------------
    void
     CQuaternion::FromAxes(const CVector3 &_xAxis, const CVector3 &_yAxis, const CVector3 &_zAxis)
    {
        CMatrix3 rot;

        rot[0][0] = _xAxis.x;
        rot[1][0] = _xAxis.y;
        rot[2][0] = _xAxis.z;

        rot[0][1] = _yAxis.x;
        rot[1][1] = _yAxis.y;
        rot[2][1] = _yAxis.z;

        rot[0][2] = _zAxis.x;
        rot[1][2] = _zAxis.y;
        rot[2][2] = _zAxis.z;

        FromRotationMatrix(rot);

    }

    //---------------------------------
    void
    CQuaternion::ToAxes(CVector3 *_pAxis) const
    {
        CMatrix3 rot;

        ToRotationMatrix(rot);

        for(size_t iCol = 0; iCol < 3; iCol++)
        {
            _pAxis[iCol].x = rot[0][iCol];
            _pAxis[iCol].y = rot[1][iCol];
            _pAxis[iCol].z = rot[2][iCol];
        }
    }

    //---------------------------------
    void
    CQuaternion::ToAxes(CVector3 & _xAxis, CVector3 & _yAxis, CVector3 & _zAxis) const
    {
        CMatrix3 rot;

        ToRotationMatrix(rot);

        _xAxis.x = rot[0][0];
        _xAxis.y = rot[1][0];
        _xAxis.z = rot[2][0];

        _yAxis.x = rot[0][1];
        _yAxis.y = rot[1][1];
        _yAxis.z = rot[2][1];

        _zAxis.x = rot[0][2];
        _zAxis.y = rot[1][2];
        _zAxis.z = rot[2][2];
    }

    //---------------------------------

    //---------------------------------
    CVector3
    CQuaternion::XAxis() const
    {
        //float _Tx  = 2.0*x;
        float Ty  = 2.0f*y;
        float Tz  = 2.0f*z;
        float Twy = Ty*w;
        float Twz = Tz*w;
        float Txy = Ty*x;
        float Txz = Tz*x;
        float Tyy = Ty*y;
        float Tzz = Tz*z;

        return CVector3(1.0f - (Tyy+Tzz), Txy+Twz, Txz-Twy);
    }

    //---------------------------------
    CVector3
    CQuaternion::YAxis() const
    {
        float Tx  = 2.0f*x;
        float Ty  = 2.0f*y;
        float Tz  = 2.0f*z;
        float Twx = Tx*w;
        float Twz = Tz*w;
        float Txx = Tx*x;
        float Txy = Ty*x;
        float Tyz = Tz*y;
        float Tzz = Tz*z;

        return CVector3(Txy-Twz, 1.0f - (Txx+Tzz), Tyz+Twx);
    }

    //---------------------------------
    CVector3
    CQuaternion::ZAxis() const
    {
        float Tx  = 2.0f*x;
        float Ty  = 2.0f*y;
        float Tz  = 2.0f*z;
        float Twx = Tx*w;
        float Twy = Ty*w;
        float Txx = Tx*x;
        float Txz = Tz*x;
        float Tyy = Ty*y;
        float Tyz = Tz*y;

        return CVector3(Txz+Twy, Tyz-Twx, 1.0f - (Txx+Tyy));
    }

    //---------------------------------

    // NOTE:  Multiplication is not generally commutative, so in most
    // cases p*q != q*p.
    //---------------------------------
    CQuaternion
    CQuaternion::operator * (const CQuaternion &_other) const
    {
        return CQuaternion
       (
            w * _other.w - x * _other.x - y * _other.y - z * _other.z,
            w * _other.x + x * _other.w + y * _other.z - z * _other.y,
            w * _other.y + y * _other.w + z * _other.x - x * _other.z,
            w * _other.z + z * _other.w + x * _other.y - y * _other.x
       );
    }

    // nVidia SDK implementation
    //---------------------------------
    CVector3
    CQuaternion::operator * (const CVector3 &_vec3) const
    {
        CVector3    uv, uuv;
        CVector3    qvec(x, y, z);

        uv  = qvec.CrossProduct(_vec3);
        uuv = qvec.CrossProduct(uv);

        uv  *= 2.0f * w;
        uuv *= 2.0f;

        return _vec3 + uv + uuv;

    }

    //---------------------------------

    //---------------------------------
    float
    CQuaternion::GetLength() const
    {
        return MindShake::Sqrt(w*w + x*x + y*y + z*z);
    }

    //---------------------------------
    float
    CQuaternion::GetInverseLength() const
    {
        return MindShake::InvSqrt(w*w + x*x + y*y + z*z);
    }

    //---------------------------------
    float
    CQuaternion::GetFastInverseLength() const
    {
        return MindShake::FastInvSqrt(w*w + x*x + y*y + z*z);
    }

    //---------------------------------

    //---------------------------------
    CQuaternion
    CQuaternion::GetInverse() const
    {
        float length;
        float invLength;

        length = w*w + x*x + y*y + z*z;
        if(length > 0.0f)
        {
            invLength = 1.0f / length;
            return CQuaternion(w*invLength, -x*invLength, -y*invLength, -z*invLength);
        }
        else
        {
            // return an invalid result to flag the error
            return kZERO;
        }
    }

    //---------------------------------
    CQuaternion
    CQuaternion::UnitInverse() const
    {
        // assert:  'this' is unit length
        return CQuaternion(w, -x, -y, -z);
    }

    //---------------------------------

    // If q = A*(x*i+y*j+z*k) Where(x, y, z) is unit length, then
    // exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).
    // If Sin(A) is near zero,
    // use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/Sin(A) has limit 1.
    //---------------------------------
    CQuaternion
    CQuaternion::Exp() const
    {
        float       angle;
        float       fSin;
        float       coeff;
        CQuaternion result;

        angle = MindShake::Sqrt(x*x + y*y + z*z);
        fSin  = MindShake::Sin(angle);

        result.w = MindShake::Cos(angle);

        if(MindShake::Abs(fSin) >= Float32::EPSILON)
        {
            coeff = fSin / angle;

            result.x = coeff * x;
            result.y = coeff * y;
            result.z = coeff * z;
        }
        else
        {
            result.x = x;
            result.y = y;
            result.z = z;
        }

        return result;
    }

    // If q = cos(A)+sin(A)*(x*i+y*j+z*k) Where(x, y, z) is unit length, then
    // log(q) = A*(x*i+y*j+z*k).
    // If Sin(A) is near zero, use Log(q) =
    // sin(A)*(x*i+y*j+z*k) since Sin(A)/A has limit 1.
    //---------------------------------
    CQuaternion
    CQuaternion::Log() const
    {
        float       angle;
        float       fSin;
        float       coeff;
        CQuaternion result;

        result.w = 0.0f;

        if(MindShake::Abs(w) < 1.0f)
        {
            angle = MindShake::ACos(w);
            fSin  = MindShake::Sin(angle);
            if(MindShake::Abs(fSin) >= Float32::EPSILON)
            {
                coeff = angle / fSin;

                result.x = coeff*x;
                result.y = coeff*y;
                result.z = coeff*z;

                return result;
            }
        }

        result.x = x;
        result.y = y;
        result.z = z;

        return result;
    }

    //---------------------------------

    //---------------------------------
    CQuaternion
    CQuaternion::Slerp(float _T, const CQuaternion &_P, const CQuaternion &_Q, bool _shortestPath)
    {
        float       cosine;
        CQuaternion T;
        float       fSin;
        float       angle;
        float       invSin;
        float       coeff0;
        float       coeff1;

        cosine = _P.DotProduct(_Q);
        // Do we need to invert rotation?
        if(cosine < 0.0f && _shortestPath)
        {
            cosine = -cosine;
            T = -_Q;
        }
        else
        {
            T = _Q;
        }

        if(MindShake::Abs(cosine) < 1 - Float32::EPSILON)
        {
            // Standard case(slerp)
            fSin   = MindShake::Sqrt(1.0f - MindShake::Sqr(cosine));
            angle  = MindShake::ATan2(fSin, cosine);
            invSin = 1.0f / fSin;
            coeff0 = MindShake::Sin((1.0f - _T) * angle) * invSin;
            coeff1 = MindShake::Sin(_T * angle) * invSin;

            return coeff0 * _P + coeff1 * T;
        }
        else
        {
            // There are two situations:
            // 1. "_rP" and "_rQ" are very close(cosine ~= +1), so we can do a linear
            //  interpolation safely.
            // 2. "_rP" and "_rQ" are almost inverse of each _rQ(cosine ~= -1), there
            //  are an infinite number of possibilities interpolation. but we haven't
            //  have method to fix this case, so just use linear interpolation here.
            CQuaternion t = (1.0f - _T) * _P + _T * T;
            // taking the complement requires renormalisation
            t.Normalize();

            return t;
        }
    }

    //---------------------------------
    CQuaternion
    CQuaternion::SlerpExtraSpins(float _T, const CQuaternion & _P, const CQuaternion &_Q, int _extraSpins)
    {
        float cosine;
        float angle;
        float fSin;
        float phase;
        float invSin;
        float coeff0;
        float coeff1;

        cosine  = _P.DotProduct(_Q);
        angle =(MindShake::ACos(cosine));
        if(MindShake::Abs(angle) < Float32::EPSILON)
            return _P;

        fSin   = MindShake::Sin(angle);
        phase  = (MindShake::Float32::PI * _extraSpins * _T);
        invSin = 1.0f / fSin;
        coeff0 = MindShake::Sin((1.0f - _T) * angle - phase) * invSin;
        coeff1 = MindShake::Sin(_T * angle + phase) * invSin;

        return coeff0 * _P + coeff1 * _Q;
    }

    // assert:  q0, q1, q2 are unit quaternions
    //---------------------------------
    void
    CQuaternion::Intermediate(const CQuaternion &_Q0, const CQuaternion &_Q1, const CQuaternion &_Q2, CQuaternion &_rA, CQuaternion &_rB)
    {
        CQuaternion Q0inv;
        CQuaternion Q1inv;
        CQuaternion P0;
        CQuaternion P1;
        CQuaternion Arg;
        CQuaternion MinusArg;

        Q0inv   = _Q0.UnitInverse();
        Q1inv   = _Q1.UnitInverse();
        P0     = Q0inv * _Q1;
        P1     = Q1inv * _Q2;
        Arg   = 0.25 * (P0.Log() - P1.Log());
        MinusArg = -Arg;

        _rA = _Q1 * Arg.Exp();
        _rB = _Q1 * MinusArg.Exp();
    }

    //---------------------------------
    CQuaternion
    CQuaternion::Squad(float _T, const CQuaternion &_P, const CQuaternion &_A, const CQuaternion &_B, const CQuaternion &_Q, bool _shortestPath)
    {
        float       slerpT;
        CQuaternion slerpP;
        CQuaternion slerpQ;

        slerpT  = 2.0f * _T * (1.0f - _T);
        slerpP = Slerp(_T, _P, _Q, _shortestPath);
        slerpQ = Slerp(_T, _A, _B);

        return Slerp(slerpT, slerpP , slerpQ);
    }

    //---------------------------------
    float
    CQuaternion::Normalize()
    {
        float len;
        float invLen;

        len = GetLength();
        invLen = 1.0f / len;

        *this = *this * invLen;

        return len;
    }

    //---------------------------------

    // roll = atan2(localx.y, localx.x)
    //---------------------------------
    float
    CQuaternion::GetRoll(bool _reprojectAxis) const
    {
        if(_reprojectAxis)
        {
//          float Tx  = 2.0*x;
            float Ty  = 2.0f*y;
            float Tz  = 2.0f*z;
            float Twz = Tz*w;
            float Txy = Ty*x;
            float Tyy = Ty*y;
            float Tzz = Tz*z;

            return MindShake::ATan2(Txy+Twz, 1.0f - (Tyy+Tzz)) * Float32::RADTODEG;
        }
        else
        {
            return MindShake::ATan2(2.0f * (x*y + w*z), w*w + x*x - y*y - z*z) * Float32::RADTODEG;
        }
    }

    // pitch = atan2(localy.z, localy.y)
    //---------------------------------
    float
    CQuaternion::GetPitch(bool _reprojectAxis) const
    {
        if(_reprojectAxis)
        {
            float Tx  = 2.0f*x;
//          float Ty  = 2.0f*y;
            float Tz  = 2.0f*z;
            float Twx = Tx*w;
            float Txx = Tx*x;
            float Tyz = Tz*y;
            float Tzz = Tz*z;

            return MindShake::ATan2(Tyz+Twx, 1.0f - (Txx+Tzz)) * Float32::RADTODEG;
        }
        else
        {
            return MindShake::ATan2(2.0f * (y*z + w*x), w*w - x*x - y*y + z*z) * Float32::RADTODEG;
        }
    }

    // yaw = atan2(localz.x, localz.z)
    //---------------------------------
    float CQuaternion::GetYaw(bool _reprojectAxis) const
    {
        if(_reprojectAxis)
        {
            float Tx  = 2.0f*x;
            float Ty  = 2.0f*y;
            float Tz  = 2.0f*z;
            float Twy = Ty*w;
            float Txx = Tx*x;
            float Txz = Tz*x;
            float Tyy = Ty*y;

            return MindShake::ATan2(Txz+Twy, 1.0f - (Txx+Tyy)) * Float32::RADTODEG;
        }
        else
        {
            return float(MindShake::ASin(-2.0f * (x*z - w*y))) * Float32::RADTODEG;
        }
    }

    //---------------------------------

    //---------------------------------
    CQuaternion &
    CQuaternion::FromEulerAngles(const CVector3 &_angles) 
    {
        return FromEulerAngles(_angles.x, _angles.y, _angles.z);
    }

    //---------------------------------
    CQuaternion &
    CQuaternion::FromEulerAngles(float _roll, float _pitch, float _yaw)
    {
        float cosR = MindShake::CosG(_roll  * 0.5f);
        float sinR = MindShake::SinG(_roll  * 0.5f);
        float cosY = MindShake::CosG(_yaw   * 0.5f);
        float sinY = MindShake::SinG(_yaw   * 0.5f);
        float cosP = MindShake::CosG(_pitch * 0.5f);
        float sinP = MindShake::SinG(_pitch * 0.5f);

        w = cosR * cosY * cosP + sinR * sinY * sinP;
        x = cosR * cosY * sinP - sinR * sinY * cosP;
        y = sinR * cosY * sinP + cosR * sinY * cosP;
        z = sinR * cosY * cosP - cosR * sinY * sinP;

        return *this;
    }

    //---------------------------------
    void
    CQuaternion::ToEulerAngles(CVector3 &_angles) const
    {
        float sinr_cosp =     2 * (w * x + y * z);
        float cosr_cosp = 1 - 2 * (x * x + y * y);
        _angles.y = MindShake::ATan2(sinr_cosp, cosr_cosp) * Float32::RADTODEG;

        float sinp = 2 * (w * y - z * x);
        if (MindShake::Abs(sinp) >= 1)
            _angles.z = MindShake::Sign(sinp) * Float32::HALF_PI * Float32::RADTODEG; // use 90 degrees if out of range
        else
            _angles.z = MindShake::ASin(sinp) * Float32::RADTODEG;

        float siny_cosp =     2 * (w * z + x * y);
        float cosy_cosp = 1 - 2 * (y * y + z * z);
        _angles.x = MindShake::ATan2(siny_cosp, cosy_cosp) * Float32::RADTODEG;
    }

    //---------------------------------

    //---------------------------------
    CQuaternion
    CQuaternion::Nlerp(float _T, const CQuaternion &_P, const CQuaternion &_Q, bool _shortestPath)
    {
        CQuaternion result;
        float       cosine;

        cosine = _P.DotProduct(_Q);
        if(cosine < 0.0f && _shortestPath)
        {
            result = _P + _T * ((-_Q) - _P);
        }
        else
        {
            result = _P + _T * (_Q - _P);
        }
        result.Normalize();

        return result;
    }

    //---------------------------------
    bool
    CQuaternion::IsNaN() const
    {
        return MindShake::IsNaN(x) || MindShake::IsNaN(y) || MindShake::IsNaN(z) || MindShake::IsNaN(w);
    }

    //---------------------------------

    //---------------------------------
    CQuaternion
    operator * (float _value, const CQuaternion &_quat)
    {
        return CQuaternion(_value * _quat.w, _value * _quat.x, _value * _quat.y, _value * _quat.z);
    }

} // end of namespace

