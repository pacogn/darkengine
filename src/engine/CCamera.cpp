#include "CCamera.h"
//-------------------------------------
#include <Common/Math/constants.h>

using namespace MindShake;

//-------------------------------------
const mat4 &
CCamera::GetViewMatrix() {

    if (IsDirtyTransformWorld() || mIsDirtyView) {
        CSceneNode::GetMatrixWorld();
        mIsDirtyView = false;

        mView = mMatrixWorld.GetInverseAffine();
    }

    return mView;
}

//-------------------------------------
const mat4 &
CCamera::GetProjectionMatrix() {

    if (mIsDirtyProjection) {
        mIsDirtyProjection = false;

//        mProjection = mat4::Perspective(mFOV, mAspectRatio, mNear, mFar);
        mProjection = mat4::PerspectiveReverseZ(mFOV, mAspectRatio, mViewportNear);
    }

    return mProjection;
}

//-------------------------------------
const mat4 &
CCamera::GetViewProjectionMatrix() {

    if (mIsDirtyTransform || mIsDirtyProjection || mIsDirtyViewProjection) {
        mIsDirtyViewProjection = false;

        mViewProjection = GetProjectionMatrix() * GetViewMatrix();
    }

    return mViewProjection;
}

//-------------------------------------
const mat4 &
CCamera::GetMatrixWorld() {

    if (IsDirtyTransformWorld()) {
        CSceneNode::GetMatrixWorld();
        mIsDirtyView = true;
    }

    return mMatrixWorld;
}

//-------------------------------------
void
CCamera::LookAt(const vec3 &target, const vec3 &up) {
#if 0
    mView = mat4::InverseLookAt(CSceneNode::GetMatrixWorld().GetTranslation(), target, up);
    mIsDirtyView = false;
    mIsDirtyViewProjection = true;

    // The user must or use LookAt or use Euler angles, but not both
    CVector3 angles;
    mView.Extract3x3Matrix().GetTransposed().ToEulerAnglesXYZ(angles.x, angles.y, angles.z);
    angles *= Float32::RADTODEG;
    SetRotation(angles);
#else
    CVector3 angles;
    mat4 mat = mat4::LookAt(CSceneNode::GetMatrixWorld().GetTranslation(), target, up);
    mat.Extract3x3Matrix().ToEulerAnglesXYZ(angles.x, angles.y, angles.z);
    angles *= Float32::RADTODEG;
    SetRotation(angles);
#endif
}

//-------------------------------------
vec3
CCamera::Project(const vec3& pos) {
    mat4    mvp;
    vec4    tmp;
    vec3    out;

    mvp = GetViewProjectionMatrix();

    // Clip coordinates
    tmp = mvp * vec4(pos, 1);
    if (tmp.w != 0) {
        float invW = 1.0f / tmp.w;

        // Normalized Device Coordinates (NDC)
        out = vec3(tmp.x * invW, tmp.y * invW, tmp.z * invW);

        // Window Coordinates (Screen Coordinates)
        out.x = (out.x + 1) * (mViewportWidth  * 0.5f) + mViewportX;
        out.y = (out.y + 1) * (mViewportHeight * 0.5f) + mViewportY;
        // let Z as z/w
    }
    else {
        out.Set(0, 0, Float32::POS_INFINITY);
    }

    return out;
}

//-------------------------------------
vec3
CCamera::UnProject(const vec3 &pos) {
    mat4    mvpI;
    vec4    in, out;

    mvpI = GetViewProjectionMatrix().GetInverse();

    in = pos;

    // Map x and y from window coordinates
    in.x = (in.x - mViewportX) / mViewportWidth;
    in.y = (in.y - mViewportY) / mViewportHeight;
    // In this case, let Z as is

    // Map to range -1 to 1
    in.x = in.x * 2 - 1;
    in.y = in.y * 2 - 1;

    out = mvpI * in;

    out.x /= out.w;
    out.y /= out.w;
    out.z /= out.w;

    return out.GetXYZ();
}
