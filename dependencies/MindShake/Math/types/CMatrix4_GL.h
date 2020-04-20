#pragma once

#include <Common/Math/constants.h>
//-------------------------------------
#include <cstddef>

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    class CVector2;
    class CVector3;
    class CVector4;
    class CMatrix3;
    class CQuaternion;
    //---------------------------------

    //---------------------------------
    // The elements of the matrix are stored as column major order.
    // OpenGL code is often using a right-handed coordinate system, 
    // column-major matrices, column vectors, and post-multiplication.
    //---------------------------------
    // Memory: 
    //  | column0 column1 column2 colum3 |
    // Logical representation: scale and translation
    //  | sx  0  0 tx |
    //  |  0 sy  0 ty |
    //  |  0  0 sz tz |
    //  |  0  0  0  1 |
    // v: 
    //  |  0  4  8 12 |
    //  |  1  5  9 13 |
    //  |  2  6 10 14 |
    //  |  3  7 11 15 |
    // m:
    //  | m[0][0]  m[1][0]  m[2][0]  m[3][0] |
    //  | m[0][1]  m[1][1]  m[2][1]  m[3][1] |
    //  | m[0][2]  m[1][2]  m[2][2]  m[3][2] |
    //  | m[0][3]  m[1][3]  m[2][3]  m[3][3] |
    //---------------------------------

    //---------------------------------
    class alignas(16) CMatrix4
    {
        public:
                            CMatrix4()                          = default;
                            CMatrix4(const CMatrix4 &_other)    = default;
                            ~CMatrix4()                         = default;

                            CMatrix4(float _m00, float _m01, float _m02, float _m03,
                                     float _m10, float _m11, float _m12, float _m13,
                                     float _m20, float _m21, float _m22, float _m23,
                                     float _m30, float _m31, float _m32, float _m33);

            template <typename T>
            explicit        CMatrix4(const T *_ptr);
                            CMatrix4(const CMatrix3    &_mat3);
                            CMatrix4(const CQuaternion &_quat);

            CMatrix4 &      operator = (const CMatrix4 &_other)  = default;
            CMatrix4 &      operator = (const CMatrix3    &_mat3);
            CMatrix4 &      operator = (const CQuaternion &_quat);

            CMatrix4 &      Set(float _m00, float _m01, float _m02, float _m03,
                                float _m10, float _m11, float _m12, float _m13,
                                float _m20, float _m21, float _m22, float _m23,
                                float _m30, float _m31, float _m32, float _m33);
            CMatrix4 &      Set(const CMatrix4 &_other);
            CMatrix4 &      Set(const CMatrix3 &_mat3);
            CMatrix4 &      Set(const CQuaternion &_quat);

            // Remember this matrix is column major
            void            SetRow(int _index, const float _row[4]);
            void            SetRow(int _index, const CVector4 &_vec4);
            void            SetRow(int _index, const CVector3 &_vec3);
            CVector4        GetRow(int _index) const;

            // Remember this matrix is column major
            void            SetColumn(int _index, const float _col[4]);
            void            SetColumn(int _index, const CVector4 &_vec4);
            void            SetColumn(int _index, const CVector3 &_vec3);
            CVector4        GetColumn(int _index) const;

            float *         operator [] (size_t _row);
            const float *   operator [] (size_t _row) const;

            float *         GetPtr();
            const float *   GetPtr() const;

            void            Swap(CMatrix4 &_other);

            bool            operator == (const CMatrix4 &_other) const;
            bool            operator != (const CMatrix4 &_other) const;

            bool            IsEqual   (const CMatrix4 &_other, float _tolerance = Float32::EPSILON) const;
            bool            IsNotEqual(const CMatrix4 &_other, float _tolerance = Float32::EPSILON) const;

            CMatrix4        operator + (const CMatrix4 &_other) const;
            CMatrix4        operator - (const CMatrix4 &_other) const;

            CMatrix4 &      Concatenate(const CMatrix4 &_other);
            CMatrix4        GetConcatenated(const CMatrix4 &_other) const;
            CMatrix4        operator * (const CMatrix4 &_other) const;
            // v' = M * v
            CVector2        operator * (const CVector2 &_vec2) const;           // Z = 0, W = 1
            CVector3        operator * (const CVector3 &_vec3) const;           // W = 1
            CVector4        operator * (const CVector4 &_vec4) const;
            CMatrix4        operator * (float _value) const;

            // An affine matrix is a 4x4 matrix with row 3 equal to (0, 0, 0, 1)
            bool            IsAffine() const;
            CMatrix4 &      InvertAffine();
            CMatrix4        GetInverseAffine() const;

            CMatrix4 &      ConcatenateAffine(const CMatrix4 &_other);
            CMatrix4        GetConcatenatedAffine(const CMatrix4 &_other) const;

            CVector2        TransformAffine(const CVector2 &_vec2) const;
            CVector3        TransformAffine(const CVector3 &_vec3) const;
            CVector4        TransformAffine(const CVector4 &_vec4) const;

            // Transpose
            CMatrix4 &      Transpose();
            CMatrix4        GetTransposed() const;

            // Translation
            CMatrix4 &      SetTranslation(const CVector3 &_vec3);
            CMatrix4 &      SetTranslation(float _tx, float _ty, float _tz);

            CMatrix4 &      Translate(const CVector3 &_vec3);
            CMatrix4 &      Translate(float _tx, float _ty, float _tz);

            CMatrix4 &      TranslateAffine(const CVector3 &_vec3);
            CMatrix4 &      TranslateAffine(float _tx, float _ty, float _tz);

            CMatrix4 &      PreTranslate(const CVector3 &_vec3);
            CMatrix4 &      PreTranslate(float _tx, float _ty, float _tz);

            CMatrix4 &      PreTranslateAffine(const CVector3 &_vec3);
            CMatrix4 &      PreTranslateAffine(float _tx, float _ty, float _tz);

            CVector3        GetTranslation() const;
            float           GetTranslationX() const;
            float           GetTranslationY() const;
            float           GetTranslationZ() const;

            CMatrix4 &      MakeTranslation(const CVector3 &_vec3);
            CMatrix4 &      MakeTranslation(float _tx, float _ty, float _tz);

            // Rotation
            CMatrix4 &      Rotate(const CVector3 &_angles);
            CMatrix4 &      Rotate(float _angleX, float _angleY, float _angleZ);
            CMatrix4 &      Rotate(float _angle, const CVector3 &_axis);
            CMatrix4 &      Rotate(float _angle, float _axisX, float _axisY, float _axisZ);
            CMatrix4 &      Rotate(const CMatrix3 &_mat3);
            CMatrix4 &      Rotate(const CQuaternion &_quat);

            CMatrix4 &      MakeRotation(const CVector3 &_angles);
            CMatrix4 &      MakeRotation(float _angleX, float _angleY, float _angleZ);
            CMatrix4 &      MakeRotation(float _angle, const CVector3 &_axis);
            CMatrix4 &      MakeRotation(float _angle, float _axisX, float _axisY, float _axisZ);
            CMatrix4 &      MakeRotation(const CMatrix3 &_mat3);
            CMatrix4 &      MakeRotation(const CQuaternion &_quat);
            CVector3        GetAngles() const;

            // Scale
            CMatrix4 &      SetScale(const CVector3 &_vec3);
            CMatrix4 &      SetScale(float _sx, float _sy, float _sz);

            CMatrix4 &      Scale(const CVector3 &_vec3);
            CMatrix4 &      Scale(float _sx, float _sy, float _sz);

            CMatrix4 &      ScaleAffine(const CVector3 &_vec3);
            CMatrix4 &      ScaleAffine(float _sx, float _sy, float _sz);

            CMatrix4 &      PreScale(const CVector3 &_vec3);
            CMatrix4 &      PreScale(float _sx, float _sy, float _sz);

            CMatrix4 &      PreScaleAffine(const CVector3 &_vec3);
            CMatrix4 &      PreScaleAffine(float _sx, float _sy, float _sz);

            bool            HasScale() const;
            bool            HasNegativeScale() const;

            CMatrix4 &      MakeScale(const CVector3 &_vec3);
            CMatrix4 &      MakeScale(float _sx, float _sy, float _sz);

            // Combined Transform
            CMatrix4 &      MakeTransform(const CVector3 &_position, const CVector3 &_scale, const CQuaternion &_orientation);
            CMatrix4 &      MakeTransform(const CVector3 &_position, const CVector3 &_scale, const CVector3 &_angles);
            CMatrix4 &      MakeTransform(const CVector3 &_position, const CVector3 &_scale, float _angleZ);    // For sprites
            CMatrix4 &      MakeTransform(const CVector3 &_position, const CVector3 &_scale);                   // For Layers

            CMatrix4 &      MakeTransform(float _posX,   float _posY,   float _posZ,
                                          float _scaleX, float _scaleY, float _scaleZ,
                                          float _angleX, float _angleY, float _angleZ);

            CMatrix4 &      MakeTransform(float _posX,   float _posY,   float _posZ,
                                          float _scaleX, float _scaleY, float _scaleZ,
                                          float _angleZ);                                                       // For sprites

            CMatrix4 &      MakeTransform(float _posX,   float _posY,   float _posZ,
                                          float _scaleX, float _scaleY, float _scaleZ);                         // For Layers

            CMatrix4 &      MakeInverseTransform(const CVector3 &_position, const CVector3 &_scale, const CQuaternion &_orientation);

            CMatrix3        Extract3x3Matrix() const;
            void            Extract3x3Matrix(CMatrix3 &_mat3) const;
            void            ExtractQuaternion(CQuaternion &_quat) const;

            void            Decomposition(CVector3 &_position, CVector3 &_scale, CQuaternion &_orientation) const;
            void            ExtractScale(CVector3 &_scale) const;

            CMatrix4        Adjoint() const;
            float           GetDeterminant() const;
            CMatrix4 &      Invert();
            CMatrix4        GetInverse() const;

            void            Print() const;

        protected:
            float           MINOR(size_t r0, size_t r1, size_t r2, size_t c0, size_t c1, size_t c2) const;

        protected:
            static CMatrix4 &InvertAux(const CMatrix4 &_in, CMatrix4 &_out);
            static CMatrix4 &InvertAffineAux(const CMatrix4 &_in, CMatrix4 &_out);

        public:
            static CMatrix4 BuildTranslationMatrix(const CVector3 &_vec3);
            static CMatrix4 BuildTranslationMatrix(float _tx, float _ty, float _tz);

            static CMatrix4 BuildRotationMatrix(const CVector3 &_angles);
            static CMatrix4 BuildRotationMatrix(float _angleX, float _angleY, float _angleZ);
            static CMatrix4 BuildRotationMatrix(float _angle, const CVector3 &_axis);
            static CMatrix4 BuildRotationMatrix(float _angle, float _axisX, float _axisY, float _axisZ);
            static CMatrix4 BuildRotationMatrix(const CMatrix3 &_mat3);
            static CMatrix4 BuildRotationMatrix(const CQuaternion &_quat);

            static CMatrix4 BuildScaleMatrix(const CVector3 &_vec3);
            static CMatrix4 BuildScaleMatrix(float _sx, float _sy, float _sz);

            static CMatrix4 Ortho(float _left, float _right, float _bottom, float _top, float _near, float _far);
            static CMatrix4 Perspective(float _fovy, float _aspect, float _zNear, float _zFar);
            static CMatrix4 PerspectiveReverseZ(float _fovy, float _aspect, float _zNear);       // Don't use with OpenGL 4.5-!
            static CMatrix4 Frustum(float _left, float _right, float _bottom, float _top, float _near, float _far);
            static CMatrix4 LookAt(float    _posx, float    _posy, float    _posz,
                                   float _targetx, float _targety, float _targetz,
                                   float     _upx, float     _upy, float     _upz);
            static CMatrix4 LookAt(const CVector3 &_pos, const CVector3 &_target, const CVector3 &_up);

            // For cameras!
            static CMatrix4 InverseLookAt(float    _posx, float    _posy, float    _posz,
                                          float _targetx, float _targety, float _targetz,
                                          float     _upx, float     _upy, float     _upz);
            static CMatrix4 InverseLookAt(const CVector3 &_pos, const CVector3 &_target, const CVector3 &_up);

            static CMatrix4 Viewport(float _left, float _right, float _top, float _bottom, float _near, float _far);
            static CMatrix4 Viewport(float _left, float _right, float _top, float _bottom);

        public:
            static const CMatrix4 kZERO;
            static const CMatrix4 kIDENTITY;

        protected:
            // Indexed by [col][row]
            union {
                struct {
                    float col1[4];
                    float col2[4];
                    float col3[4];
                    float col4[4];
                };
                float   m[4][4];
                float   v[16];
            };
    };

} // end of namespace
#undef CMatrix4

