#pragma once

//-------------------------------------
#include <Common/Math/constants.h>
//-------------------------------------
#include <cstddef>
#include <cassert>
//-------------------------------------

//-------------------------------------
// The(x,y,z) coordinate system is assumed to be right-handed.
// Coordinate axis rotation matrices are of the form
//   RX =   1       0       0
//          0      cos(t) -sin(t)
//          0      sin(t)  cos(t)
// where t > 0 indicates a counterclockwise rotation in the yz-plane
//
//   RY =  cos(t)   0      sin(t)
//          0       1       0
//        -sin(t)   0      cos(t)
// where t > 0 indicates a counterclockwise rotation in the zx-plane
//
//   RZ =  cos(t) -sin(t)   0
//         sin(t)  cos(t)   0
//          0       0       1
// where t > 0 indicates a counterclockwise rotation in the xy-plane.
//-------------------------------------

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    class CVector2;
    class CVector3;
    class CVector4;
    //---------------------------------

    //---------------------------------
    class CMatrix3
    {
        public:
            friend class CMatrix4;
            friend class CMatrix4_GL;

            friend CVector3 operator * (const CVector3 &_vec, const CMatrix3 &_matrix);
            friend CMatrix3 operator * (float _value, const CMatrix3 &_matrix);

        public:
                            CMatrix3()                                          = default;
                            CMatrix3(const CMatrix3 &_other)                    = default;
                            ~CMatrix3()                                         = default;

            template <typename T>
            explicit        CMatrix3(const T* _ptr);
                            CMatrix3(float _00, float _01, float _02,
                                     float _10, float _11, float _12,
                                     float _20, float _21, float _22);

            CMatrix3 &      operator = (const CMatrix3 &_other)                 = default;

            float *         operator [] (size_t _row)                           { assert(_row < 3); return m[_row]; }
            const float *   operator [] (size_t _row) const                     { assert(_row < 3); return m[_row]; }

            float *         GetPtr()                                            { return &v[0]; }
            const float *   GetPtr() const                                      { return &v[0]; }

            void            SetColumn(size_t _col, const CVector3 &_vec);
            void            SetColumns(const CVector3 &_v1, const CVector3 &_v2, const CVector3 &_v3);
            CVector3        GetColumn(size_t _col) const;

            void            Swap(CMatrix3 &_rOther);

            bool            operator == (const CMatrix3 &_other) const;
            bool            operator != (const CMatrix3 &_other) const;

            bool            IsEqual   (const CMatrix3 &_other, float _tolerance = Float32::EPSILON) const;
            bool            IsNotEqual(const CMatrix3 &_other, float _tolerance = Float32::EPSILON) const;

            // arithmetic operations
            CMatrix3        operator + (const CMatrix3 &_other) const;
            CMatrix3        operator - (const CMatrix3 &_other) const;
            CMatrix3        operator - () const;

            CMatrix3        operator * (const CMatrix3 &_other) const;
            CVector2        operator * (const CVector2 &_vec2) const;           // Z=0
            CVector3        operator * (const CVector3 &_vec3) const;
            CVector4        operator * (const CVector4 &_vec4) const;           // Ignore W
            CMatrix3        operator * (float _value) const;

            // utilities
            void            Transpose();
            CMatrix3        GetTransposed() const;

            bool            Invert(double _tolerance = Float64::EPSILON);
            bool            GetInverse(CMatrix3 &_rInverse, double _tolerance = Float64::EPSILON) const;
            CMatrix3        GetInverse(double _tolerance = Float64::EPSILON) const;

            float           GetDeterminant() const;
            
            // Q = rotation, D = scaling, U = shear
            void            QDUDecomposition(CMatrix3 &_matQ, CVector3 &_vecD, CVector3 &_vecU) const;

            void            ExtractScale(CVector3 &_scale) const;   // Based on QDUDecomposition
            bool            HasScale() const;

            void            FromAxes(const CVector3 &_xAxis, const CVector3 &_yAxis, const CVector3 &_zAxis);

            // Matrix must be orthonormal
            void            ToAxisAngle(CVector3 &_rAxis, float &_rAngle) const;
            void            FromAxisAngle(const CVector3 &_axis, float _angle);

            // yaw is rotation about the Up axis
            // pitch is rotation about the Right axis
            // roll is rotation about the Direction axis.
            bool            ToEulerAnglesXYZ(float &_yaw, float &_pitch, float &_roll) const;

            void            FromAngleX(float _angle);
            void            FromAngleY(float _angle);
            void            FromAngleZ(float _angle);

            void            FromEulerAnglesXYZ(float _yaw, float _pitch, float _roll);

        protected:
            union
            {
                struct
                {
                    float   m00, m01, m02;
                    float   m10, m11, m12;
                    float   m20, m21, m22;
                };

                float   m[3][3];
                float   v[9];
            };

        public:
            static const CMatrix3   kZERO;
            static const CMatrix3   kIDENTITY;
    };

    //-------------------------------------
    template <typename T>
    inline
    CMatrix3::CMatrix3(const T* _ptr)
    {
        assert(_ptr != nullptr);
        for (size_t i = 0; i < 3 * 3; ++i) {
            v[i] = float(_ptr[i]);
        }
    }

} // end of namespace
