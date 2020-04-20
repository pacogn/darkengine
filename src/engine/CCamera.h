#pragma once

#include "CSceneNode.h"

//-------------------------------------
class CCamera : public CSceneNode {
public:
                        CCamera()                           = default;
    virtual             ~CCamera()                          = default;

    void                SetFOV(float angle)                 { SetDirtyTransformProjection(); mFOV = angle; }
    float               GetFOV() const                      { return mFOV;  }

    void                SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    uint32_t            GetViewportX() const                { return mViewportX;        }
    uint32_t            GetViewportY() const                { return mViewportY;        }
    uint32_t            GetViewportWidth() const            { return mViewportWidth;    }
    uint32_t            GetViewportHeight() const           { return mViewportHeight;   }

    void                SetViewportDepth(float near, float far) { SetViewportNear(near); SetViewportFar(far);  }

    void                SetViewportNear(float nearDistance) { SetDirtyTransformProjection(); mViewportNear = nearDistance; }
    float               GetViewportNear() const             { return mViewportNear; }

    void                SetViewportFar(float farDistance)   { SetDirtyTransformProjection(); mViewportFar = farDistance; }
    float               GetViewportFar() const              { return mViewportFar; }

    void                SetAspectRatio(float aspect)        { SetDirtyTransformProjection(), mAspectRatio = aspect; }

    const mat4 &        GetViewMatrix();
    const mat4 &        GetProjectionMatrix();
    const mat4 &        GetViewProjectionMatrix();
    const mat4 &        GetMatrixWorld() override;

    void                SetDirtyTransformView()             { mIsDirtyViewProjection = true; mIsDirtyView = true;          }
    bool                IsDirtyTransformView() const        { return mIsDirtyView;          }

    void                SetDirtyTransformProjection()       { mIsDirtyViewProjection = true; mIsDirtyProjection = true;    }
    bool                IsDirtyTransformWProjection() const { return mIsDirtyProjection;    }

    void                LookAt(const vec3 &target, const vec3 &up = vec3(0, -1, 0));

    vec3                Project(const vec3& pos);
    vec3                UnProject(const vec3 &pos);

private:
                        CCamera(const CCamera &)   = delete;
                        CCamera(CCamera &&)        = delete;

    CCamera &           operator=(const CCamera &) = delete;
    CCamera &           operator=(CCamera &&)      = delete;

private:
    mat4        mView           { mat4::kIDENTITY };
    mat4        mProjection     { mat4::kIDENTITY };
    mat4        mViewProjection { mat4::kIDENTITY };

    float       mFOV            { 45 };
    float       mAspectRatio    { 4.0f / 3.0f };

    uint32_t    mViewportX      { 0 };
    uint32_t    mViewportY      { 0 };
    uint32_t    mViewportWidth  { 1 };
    uint32_t    mViewportHeight { 1 };
    float       mViewportNear   { 1 };
    float       mViewportFar    { 0xffff };

    bool        mIsDirtyView           { true };
    bool        mIsDirtyProjection     { true };
    bool        mIsDirtyViewProjection { true };
};

//-------------------------------------
inline void
CCamera::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    mViewportX      = x;
    mViewportY      = y;
    mViewportWidth  = width;
    mViewportHeight = height;
    SetAspectRatio((height > 0) ? float(width) / float(height) : 1.0f);
}