//-------------------------------------
#include "CVector2.h"
#include "CVector3.h"
#include "CVector4.h"
#include "CMatrix3.h"
#include "CQuaternion.h"
//-------------------------------------
#include <Common/Math/math_funcs.h>
//-------------------------------------

//-------------------------------------
namespace MindShake {

    //---------------------------------
    inline
    CMatrix4::CMatrix4(float _m00, float _m01, float _m02, float _m03,
             float _m10, float _m11, float _m12, float _m13,
             float _m20, float _m21, float _m22, float _m23,
             float _m30, float _m31, float _m32, float _m33) {
        Set(_m00, _m01, _m02, _m03,
            _m10, _m11, _m12, _m13,
            _m20, _m21, _m22, _m23,
            _m30, _m31, _m32, _m33);
    }

    //---------------------------------
    template <typename T>
    inline
    CMatrix4::CMatrix4(const T *_ptr) {
        assert(_ptr != nullptr);
        for(size_t i=0; i<4*4; ++i) {
            v[i] = float(_ptr[i]);
        }
    }

    //---------------------------------
    inline
    CMatrix4::CMatrix4(const CMatrix3 &_mat3) {
        Set(_mat3);
    }

    //---------------------------------
    inline
    CMatrix4::CMatrix4(const CQuaternion &_quat) {
        Set(_quat);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::operator = (const CMatrix3 &_mat3) {
        return Set(_mat3);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::operator = (const CQuaternion &_quat) {
        return Set(_quat);
    }

    //---------------------------------
    // Set
    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Set(float _m00, float _m01, float _m02, float _m03,
                  float _m10, float _m11, float _m12, float _m13,
                  float _m20, float _m21, float _m22, float _m23,
                  float _m30, float _m31, float _m32, float _m33) {
        m[0][0] = _m00;
        m[0][1] = _m01;
        m[0][2] = _m02;
        m[0][3] = _m03;

        m[1][0] = _m10;
        m[1][1] = _m11;
        m[1][2] = _m12;
        m[1][3] = _m13;

        m[2][0] = _m20;
        m[2][1] = _m21;
        m[2][2] = _m22;
        m[2][3] = _m23;

        m[3][0] = _m30;
        m[3][1] = _m31;
        m[3][2] = _m32;
        m[3][3] = _m33;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Set(const CMatrix4 &_other) {
        for(size_t i=0; i<4*4; ++i) {
            v[i] = _other.v[i];
        }

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Set(const CMatrix3 &_mat3) {
        m[0][0] = _mat3.m[0][0];
        m[1][0] = _mat3.m[0][1];
        m[2][0] = _mat3.m[0][2];
        m[3][0] = 0.0f;

        m[0][1] = _mat3.m[1][0];
        m[1][1] = _mat3.m[1][1];
        m[2][1] = _mat3.m[1][2];
        m[3][1] = 0.0f;

        m[0][2] = _mat3.m[2][0];
        m[1][2] = _mat3.m[2][1];
        m[2][2] = _mat3.m[2][2];
        m[3][2] = 0.0f;

        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        m[3][3] = 1.0f;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Set(const CQuaternion &_quat) {
        CMatrix3 mat3;

        _quat.ToRotationMatrix(mat3);
        return Set(mat3);
    }

    //---------------------------------
    // Row
    //---------------------------------
    inline void
    CMatrix4::SetRow(int _index, const float _row[4]) {
        assert(_index < 4);
        m[0][_index] = _row[0];
        m[1][_index] = _row[1];
        m[2][_index] = _row[2];
        m[3][_index] = _row[3];
    }

    //---------------------------------
    inline void
    CMatrix4::SetRow(int _index, const CVector4 &_vec4) {
        assert(_index < 4);
        m[0][_index] = _vec4.x;
        m[1][_index] = _vec4.y;
        m[2][_index] = _vec4.z;
        m[3][_index] = _vec4.w;
    }

    //---------------------------------
    inline void
    CMatrix4::SetRow(int _index, const CVector3 &_vec3) {
        assert(_index < 4);
        m[0][_index] = _vec3.x;
        m[1][_index] = _vec3.y;
        m[2][_index] = _vec3.z;
    }

    //---------------------------------
    inline CVector4
    CMatrix4::GetRow(int _index) const {
        assert(_index < 4);
        return CVector4(m[0][_index], m[1][_index], m[2][_index], m[3][_index]);
    }

    //---------------------------------
    // Column
    //---------------------------------
    inline void
    CMatrix4::SetColumn(int _index, const float _col[4]) {
        assert(_index < 4);
        m[_index][0] = _col[0];
        m[_index][1] = _col[1];
        m[_index][2] = _col[2];
        m[_index][3] = _col[3];
    }

    //---------------------------------
    inline void
    CMatrix4::SetColumn(int _index, const CVector4 &_vec4) {
        assert(_index < 4);
        m[_index][0] = _vec4.x;
        m[_index][1] = _vec4.y;
        m[_index][2] = _vec4.z;
        m[_index][3] = _vec4.w;
    }

    //---------------------------------
    inline void
    CMatrix4::SetColumn(int _index, const CVector3 &_vec3) {
        assert(_index < 4);
        m[_index][0] = _vec3.x;
        m[_index][1] = _vec3.y;
        m[_index][2] = _vec3.z;
    }

    //---------------------------------
    inline CVector4
    CMatrix4::GetColumn(int _index) const {
        assert(_index < 4);
        return CVector4(m[_index][0], m[_index][1], m[_index][2], m[_index][3]);
    }

    //---------------------------------
    inline  float *
    CMatrix4::operator [] (size_t _row) {
        assert(_row < 4);
        return m[_row];
    }

    //---------------------------------
    inline const float *
    CMatrix4::operator [] (size_t _row) const {
        assert(_row < 4);
        return m[_row];
    }

    //---------------------------------
    // GetPtr
    //---------------------------------
    inline float *
    CMatrix4::GetPtr() {
        return &m[0][0];
    }

    //---------------------------------
    inline const float *
    CMatrix4::GetPtr() const {
        return &m[0][0];
    }

    //---------------------------------
    // Swap
    //---------------------------------
    inline void
    CMatrix4::Swap(CMatrix4 &_other) {
        float tmp;

        for(size_t i = 0; i < 4*4; ++i) {
            tmp          = v[i];
            v[i]         = _other.v[i];
            _other.v[i] = tmp;
        }
    }

    //---------------------------------
    // Comparators
    //---------------------------------
    inline bool
    CMatrix4::operator == (const CMatrix4 &_other) const {
        for(size_t i = 0; i < 4*4; ++i) {
            if(v[i] != _other.v[i])
                return false;
        }

        return true;
    }

    //---------------------------------
    inline bool
    CMatrix4::operator != (const CMatrix4 &_other) const {
        for(size_t i = 0; i < 4*4; ++i) {
            if(v[i] != _other.v[i])
                return true;
        }

        return false;
    }

    //---------------------------------
    inline bool
    CMatrix4::IsEqual(const CMatrix4 &_other, float _tolerance) const {
        for(size_t i = 0; i < 4*4; ++i) {
            if(MindShake::IsNotEqual(v[i], _other.v[i], _tolerance))
                return false;
        }

        return true;
    }

    //---------------------------------
    inline bool
    CMatrix4::IsNotEqual(const CMatrix4 &_other, float _tolerance) const {
        for(size_t i = 0; i < 4*4; ++i) {
            if(MindShake::IsNotEqual(v[i], _other.v[i], _tolerance))
                return true;
        }

        return false;
    }

    //---------------------------------
    // Add, Sub
    //---------------------------------
    inline CMatrix4
    CMatrix4::operator + (const CMatrix4 &_other) const {
        CMatrix4 r;

        for(size_t i = 0; i < 4*4; ++i)
            r.v[i] = v[i] + _other.v[i];

        return r;
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::operator - (const CMatrix4 &_other) const {
        CMatrix4 r;

        for(size_t i = 0; i < 4*4; ++i)
            r.v[i] = v[i] - _other.v[i];

        return r;
    }

    //---------------------------------
    // Multily / Concatenate
    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Concatenate(const CMatrix4 &_other) {
        *this = GetConcatenated(_other);
        return *this;
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::GetConcatenated(const CMatrix4 &_other) const {
        CMatrix4 r;

        r.m[0][0] = m[0][0] * _other.m[0][0] + m[1][0] * _other.m[0][1] + m[2][0] * _other.m[0][2] + m[3][0] * _other.m[0][3];
        r.m[1][0] = m[0][0] * _other.m[1][0] + m[1][0] * _other.m[1][1] + m[2][0] * _other.m[1][2] + m[3][0] * _other.m[1][3];
        r.m[2][0] = m[0][0] * _other.m[2][0] + m[1][0] * _other.m[2][1] + m[2][0] * _other.m[2][2] + m[3][0] * _other.m[2][3];
        r.m[3][0] = m[0][0] * _other.m[3][0] + m[1][0] * _other.m[3][1] + m[2][0] * _other.m[3][2] + m[3][0] * _other.m[3][3];

        r.m[0][1] = m[0][1] * _other.m[0][0] + m[1][1] * _other.m[0][1] + m[2][1] * _other.m[0][2] + m[3][1] * _other.m[0][3];
        r.m[1][1] = m[0][1] * _other.m[1][0] + m[1][1] * _other.m[1][1] + m[2][1] * _other.m[1][2] + m[3][1] * _other.m[1][3];
        r.m[2][1] = m[0][1] * _other.m[2][0] + m[1][1] * _other.m[2][1] + m[2][1] * _other.m[2][2] + m[3][1] * _other.m[2][3];
        r.m[3][1] = m[0][1] * _other.m[3][0] + m[1][1] * _other.m[3][1] + m[2][1] * _other.m[3][2] + m[3][1] * _other.m[3][3];

        r.m[0][2] = m[0][2] * _other.m[0][0] + m[1][2] * _other.m[0][1] + m[2][2] * _other.m[0][2] + m[3][2] * _other.m[0][3];
        r.m[1][2] = m[0][2] * _other.m[1][0] + m[1][2] * _other.m[1][1] + m[2][2] * _other.m[1][2] + m[3][2] * _other.m[1][3];
        r.m[2][2] = m[0][2] * _other.m[2][0] + m[1][2] * _other.m[2][1] + m[2][2] * _other.m[2][2] + m[3][2] * _other.m[2][3];
        r.m[3][2] = m[0][2] * _other.m[3][0] + m[1][2] * _other.m[3][1] + m[2][2] * _other.m[3][2] + m[3][2] * _other.m[3][3];

        r.m[0][3] = m[0][3] * _other.m[0][0] + m[1][3] * _other.m[0][1] + m[2][3] * _other.m[0][2] + m[3][3] * _other.m[0][3];
        r.m[1][3] = m[0][3] * _other.m[1][0] + m[1][3] * _other.m[1][1] + m[2][3] * _other.m[1][2] + m[3][3] * _other.m[1][3];
        r.m[2][3] = m[0][3] * _other.m[2][0] + m[1][3] * _other.m[2][1] + m[2][3] * _other.m[2][2] + m[3][3] * _other.m[2][3];
        r.m[3][3] = m[0][3] * _other.m[3][0] + m[1][3] * _other.m[3][1] + m[2][3] * _other.m[3][2] + m[3][3] * _other.m[3][3];

        return r;
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::operator * (const CMatrix4 &_other) const {
        return GetConcatenated(_other);
    }

    //---------------------------------
    inline CVector2
    CMatrix4::operator * (const CVector2 &_vec2) const {
        CVector2    r;
        float       invW;

        invW = 1.0f / (m[0][3] * _vec2.x + m[1][3] * _vec2.y + m[3][3]);

        r.x = (m[0][0] * _vec2.x + m[1][0] * _vec2.y + m[3][0]) * invW;
        r.y = (m[0][1] * _vec2.x + m[1][1] * _vec2.y + m[3][1]) * invW;

        return r;
    }

    //---------------------------------
    inline CVector3
    CMatrix4::operator * (const CVector3 &_vec3) const {
        CVector3    r;
        float       invW;

        invW = 1.0f / (m[0][3] * _vec3.x + m[1][3] * _vec3.y + m[2][3] * _vec3.z + m[3][3]);

        r.x = (m[0][0] * _vec3.x + m[1][0] * _vec3.y + m[2][0] * _vec3.z + m[3][0]) * invW;
        r.y = (m[0][1] * _vec3.x + m[1][1] * _vec3.y + m[2][1] * _vec3.z + m[3][1]) * invW;
        r.z = (m[0][2] * _vec3.x + m[1][2] * _vec3.y + m[2][2] * _vec3.z + m[3][2]) * invW;

        return r;
    }

    //---------------------------------
    inline CVector4
    CMatrix4::operator * (const CVector4 &_vec4) const {
        return CVector4(
            m[0][0] * _vec4.x + m[1][0] * _vec4.y + m[2][0] * _vec4.z + m[3][0] * _vec4.w,
            m[0][1] * _vec4.x + m[1][1] * _vec4.y + m[2][1] * _vec4.z + m[3][1] * _vec4.w,
            m[0][2] * _vec4.x + m[1][2] * _vec4.y + m[2][2] * _vec4.z + m[3][2] * _vec4.w,
            m[0][3] * _vec4.x + m[1][3] * _vec4.y + m[2][3] * _vec4.z + m[3][3] * _vec4.w
        );
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::operator * (float _value) const {
        return CMatrix4(
            _value * m[0][0], _value * m[0][1], _value * m[0][2], _value * m[0][3],
            _value * m[1][0], _value * m[1][1], _value * m[1][2], _value * m[1][3],
            _value * m[2][0], _value * m[2][1], _value * m[2][2], _value * m[2][3],
            _value * m[3][0], _value * m[3][1], _value * m[3][2], _value * m[3][3]
        );
    }

    //---------------------------------
    // Affine
    //---------------------------------
    inline bool
    CMatrix4::IsAffine() const {
        return MindShake::IsZero(m[0][3]) &&
               MindShake::IsZero(m[1][3]) &&
               MindShake::IsZero(m[2][3]) &&
               MindShake::IsEqual(m[3][3], 1.0f);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::InvertAffineAux(const CMatrix4 &_in, CMatrix4 &_out) {
        CMatrix3    mat3(_in.v[0], _in.v[1], _in.v[2],
                         _in.v[4], _in.v[5], _in.v[6],
                         _in.v[8], _in.v[9], _in.v[10]);
        float x = _in.v[12];
        float y = _in.v[13];
        float z = _in.v[14];

        mat3.Invert();

        const float *r = mat3.GetPtr();
        _out.v[0]  = r[0];
        _out.v[1]  = r[1];
        _out.v[2]  = r[2];
        _out.v[3]  = 0.0f;

        _out.v[4]  = r[3];
        _out.v[5]  = r[4];
        _out.v[6]  = r[5];
        _out.v[7]  = 0.0f;

        _out.v[8]  = r[6];
        _out.v[9]  = r[7];
        _out.v[10] = r[8];
        _out.v[11] = 0.0f;

        _out.v[12] = -(r[0] * x + r[3] * y + r[6] * z);
        _out.v[13] = -(r[1] * x + r[4] * y + r[7] * z);
        _out.v[14] = -(r[2] * x + r[5] * y + r[8] * z);
        _out.v[15] = 1.0f;

        return _out;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::InvertAffine() {
        return InvertAffineAux(*this, *this);
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::GetInverseAffine() const {
        CMatrix4 r;

        return InvertAffineAux(*this, r);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::ConcatenateAffine(const CMatrix4 &_other) {
        float   m00, m01, m02, m03;
        float   m10, m11, m12, m13;
        float   m20, m21, m22, m23;

        assert(IsAffine() && _other.IsAffine());

        m00 = m[0][0] * _other.m[0][0] + m[1][0] * _other.m[0][1] + m[2][0] * _other.m[0][2];
        m01 = m[0][0] * _other.m[1][0] + m[1][0] * _other.m[1][1] + m[2][0] * _other.m[1][2];
        m02 = m[0][0] * _other.m[2][0] + m[1][0] * _other.m[2][1] + m[2][0] * _other.m[2][2];
        m03 = m[0][0] * _other.m[3][0] + m[1][0] * _other.m[3][1] + m[2][0] * _other.m[3][2] + m[3][0];

        m10 = m[0][1] * _other.m[0][0] + m[1][1] * _other.m[0][1] + m[2][1] * _other.m[0][2];
        m11 = m[0][1] * _other.m[1][0] + m[1][1] * _other.m[1][1] + m[2][1] * _other.m[1][2];
        m12 = m[0][1] * _other.m[2][0] + m[1][1] * _other.m[2][1] + m[2][1] * _other.m[2][2];
        m13 = m[0][1] * _other.m[3][0] + m[1][1] * _other.m[3][1] + m[2][1] * _other.m[3][2] + m[3][1];

        m20 = m[0][2] * _other.m[0][0] + m[1][2] * _other.m[0][1] + m[2][2] * _other.m[0][2];
        m21 = m[0][2] * _other.m[1][0] + m[1][2] * _other.m[1][1] + m[2][2] * _other.m[1][2];
        m22 = m[0][2] * _other.m[2][0] + m[1][2] * _other.m[2][1] + m[2][2] * _other.m[2][2];
        m23 = m[0][2] * _other.m[3][0] + m[1][2] * _other.m[3][1] + m[2][2] * _other.m[3][2] + m[3][2];

        m[0][0] = m00;
        m[1][0] = m01;
        m[2][0] = m02;
        m[3][0] = m03;

        m[0][1] = m10;
        m[1][1] = m11;
        m[2][1] = m12;
        m[3][1] = m13;

        m[0][2] = m20;
        m[1][2] = m21;
        m[2][2] = m22;
        m[3][2] = m23;

        return *this;
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::GetConcatenatedAffine(const CMatrix4 &_other) const {
        float   m00, m01, m02, m03;
        float   m10, m11, m12, m13;
        float   m20, m21, m22, m23;

        assert(IsAffine() && _other.IsAffine());

        m00 = m[0][0] * _other.m[0][0] + m[1][0] * _other.m[0][1] + m[2][0] * _other.m[0][2];
        m01 = m[0][0] * _other.m[1][0] + m[1][0] * _other.m[1][1] + m[2][0] * _other.m[1][2];
        m02 = m[0][0] * _other.m[2][0] + m[1][0] * _other.m[2][1] + m[2][0] * _other.m[2][2];
        m03 = m[0][0] * _other.m[3][0] + m[1][0] * _other.m[3][1] + m[2][0] * _other.m[3][2] + m[3][0];

        m10 = m[0][1] * _other.m[0][0] + m[1][1] * _other.m[0][1] + m[2][1] * _other.m[0][2];
        m11 = m[0][1] * _other.m[1][0] + m[1][1] * _other.m[1][1] + m[2][1] * _other.m[1][2];
        m12 = m[0][1] * _other.m[2][0] + m[1][1] * _other.m[2][1] + m[2][1] * _other.m[2][2];
        m13 = m[0][1] * _other.m[3][0] + m[1][1] * _other.m[3][1] + m[2][1] * _other.m[3][2] + m[3][1];

        m20 = m[0][2] * _other.m[0][0] + m[1][2] * _other.m[0][1] + m[2][2] * _other.m[0][2];
        m21 = m[0][2] * _other.m[1][0] + m[1][2] * _other.m[1][1] + m[2][2] * _other.m[1][2];
        m22 = m[0][2] * _other.m[2][0] + m[1][2] * _other.m[2][1] + m[2][2] * _other.m[2][2];
        m23 = m[0][2] * _other.m[3][0] + m[1][2] * _other.m[3][1] + m[2][2] * _other.m[3][2] + m[3][2];

        return CMatrix4(
            m00, m10, m20, 0,
            m01, m11, m21, 0,
            m02, m12, m22, 0,
            m03, m13, m23, 1
        );
    }

    //---------------------------------
    inline CVector2
    CMatrix4::TransformAffine(const CVector2 &_vec2) const {
        assert(IsAffine());

        return CVector2(
                m[0][0] * _vec2.x + m[1][0] * _vec2.y + m[3][0],
                m[0][1] * _vec2.x + m[1][1] * _vec2.y + m[3][1]
        );
    }

    //---------------------------------
    inline CVector3
    CMatrix4::TransformAffine(const CVector3 &_vec3) const {
        assert(IsAffine());

        return CVector3(
                m[0][0] * _vec3.x + m[1][0] * _vec3.y + m[2][0] * _vec3.z + m[3][0],
                m[0][1] * _vec3.x + m[1][1] * _vec3.y + m[2][1] * _vec3.z + m[3][1],
                m[0][2] * _vec3.x + m[1][2] * _vec3.y + m[2][2] * _vec3.z + m[3][2]
        );
    }

    //---------------------------------
    inline CVector4
    CMatrix4::TransformAffine(const CVector4 &_vec4) const {
        assert(IsAffine());

        return CVector4(
            m[0][0] * _vec4.x + m[1][0] * _vec4.y + m[2][0] * _vec4.z + m[3][0] * _vec4.w,
            m[0][1] * _vec4.x + m[1][1] * _vec4.y + m[2][1] * _vec4.z + m[3][1] * _vec4.w,
            m[0][2] * _vec4.x + m[1][2] * _vec4.y + m[2][2] * _vec4.z + m[3][2] * _vec4.w,
            _vec4.w
        );
    }

    //---------------------------------
    // Transpose
    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Transpose() {
        float   tmp1, tmp2, tmp3;

        tmp1 = m[0][1];
        tmp2 = m[0][2];
        tmp3 = m[0][3];

        m[0][1] = m[1][0];
        m[0][2] = m[2][0];
        m[0][3] = m[3][0];

        m[1][0] = tmp1;
        m[2][0] = tmp2;
        m[3][0] = tmp3;

        tmp1 = m[1][2];
        tmp2 = m[1][3];
        tmp3 = m[2][3];

        m[1][2] = m[2][1];
        m[1][3] = m[3][1];
        m[2][3] = m[3][2];

        m[2][1] = tmp1;
        m[3][1] = tmp2;
        m[3][2] = tmp3;

        return *this;
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::GetTransposed() const {
        return CMatrix4(m[0][0], m[1][0], m[2][0], m[3][0],
                        m[0][1], m[1][1], m[2][1], m[3][1],
                        m[0][2], m[1][2], m[2][2], m[3][2],
                        m[0][3], m[1][3], m[2][3], m[3][3]
        );
    }

    //---------------------------------
    // Translation
    //---------------------------------
    inline CMatrix4 &
    CMatrix4::SetTranslation(const CVector3 &_vec3) {
        return SetTranslation(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::SetTranslation(float _tx, float _ty, float _tz) {
        m[3][0] = _tx;
        m[3][1] = _ty;
        m[3][2] = _tz;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Translate(const CVector3 &_vec3) {
        return Translate(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Translate(float _tx, float _ty, float _tz) {
        m[3][0] += m[0][0] * _tx + m[1][0] * _ty + m[2][0] * _tz;
        m[3][1] += m[0][1] * _tx + m[1][1] * _ty + m[2][1] * _tz;
        m[3][2] += m[0][2] * _tx + m[1][2] * _ty + m[2][2] * _tz;
        m[3][3] += m[0][3] * _tx + m[1][3] * _ty + m[2][3] * _tz;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::TranslateAffine(const CVector3 &_vec3) {
        return TranslateAffine(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::TranslateAffine(float _tx, float _ty, float _tz) {
        m[3][0] += m[0][0] * _tx + m[1][0] * _ty + m[2][0] * _tz;
        m[3][1] += m[0][1] * _tx + m[1][1] * _ty + m[2][1] * _tz;
        m[3][2] += m[0][2] * _tx + m[1][2] * _ty + m[2][2] * _tz;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::PreTranslate(const CVector3 &_vec3) {
        return PreTranslate(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::PreTranslate(float _tx, float _ty, float _tz) {
        m[0][0] += m[0][3] * _tx;
        m[0][1] += m[0][3] * _ty;
        m[0][2] += m[0][3] * _tz;

        m[1][0] += m[1][3] * _tx;
        m[1][1] += m[1][3] * _ty;
        m[1][2] += m[1][3] * _tz;

        m[2][0] += m[2][3] * _tx;
        m[2][1] += m[2][3] * _ty;
        m[2][2] += m[2][3] * _tz;

        m[3][0] += m[3][3] * _tx;
        m[3][1] += m[3][3] * _ty;
        m[3][2] += m[3][3] * _tz;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::PreTranslateAffine(const CVector3 &_vec3) {
        return PreTranslateAffine(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::PreTranslateAffine(float _tx, float _ty, float _tz) {
        m[3][0] += _tx;
        m[3][1] += _ty;
        m[3][2] += _tz;

        return *this;
    }

    //---------------------------------
    inline CVector3
    CMatrix4::GetTranslation() const {
        return CVector3(m[3][0], m[3][1], m[3][2]);
    }

    //---------------------------------
    inline float
    CMatrix4::GetTranslationX() const {
        return m[3][0];
    }

    //---------------------------------
    inline float
    CMatrix4::GetTranslationY() const {
        return m[3][1];
    }

    //---------------------------------
    inline float
    CMatrix4::GetTranslationZ() const {
        return m[3][2];
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeTranslation(const CVector3 &_vec3) {
        return MakeTranslation(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeTranslation(float _tx, float _ty, float _tz) {
        m[0][0] = 1.0f;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = 0.0f;

        m[1][0] = 0.0f;
        m[1][1] = 1.0f;
        m[1][2] = 0.0f;
        m[1][3] = 0.0f;

        m[2][0] = 0.0f;
        m[2][1] = 0.0f;
        m[2][2] = 1.0f;
        m[2][3] = 0.0f;

        m[3][0] = _tx;
        m[3][1] = _ty;
        m[3][2] = _tz;
        m[3][3] = 1.0f;

        return *this;
    }

    //---------------------------------
    // Rotation
    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Rotate(const CVector3 &_angles) {
        return Rotate(_angles.x, _angles.y, _angles.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Rotate(float _angleX, float _angleY, float _angleZ) {
        *this = *this * BuildRotationMatrix(_angleX, _angleY, _angleZ);
        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Rotate(float _angle, const CVector3 &_axis) {
        *this = *this * BuildRotationMatrix(_angle, _axis);
        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Rotate(float _angle, float _axisX, float _axisY, float _axisZ) {
        *this = *this * BuildRotationMatrix(_angle, _axisX, _axisY, _axisZ);
        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Rotate(const CMatrix3 &_mat3) {
        *this = *this * BuildRotationMatrix(_mat3);
        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Rotate(const CQuaternion &_quat) {
        *this = *this * BuildRotationMatrix(_quat);
        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeRotation(const CVector3 &_angles) {
        return MakeRotation(_angles.x, _angles.y, _angles.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeRotation(float _angleX, float _angleY, float _angleZ) {
        float   sinX, cosX;
        float   sinY, cosY;
        float   sinZ, cosZ;

        sinX = MindShake::SinG(_angleX);
        cosX = MindShake::CosG(_angleX);

        sinY = MindShake::SinG(_angleY);
        cosY = MindShake::CosG(_angleY);

        sinZ = MindShake::SinG(_angleZ);
        cosZ = MindShake::CosG(_angleZ);

        m[0][0] =  cosY * cosZ;
        m[1][0] = -cosY * sinZ;
        m[2][0] = sinY;
        m[3][0] = 0;

        m[0][1] = (cosX * sinZ + sinX * sinY * cosZ);
        m[1][1] = (cosX * cosZ - sinX * sinY * sinZ);
        m[2][1] = -sinX * cosY;
        m[3][1] = 0;

        m[0][2] = (sinX * sinZ - cosX * sinY * cosZ);
        m[1][2] = (sinX * cosZ + cosX * sinY * sinZ);
        m[2][2] =  cosX * cosY;
        m[3][2] = 0;

        m[0][3] = 0;
        m[1][3] = 0;
        m[2][3] = 0;
        m[3][3] = 1;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeRotation(const CMatrix3 &_mat3) {
        return Set(_mat3);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeRotation(const CQuaternion &_quat) {
        return Set(_quat);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeRotation(float _angle, const CVector3 &_axis) {
        return MakeRotation(_angle, _axis.x, _axis.y, _axis.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeRotation(float _angle, float _axisX, float _axisY, float _axisZ) {
        float c = MindShake::Cos(_angle * Float32::DEGTORAD);
        float s = MindShake::Sin(_angle * Float32::DEGTORAD);
        float c1 = 1.0f - c;

        m[0][0] = _axisX * _axisX * c1 + c;
        m[0][1] = _axisX * _axisY * c1 + _axisZ * s;
        m[0][2] = _axisX * _axisZ * c1 - _axisY * s;
        m[0][3] = 0;

        m[1][0] = _axisY * _axisX * c1 - _axisZ * s;
        m[1][1] = _axisY * _axisY * c1 + c;
        m[1][2] = _axisY * _axisZ * c1 + _axisX * s;
        m[1][3] = 0;

        m[2][0] = _axisZ * _axisX * c1 + _axisY * s;
        m[2][1] = _axisZ * _axisY * c1 - _axisX * s;
        m[2][2] = _axisZ * _axisZ * c1 + c;
        m[2][3] = 0;

        m[3][0] = 0;
        m[3][1] = 0;
        m[3][2] = 0;
        m[3][3] = 1;

        return *this;
    }

    //---------------------------------
    inline CVector3
    CMatrix4::GetAngles() const {
        float   pitch, yaw, roll;

        // Find yaw (around y-axis)
        // NOTE: asin() returns -90~+90, so correct the angle range -180~+180
        // Using z value of forward vector
        yaw = MindShake::ASin(m[2][0]) * Float32::RADTODEG;
        if (m[2][2] < 0) {
            if (yaw >= 0) yaw =  180.0f - yaw;
            else          yaw = -180.0f - yaw;
        }

        // Find roll (around z-axis) and pitch (around x-axis)
        // If forward vector is (1, 0, 0) or (-1, 0, 0), then m[0] = m[4] = m[9] = m[10] = 0
        if (m[0][0] > -Float32::EPSILON && m[0][0] < Float32::EPSILON)
        {
            roll  = 0;  // assume roll = 0
            pitch = MindShake::ATan2(m[0][1], m[1][1]) * Float32::RADTODEG;
        }
        else
        {
            roll  = MindShake::ATan2(-m[1][0], m[0][0]) * Float32::RADTODEG;
            pitch = MindShake::ATan2(-m[2][1], m[2][2]) * Float32::RADTODEG;
        }

        return CVector3(pitch, yaw, roll);
    }

    //---------------------------------
    // Scale
    //---------------------------------
    inline CMatrix4 &
    CMatrix4::SetScale(const CVector3 &_vec3) {
        return SetScale(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::SetScale(float _sx, float _sy, float _sz) {
        m[0][0] = _sx;
        m[1][1] = _sy;
        m[2][2] = _sz;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Scale(const CVector3 &_vec3) {
        return Scale(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Scale(float _sx, float _sy, float _sz) {
        m[0][0] *= _sx;   
        m[0][1] *= _sx;   
        m[0][2] *= _sx;   
        m[0][3] *= _sx;   

        m[1][0] *= _sy;   
        m[1][1] *= _sy;   
        m[1][2] *= _sy;   
        m[1][3] *= _sy;   

        m[2][0] *= _sz;  
        m[2][1] *= _sz;  
        m[2][2] *= _sz;  
        m[2][3] *= _sz;  

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::ScaleAffine(const CVector3 &_vec3) {
        return ScaleAffine(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::ScaleAffine(float _sx, float _sy, float _sz) {
        m[0][0] *= _sx;   
        m[0][1] *= _sx;   
        m[0][2] *= _sx;   

        m[1][0] *= _sy;   
        m[1][1] *= _sy;   
        m[1][2] *= _sy;   

        m[2][0] *= _sz;  
        m[2][1] *= _sz;  
        m[2][2] *= _sz;  

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::PreScale(const CVector3 &_vec3) {
        return PreScale(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::PreScale(float _sx, float _sy, float _sz) {
        m[0][0] *= _sx;   
        m[0][1] *= _sy;   
        m[0][2] *= _sz;   

        m[1][0] *= _sx;   
        m[1][1] *= _sy;   
        m[1][2] *= _sz;   

        m[2][0] *= _sx;  
        m[2][1] *= _sy;  
        m[2][2] *= _sz;  

        m[3][0] *= _sx;
        m[3][1] *= _sy;
        m[3][2] *= _sz;

        return *this;
    }

    // It is the same
    //---------------------------------
    inline CMatrix4 &
    CMatrix4::PreScaleAffine(const CVector3 &_vec3) {
        return PreScale(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::PreScaleAffine(float _sx, float _sy, float _sz) {
        return PreScale(_sx, _sy, _sz);
    }

    //---------------------------------
    inline bool
    CMatrix4::HasScale() const {
        float t;

        // check magnitude of row vectors (local axes)
        t = m[0][0] * m[0][0] + m[0][1] * m[0][1] + m[0][2] * m[0][2];
        if(MindShake::IsNotEqual(t, 1.0f, Float32::EPSILON))
            return true;

        t = m[1][0] * m[1][0] + m[1][1] * m[1][1] + m[1][2] * m[1][2];
        if(MindShake::IsNotEqual(t, 1.0f, Float32::EPSILON))
            return true;

        t = m[2][0] * m[2][0] + m[2][1] * m[2][1] + m[2][2] * m[2][2];
        if(MindShake::IsNotEqual(t, 1.0f, Float32::EPSILON))
            return true;

        return false;
    }

    //---------------------------------
    inline bool
    CMatrix4::HasNegativeScale() const {
        return GetDeterminant() < 0;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeScale(const CVector3 &_vec3) {
        return MakeScale(_vec3.x, _vec3.y, _vec3.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeScale(float _sx, float _sy, float _sz) {
        m[0][0] = _sx;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = 0.0f;

        m[1][0] = 0.0f;
        m[1][1] = _sy;
        m[1][2] = 0.0f;
        m[1][3] = 0.0f;

        m[2][0] = 0.0f;
        m[2][1] = 0.0f;
        m[2][2] = _sz;
        m[2][3] = 0.0f;

        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[3][3] = 1.0f;

        return *this;
    }

    //---------------------------------
    // Other transformations
    //---------------------------------

    // Ordering:
    //  1. Scale
    //  2. Rotate
    //  3. Translate
    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeTransform(const CVector3 &_position, const CVector3 &_scale, const CQuaternion &_orientation) {
        CMatrix3    rot3x3, scale3x3;

        _orientation.ToRotationMatrix(rot3x3);

        scale3x3[0][0] = _scale.x;
        scale3x3[0][1] = 0.0f;
        scale3x3[0][2] = 0.0f;

        scale3x3[1][0] = 0.0f;
        scale3x3[1][1] = _scale.y;
        scale3x3[1][2] = 0.0f;

        scale3x3[2][0] = 0.0f;
        scale3x3[2][1] = 0.0f;
        scale3x3[2][2] = _scale.z;

        *this = rot3x3 * scale3x3;
        this->SetTranslation(_position);

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeTransform(const CVector3 &_position, const CVector3 &_scale, const CVector3 &_angles) {
        return MakeTransform(_position.x, _position.y, _position.z, _scale.x, _scale.y, _scale.z, _angles.x, _angles.y, _angles.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeTransform(float _posX,   float _posY,   float _posZ,
                            float _scaleX, float _scaleY, float _scaleZ,
                            float _angleX, float _angleY, float _angleZ) {
        float   sinX, cosX;
        float   sinY, cosY;
        float   sinZ, cosZ;

        sinX = MindShake::SinG(_angleX);
        cosX = MindShake::CosG(_angleX);

        sinY = MindShake::SinG(_angleY);
        cosY = MindShake::CosG(_angleY);

        sinZ = MindShake::SinG(_angleZ);
        cosZ = MindShake::CosG(_angleZ);

//      m[0][0] = (cosY * cosZ) * _scaleX;
//      m[0][1] = (cosY * -sinZ) * _scaleY;
//      m[0][2] = (sinY) * _scaleZ;
//      m[0][3] = _posX;
//
//      m[1][0] = (cosX * sinZ + -sinX * -sinY * cosZ) * _scaleX;
//      m[1][1] = (cosX * cosZ + -sinX * -sinY * -sinZ) * _scaleY;
//      m[1][2] = (-sinX * cosY) * _scaleZ;
//      m[1][3] = _posY;
//
//      m[2][0] = (sinX * sinZ + cosX * -sinY * cosZ) * _scaleX;
//      m[2][1] = (sinX * cosZ + cosX * -sinY * -sinZ) * _scaleY;
//      m[2][2] = (cosX * cosY) * _scaleZ;
//      m[2][3] = _posZ;

        m[0][0] =  cosY * cosZ * _scaleX;
        m[1][0] = -cosY * sinZ * _scaleY;
        m[2][0] = sinY * _scaleZ;
        m[3][0] = _posX;

        m[0][1] = (cosX * sinZ + sinX * sinY * cosZ) * _scaleX;
        m[1][1] = (cosX * cosZ - sinX * sinY * sinZ) * _scaleY;
        m[2][1] = -sinX * cosY * _scaleZ;
        m[3][1] = _posY;

        m[0][2] = (sinX * sinZ - cosX * sinY * cosZ) * _scaleX;
        m[1][2] = (sinX * cosZ + cosX * sinY * sinZ) * _scaleY;
        m[2][2] = cosX * cosY * _scaleZ;
        m[3][2] = _posZ;

        m[0][3] = 0;
        m[1][3] = 0;
        m[2][3] = 0;
        m[3][3] = 1;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeTransform(const CVector3 &_position, const CVector3 &_scale, float _angleZ) {
        return MakeTransform(_position.x, _position.y, _position.z, _scale.x, _scale.y, _scale.z, _angleZ);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeTransform(float _posX,   float _posY,   float _posZ,
                            float _scaleX, float _scaleY, float _scaleZ,
                            float _angleZ) {
        float   sinZ, cosZ;

        sinZ = MindShake::SinG(_angleZ);
        cosZ = MindShake::CosG(_angleZ);

        m[0][0] =  cosZ * _scaleX;
        m[1][0] = -sinZ * _scaleY;
        m[2][0] = 0;
        m[3][0] = _posX;

        m[0][1] = sinZ * _scaleX;
        m[1][1] = cosZ * _scaleY;
        m[2][1] = 0;
        m[3][1] = _posY;

        m[0][2] = 0;
        m[1][2] = 0;
        m[2][2] = _scaleZ;
        m[3][2] = _posZ;

        m[0][3] = 0;
        m[1][3] = 0;
        m[2][3] = 0;
        m[3][3] = 1;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeTransform(const CVector3 &_position, const CVector3 &_scale) {
        return MakeTransform(_position.x, _position.y, _position.z, _scale.x, _scale.y, _scale.z);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeTransform(float _posX,   float _posY,   float _posZ,
                            float _scaleX, float _scaleY, float _scaleZ) {
        m[0][0] = _scaleX;
        m[1][0] = 0;
        m[2][0] = 0;
        m[3][0] = _posX;

        m[0][1] = 0;
        m[1][1] = _scaleY;
        m[2][1] = 0;
        m[3][1] = _posY;

        m[0][2] = 0;
        m[1][2] = 0;
        m[2][2] = _scaleZ;
        m[3][2] = _posZ;

        m[0][3] = 0;
        m[1][3] = 0;
        m[2][3] = 0;
        m[3][3] = 1;

        return *this;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::MakeInverseTransform(const CVector3 &_position, const CVector3 &_scale, const CQuaternion &_orientation) {
        CVector3    invTranslate;
        CVector3    invScale;
        CQuaternion invRot;
        CMatrix3    rot3x3;

        // Invert the parameters
        invTranslate = -_position;
        invScale.Set(1 / _scale.x, 1 / _scale.y, 1 / _scale.z);
        invRot = _orientation.GetInverse();

        // Because we are inverting, the order is: translation, rotation, scale
        // Make translation relative to scale and rotation
        invTranslate = invRot * invTranslate; // rotate
        invTranslate *= invScale; // scale

        // Make a 3x3 rotation matrix
        invRot.ToRotationMatrix(rot3x3);

        // Apply inverse scale
        m[0][0] = invScale.x * rot3x3[0][0];
        m[0][1] = invScale.y * rot3x3[1][0];
        m[0][2] = invScale.z * rot3x3[2][0];
        m[0][3] = 0;

        m[1][0] = invScale.x * rot3x3[0][1];
        m[1][1] = invScale.y * rot3x3[1][1];
        m[1][2] = invScale.z * rot3x3[2][1];
        m[1][3] = 0;

        m[2][0] = invScale.x * rot3x3[0][2];
        m[2][1] = invScale.y * rot3x3[1][2];
        m[2][2] = invScale.z * rot3x3[2][2];
        m[2][3] = 0;

        m[3][0] = invTranslate.x;
        m[3][1] = invTranslate.y;
        m[3][2] = invTranslate.z;
        m[3][3] = 1;

        return *this;
    }

    //---------------------------------
    // Extract
    //---------------------------------
    inline CMatrix3
    CMatrix4::Extract3x3Matrix() const {

        return CMatrix3(
            m[0][0], m[1][0], m[2][0],
            m[0][1], m[1][1], m[2][1],
            m[0][2], m[1][2], m[2][2]
        );
    }

    //---------------------------------
    inline void
    CMatrix4::Extract3x3Matrix(CMatrix3 &_mat3) const {
        _mat3.m[0][0] = m[0][0];
        _mat3.m[0][1] = m[1][0];
        _mat3.m[0][2] = m[2][0];

        _mat3.m[1][0] = m[0][1];
        _mat3.m[1][1] = m[1][1];
        _mat3.m[1][2] = m[2][1];

        _mat3.m[2][0] = m[0][2];
        _mat3.m[2][1] = m[1][2];
        _mat3.m[2][2] = m[2][2];
    }

    //---------------------------------
    inline void
    CMatrix4::ExtractQuaternion(CQuaternion &_quat) const {
        CMatrix3 m3x3;

        Extract3x3Matrix(m3x3);

        _quat = m3x3;
    }

    //---------------------------------
    inline void
    CMatrix4::Decomposition(CVector3 &_position, CVector3 &_scale, CQuaternion &_orientation) const {
        assert(IsAffine());

        CMatrix3    m3x3;
        CMatrix3    matQ;
        CVector3    vecU;

        Extract3x3Matrix(m3x3);

        m3x3.QDUDecomposition(matQ, _scale, vecU);

        _orientation = CQuaternion(matQ);
        _position    = CVector3(m[3][0], m[3][1], m[3][2]);
    }

    //---------------------------------
    inline void
    CMatrix4::ExtractScale(CVector3 &_scale) const {
        assert(IsAffine());

        CMatrix3    m3x3;

        Extract3x3Matrix(m3x3);

        m3x3.ExtractScale(_scale);
    }

    //---------------------------------
    // Adjoint
    //---------------------------------
    inline CMatrix4
    CMatrix4::Adjoint() const {
        return CMatrix4(
             MINOR(1, 2, 3, 1, 2, 3),
            -MINOR(0, 2, 3, 1, 2, 3),
             MINOR(0, 1, 3, 1, 2, 3),
            -MINOR(0, 1, 2, 1, 2, 3),

            -MINOR(1, 2, 3, 0, 2, 3),
             MINOR(0, 2, 3, 0, 2, 3),
            -MINOR(0, 1, 3, 0, 2, 3),
             MINOR(0, 1, 2, 0, 2, 3),

             MINOR(1, 2, 3, 0, 1, 3),
            -MINOR(0, 2, 3, 0, 1, 3),
             MINOR(0, 1, 3, 0, 1, 3),
            -MINOR(0, 1, 2, 0, 1, 3),

            -MINOR(1, 2, 3, 0, 1, 2),
             MINOR(0, 2, 3, 0, 1, 2),
            -MINOR(0, 1, 3, 0, 1, 2),
             MINOR(0, 1, 2, 0, 1, 2));
    }

    //---------------------------------
    inline float
    CMatrix4::GetDeterminant() const {
        return
            m[0][0] * MINOR(1, 2, 3, 1, 2, 3) -
            m[0][1] * MINOR(1, 2, 3, 0, 2, 3) +
            m[0][2] * MINOR(1, 2, 3, 0, 1, 3) -
            m[0][3] * MINOR(1, 2, 3, 0, 1, 2);
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::InvertAux(const CMatrix4 &_in, CMatrix4 &_out) {
        double  m00, m01, m02, m03;
        double  m10, m11, m12, m13;
        double  m20, m21, m22, m23;
        double  m30, m31, m32, m33;
        double  v0, v1, v2, v3, v4, v5;
        double  t00, t10, t20, t30;
        double  invDet;
        double  r00, r01, r02, r03;
        double  r10, r11, r12, r13;
        double  r20, r21, r22, r23;
        double  r30, r31, r32, r33;

        m00 = _in.m[0][0];
        m01 = _in.m[0][1];
        m02 = _in.m[0][2];
        m03 = _in.m[0][3];

        m10 = _in.m[1][0];
        m11 = _in.m[1][1];
        m12 = _in.m[1][2];
        m13 = _in.m[1][3];

        m20 = _in.m[2][0];
        m21 = _in.m[2][1];
        m22 = _in.m[2][2];
        m23 = _in.m[2][3];

        m30 = _in.m[3][0];
        m31 = _in.m[3][1];
        m32 = _in.m[3][2];
        m33 = _in.m[3][3];

        v0 = m20 * m31 - m21 * m30;
        v1 = m20 * m32 - m22 * m30;
        v2 = m20 * m33 - m23 * m30;
        v3 = m21 * m32 - m22 * m31;
        v4 = m21 * m33 - m23 * m31;
        v5 = m22 * m33 - m23 * m32;

        t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
        t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
        t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
        t30 = -(v3 * m10 - v1 * m11 + v0 * m12);

        invDet = 1.0f / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

        r00 = t00 * invDet;
        r10 = t10 * invDet;
        r20 = t20 * invDet;
        r30 = t30 * invDet;

        r01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        r11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        r21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        r31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m10 * m31 - m11 * m30;
        v1 = m10 * m32 - m12 * m30;
        v2 = m10 * m33 - m13 * m30;
        v3 = m11 * m32 - m12 * m31;
        v4 = m11 * m33 - m13 * m31;
        v5 = m12 * m33 - m13 * m32;

        r02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        r12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        r22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        r32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m21 * m10 - m20 * m11;
        v1 = m22 * m10 - m20 * m12;
        v2 = m23 * m10 - m20 * m13;
        v3 = m22 * m11 - m21 * m12;
        v4 = m23 * m11 - m21 * m13;
        v5 = m23 * m12 - m22 * m13;

        r03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        r13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        r23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        r33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        _out.m[0][0] = float(r00);
        _out.m[0][1] = float(r01);
        _out.m[0][2] = float(r02);
        _out.m[0][3] = float(r03);

        _out.m[1][0] = float(r10);
        _out.m[1][1] = float(r11);
        _out.m[1][2] = float(r12);
        _out.m[1][3] = float(r13);

        _out.m[2][0] = float(r20);
        _out.m[2][1] = float(r21);
        _out.m[2][2] = float(r22);
        _out.m[2][3] = float(r23);

        _out.m[3][0] = float(r30);
        _out.m[3][1] = float(r31);
        _out.m[3][2] = float(r32);
        _out.m[3][3] = float(r33);

        return _out;
    }

    //---------------------------------
    inline CMatrix4 &
    CMatrix4::Invert() {
        return InvertAux(*this, *this);
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::GetInverse() const {
        CMatrix4 r;

        return InvertAux(*this, r);
    }

    //---------------------------------

    //---------------------------------
    inline float
    CMatrix4::MINOR(size_t r0, size_t r1, size_t r2, size_t c0, size_t c1, size_t c2) const {
        return m[r0][c0] * (m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) -
               m[r0][c1] * (m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) +
               m[r0][c2] * (m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]);
    }

    //---------------------------------
    // Build Transform
    //---------------------------------
    inline CMatrix4
    CMatrix4::BuildTranslationMatrix(const CVector3 &_vec3) {
        CMatrix4 r;
        return r.MakeTranslation(_vec3);
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::BuildTranslationMatrix(float _tx, float _ty, float _tz) {
        CMatrix4 r;
        return r.MakeTranslation(_tx, _ty, _tz);
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::BuildRotationMatrix(const CVector3 &_angles) {
        CMatrix4 r;
        return r.MakeRotation(_angles);
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::BuildRotationMatrix(float _angleX, float _angleY, float _angleZ) {
        CMatrix4 r;
        return r.MakeRotation(_angleX, _angleY, _angleZ);
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::BuildRotationMatrix(float _angle, const CVector3 &_axis) {
        CMatrix4 r;
        return r.MakeRotation(_angle, _axis);
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::BuildRotationMatrix(float _angle, float _axisX, float _axisY, float _axisZ) {
        CMatrix4 r;
        return r.MakeRotation(_angle, _axisX, _axisY, _axisZ);
    }

    //---------------------------------
    inline CMatrix4 
    CMatrix4::BuildRotationMatrix(const CMatrix3 &_mat3) {
        return CMatrix4(_mat3);
    }

    //---------------------------------
    inline CMatrix4 
    CMatrix4::BuildRotationMatrix(const CQuaternion &_quat) {
        return CMatrix4(_quat);
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::BuildScaleMatrix(const CVector3 &_vec3) {
        CMatrix4 r;
        return r.MakeScale(_vec3);
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::BuildScaleMatrix(float _sx, float _sy, float _sz) {
        CMatrix4 r;
        return r.MakeScale(_sx, _sy, _sz);
    }

    //---------------------------------

    //---------------------------------
    inline CMatrix4
    CMatrix4::Ortho(float _left, float _right, float _bottom, float _top, float _zNear, float _zFar) {
        float width  = _right - _left;
        float height = _top - _bottom;
        float depth  = _zFar - _zNear;
        float tx     = - (_right + _left) / (_right - _left);
        float ty     = - (_top + _bottom) / (_top - _bottom);
        float tz     = - (_zFar + _zNear) / (_zFar - _zNear);

        return CMatrix4(
            2.0f / width, 0.0f,          0.0f,         0.0f,
            0.0f,         2.0f / height, 0.0f,         0.0f,
            0.0f,         0.0f,         -2.0f / depth, 0.0f,
              tx,           ty,            tz,         1.0f
            );
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::Perspective(float _fovY, float _aspect, float _zNear, float _zFar) {
       float    xmin, xmax, ymin, ymax;

       ymax = _zNear * MindShake::TanG(_fovY * 0.5f);
       ymin = -ymax;
       xmin = ymin * _aspect;
       xmax = ymax * _aspect;

       return Frustum(xmin, xmax, ymin, ymax, _zNear, _zFar);
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::PerspectiveReverseZ(float _fovY, float _aspect, float _zNear) {
        float f1 = 1.0f / MindShake::TanG(_fovY * 0.5f);
        float f2 = f1 / _aspect;
        return CMatrix4(  f2,  0.0f,   0.0f,  0.0f,
                        0.0f,    f1,   0.0f,  0.0f,
                        0.0f,  0.0f,   0.0f, -1.0f,
                        0.0f,  0.0f, _zNear,  0.0f
        );
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::Frustum(float _left, float _right, float _bottom, float _top, float _zNear, float _zFar) {
        float   x, y, a, b, c, d;

        x =  (2.0f * _zNear)     / (_right - _left);
        y =  (2.0f * _zNear)     / (_top   - _bottom);
        a =  (_right + _left)    / (_right - _left);
        b =  (_top   + _bottom)  / (_top   - _bottom);
        c = -(_zFar  + _zNear)   / (_zFar  - _zNear);
        d = -(2.0f * _zFar * _zNear) / (_zFar - _zNear);

        return CMatrix4(
                   x,  0.0f,   0.0f,  0.0f,
                0.0f,     y,   0.0f,  0.0f,
                   a,     b,      c, -1.0f,
                0.0f,  0.0f,      d,  0.0f
        );
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::LookAt(float    _posx, float    _posy, float    _posz,
                     float _targetx, float _targety, float _targetz,
                     float     _upx, float     _upy, float     _upz) {
        return LookAt(CVector3(_posx,    _posy,    _posz), 
                      CVector3(_targetx, _targety, _targetz), 
                      CVector3(_upx,     _upy,     _upz)
        );
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::LookAt(const CVector3 &_pos, const CVector3 &_target, const CVector3 &_up) {
        CVector3    forward, left, up;

        forward = _pos - _target;
        forward.Normalize();

        left = _up.CrossProduct(-forward);
        if (left.IsNotEqual(CVector3::kZERO)) {
            left.Normalize();
        }
        else {
            left.x = -1.0f;
        }

        up = forward.CrossProduct(left);

        return CMatrix4(left.x,    left.y,    left.z,    0,
                        up.x,      up.y,      up.z,      0,
                        forward.x, forward.y, forward.z, 0,
                        _pos.x,    _pos.y,    _pos.z,    1
        );
    }

    // For cameras!
    //---------------------------------
    inline CMatrix4 
    CMatrix4::InverseLookAt(float    _posx, float    _posy, float    _posz,
                            float _targetx, float _targety, float _targetz,
                            float     _upx, float     _upy, float     _upz) {
        return InverseLookAt(CVector3(_posx,    _posy,    _posz), 
                             CVector3(_targetx, _targety, _targetz), 
                             CVector3(_upx,     _upy,     _upz)
        );
    }

    //---------------------------------
    inline CMatrix4 
    CMatrix4::InverseLookAt(const CVector3 &_pos, const CVector3 &_target, const CVector3 &_up) {
        CVector3    forward, left, up, t;

        forward = _pos - _target;
        forward.Normalize();

        left = _up.CrossProduct(-forward);
        if (left.IsNotEqual(CVector3::kZERO)) {
            left.Normalize();
        }
        else {
            left.x = -1.0f;
        }

        up = forward.CrossProduct(left);

        t.x = -left.x    * _pos.x - left.y    * _pos.y - left.z    * _pos.z;
        t.y = -up.x      * _pos.x - up.y      * _pos.y - up.z      * _pos.z;
        t.z = -forward.x * _pos.x - forward.y * _pos.y - forward.z * _pos.z;

        return CMatrix4(left.x, up.x, forward.x, 0,
                        left.y, up.y, forward.y, 0,
                        left.z, up.z, forward.z, 0,
                        t.x,    t.y,  t.z,       1
        );
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::Viewport(float _left, float _right, float _top, float _bottom, float _near, float _far) {
        float   halfWidth, halfHeight, halfDepth;
        float   tx, ty, tz;

        halfWidth  = (_right  - _left) * 0.5f;
        halfHeight = (_bottom - _top)  * 0.5f;
        halfDepth  = (_far    - _near) * 0.5f;

        tx = _left + halfWidth;
        ty = _top  + halfHeight;
        tz = (_far + _near) * 0.5f;

        return CMatrix4(
            halfWidth,           0,         0, 0,
                    0, -halfHeight,         0, 0,
                    0,           0, halfDepth, 0,
                   tx,          ty,        tz, 1
        );
    }

    //---------------------------------
    inline CMatrix4
    CMatrix4::Viewport(float _left, float _right, float _top, float _bottom) {
        return Viewport(_left, _right, _top, _bottom, 0, 1);
    }

} // end of namespace
