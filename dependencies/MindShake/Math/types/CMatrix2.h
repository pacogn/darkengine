#pragma once

//-------------------------------------
#include <cstddef>
#include <cassert>
//-------------------------------------

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    class CVector2;

    //---------------------------------
    class alignas(16) CMatrix2
    {
        public:
                            CMatrix2()                                          = default;
                            CMatrix2(const CMatrix2 &_other)                    = default;
                            ~CMatrix2()                                         = default;

            explicit        CMatrix2(float _radians);
                            CMatrix2(float _00, float _01, float _10, float _11) : m00(_00), m01(_01), m10(_10), m11(_11) { }

            CMatrix2 &      operator = (const CMatrix2 &_other)                 = default;

            float *         operator [] (size_t _row)                           { assert(_row < 2); return m[_row]; }
            const float *   operator [] (size_t _row) const                     { assert(_row < 2); return m[_row]; }

            float *         GetPtr()                                            { return &m[0][0]; }
            const float *   GetPtr() const                                      { return &m[0][0]; }

            bool            operator == (const CMatrix2 &_other) const;
            bool            operator != (const CMatrix2 &_other) const;

            bool            IsEqual   (const CMatrix2 &_other, float _tolerance = Float32::EPSILON) const;
            bool            IsNotEqual(const CMatrix2 &_other, float _tolerance = Float32::EPSILON) const;

            CMatrix2        operator + (const CMatrix2 &_other) const;
            CMatrix2        operator + (float _value) const                     { return CMatrix2(m00 + _value, m01 + _value, m10 + _value, m11 + _value); }

            CMatrix2        operator - (const CMatrix2 &_other) const;
            CMatrix2        operator - (float _value) const                     { return CMatrix2(m00 - _value, m01 - _value, m10 - _value, m11 - _value); }

            CMatrix2        operator - () const                                 { return CMatrix2(-m00, -m01, -m10, -m11); }

            CMatrix2        operator * (const CMatrix2 &_other) const;
            CVector2        operator * (const CVector2 &_vec2) const;
            CMatrix2        operator * (float _value) const                     { return CMatrix2(m00 * _value, m01 * _value, m10 * _value, m11 * _value); }

            void            Transpose();
            CMatrix2        GetTransposed() const                               { return CMatrix2(m00, m10, m01, m11); }

            bool            Invert(double _tolerance = Float64::EPSILON);
            bool            GetInverse(CMatrix2 &_rInverse, double _tolerance = Float64::EPSILON) const;
            CMatrix2        GetInverse(double _tolerance = Float64::EPSILON) const;

            float           GetDeterminant() const                              { return (m00 * m11) - (m01 * m10); }

            void            SetRotation(float _radians);

            CMatrix2        Abs() const;

            CVector2        AxisX() const;
            CVector2        AxisY() const;

        protected:
            union
            {
                struct
                {
                    float   m00, m01;
                    float   m10, m11;
                };

                float   m[2][2];
                float   v[4];
            };

    public:
            static const CMatrix2   kZERO;
            static const CMatrix2   kIDENTITY;
    };

} // end of namespace
