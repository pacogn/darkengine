#pragma once

#include <engine/CCamera.h>
#include <engine/CMesh.h>
//-------------------------------------
#include <vector>
#include <cstdint>

//-------------------------------------
class CWindow;

using std::vector;
using mat4 = MindShake::CMatrix4;
using vec3 = MindShake::CVector3;

//-------------------------------------
class Stars
{
public:
            Stars(CWindow *window, uint32_t numStars, uint32_t depth);
            ~Stars();

    void    OnEnterFrame(CWindow *window);
    void    OnExitFrame(CWindow *window);

    void    Init(uint32_t numStars, uint32_t depth);
    void    InitCamera(uint32_t depth);
    void    InitScene(uint32_t numStars);
    vec3 &  ResetStar(vec3 &star) const;

    void    Animate();
    void    ManageInput();
    void    Render();

protected:
    CWindow     *mWindow         { nullptr };
    CCamera     mCamera;
    CMesh       mStars;
    uint32_t    mWindowWidth     { 0 };
    uint32_t    mWindowHeight    { 0 };
    uint32_t    mFieldWidth      { 0 };
    uint32_t    mFieldHalfWidth  { 0 };
    uint32_t    mFieldHeight     { 0 };
    uint32_t    mFieldHalfHeight { 0 };
    uint32_t    mDepth           { 1024 };
    float       mDepthNear       { 0 };
    float       mDepthFar        { 1 };
    vec3        mDebugStar;
    bool        mShowDebugStar  { false };
    bool        mShowFPS        { false };
};
