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
    class CMatrix3;
    class CVector3;
    //---------------------------------

    //---------------------------------
    class alignas(16) CQuaternion
    {
        public:
            friend CQuaternion operator * (float _value, const CQuaternion &_quat);

        public:
                            CQuaternion(const CQuaternion &_other)              = default;
                            ~CQuaternion()                                      = default;

                            CQuaternion(float _w = 1.0f, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : w(_w), x(_x), y(_y), z(_z) { }
                            CQuaternion(const CMatrix3 &_rot)                                                   { this->FromRotationMatrix(_rot);       }
                            CQuaternion(float _angle, const CVector3 &_axis)                                    { this->FromAngleAxis(_angle, _axis);   }
                            CQuaternion(const CVector3 &_xAxis, const CVector3 &_yAxis, const CVector3 &_zAxis) { this->FromAxes(_xAxis, _yAxis, _zAxis); }
                            CQuaternion(const CVector3 *_pAxis)                                                 { this->FromAxes(_pAxis); }
                            CQuaternion(float *_pV)                                                             { w = _pV[0]; x = _pV[1]; y = _pV[2]; z = _pV[3]; }

            CQuaternion &   operator = (const CQuaternion &_other)              = default;

            bool            operator == (const CQuaternion &_other) const       { return (_other.x == x) && (_other.y == y) && (_other.z == z) && (_other.w == w); }
            bool            operator != (const CQuaternion &_other) const       { return (_other.x != x) || (_other.y != y) || (_other.z != z) || (_other.w != w); }

            // Do not compare the components, compare if the quaternion is similar enough
            bool            IsEqual   (const CQuaternion &_other, float _tolerance=Float32::EPSILON) const;
            bool            IsNotEqual(const CQuaternion &_other, float _tolerance=Float32::EPSILON) const      { return !IsEqual(_other, _tolerance); }

            float           operator [] (const size_t _i) const                 { assert(_i < 4); return *(&w + _i); }
            float &         operator [] (const size_t _i)                       { assert(_i < 4); return *(&w + _i); }

            float *         GetPtr()                                            { return &w; }
            const float *   GetPtr() const                                      { return &w; }

            void            Swap(CQuaternion &_rOther);

            CQuaternion     operator + (const CQuaternion &_other) const        { return CQuaternion(w+_other.w, x+_other.x, y+_other.y, z+_other.z); }

            CQuaternion     operator - (const CQuaternion &_other) const        { return CQuaternion(w-_other.w, x-_other.x, y-_other.y, z-_other.z); }

            CQuaternion     operator * (const CQuaternion &_other) const;
            CVector3        operator * (const CVector3 &_vec3) const;           // rotation of a vector by a quaternion
            CQuaternion     operator * (float _value) const                     { return CQuaternion(_value * w, _value * x, _value * y, _value * z); }

            CQuaternion     operator - () const                                 { return CQuaternion(-w, -x, -y, -z); }

            CVector3        XAxis() const;
            CVector3        YAxis() const;
            CVector3        ZAxis() const;

            float           GetRoll(bool _reprojectAxis = true) const;  // X
            float           GetPitch(bool _reprojectAxis = true) const; // Y
            float           GetYaw(bool _reprojectAxis = true) const;   // Z
            
            CQuaternion &   FromEulerAngles(const CVector3 &_angles);
            CQuaternion &   FromEulerAngles(float _roll, float _pitch, float _yaw); // roll (X), pitch (Y), yaw (Z)
            void            ToEulerAngles(CVector3 &_angles) const;

            CQuaternion &   FromRotationMatrix(const CMatrix3 &_rRot);
            void            ToRotationMatrix(CMatrix3 &_rRot) const;

            CQuaternion &   FromAngleAxis(float _angle, const CVector3 &_axis); // Axis must be normalized
            void            ToAngleAxis(float &_rAngle, CVector3 &_rAxis) const;

            void            FromAxes(const CVector3 *_pAxis);
            void            FromAxes(const CVector3 & xAxis, const CVector3 & yAxis, const CVector3 & zAxis);

            void            ToAxes(CVector3 * _pAxis) const;
            void            ToAxes(CVector3 & xAxis, CVector3 & yAxis, CVector3 & zAxis) const;

            float           DotProduct(const CQuaternion &_other) const         { return w*_other.w + x*_other.x + y*_other.y + z*_other.z; }

            float           GetLength() const;
            float           GetSquaredLength() const                            { return w*w + x*x + y*y + z*z; }
            float           GetInverseLength() const;
            float           GetFastInverseLength() const;

            float           Normalize(void);

            CQuaternion     GetInverse() const;                                 // apply to non-zero quaternion
            CQuaternion     UnitInverse() const;                                // apply ONLY to a unit-length quaternion

            CQuaternion     Exp() const;
            CQuaternion     Log() const;

            bool            IsNaN() const;

        public:
            // spherical linear interpolation
            static
            CQuaternion     Slerp(float _T, const CQuaternion &_P, const CQuaternion &_Q, bool _shortestPath=false);

            static
            CQuaternion     SlerpExtraSpins(float _T, const CQuaternion & _P, const CQuaternion &_Q, int _extraSpins);

            // setup for spherical quadratic interpolation
            static
            void            Intermediate(const CQuaternion &_Q0, const CQuaternion &_Q1, const CQuaternion &_Q2, CQuaternion &_rA, CQuaternion &_rB);
            // spherical quadratic interpolation
            static
            CQuaternion     Squad(float _T, const CQuaternion &_P, const CQuaternion &_A, const CQuaternion &_B, const CQuaternion &_Q, bool _shortestPath=false);

            // normalized linear interpolation - faster but less accurate (non-constant rotation velocity)
            static
            CQuaternion     Nlerp(float _T, const CQuaternion &_P, const CQuaternion &_Q, bool _shortestPath = false);

        public:
            static const CQuaternion kZERO;
            static const CQuaternion kIDENTITY;

        public:
            float w, x, y, z;
    };

} // end of namespace
