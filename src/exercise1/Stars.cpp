#include "Stars.h"
//-------------------------------------
#include <engine/CCamera.h>
#include <engine/CWindow.h>
//-------------------------------------
#include <Math/random/FastRand2.h>
#include <Common/Math/math_funcs.h>
#include <Common/Math/constants.h>

//-------------------------------------
using namespace MindShake;

//-------------------------------------
Stars::Stars(CWindow *window, uint32_t numStars, uint32_t depth) {
    mWindow = window;
    mWindow->AddOnEnterFrame(this, &Stars::OnEnterFrame);
    mWindow->AddOnExitFrame(this,  &Stars::OnExitFrame);

    Init(numStars, depth);
}

//-------------------------------------
Stars::~Stars() {
}


//-------------------------------------
void
Stars::Init(uint32_t numStars, uint32_t depth) {
    printf("Debug Keys:\n");
    printf(" - Move XY: Arrow keys\n");
    printf(" - Move Z: Q, A\n");
    printf(" - Speed up: Shift\n");
    printf(" - Show Debug point: D");
    printf("   - Debug: Print: P\n");
    printf("   - Debug: Unproject: U\n");
    printf("   - Debug: To Bottom: B\n");
    printf("   - Debug: To Front: F\n");
    printf(" - Show FPS info: F1\n");

    mWindowWidth     = mWindow->GetRenderer().GetWidth();
    mWindowHeight    = mWindow->GetRenderer().GetHeight();

    mFieldWidth      = uint32_t(mWindowWidth  * 1.25f);
    mFieldHeight     = uint32_t(mWindowHeight * 1.25f);
    mFieldHalfWidth  = mFieldWidth  >> 1;
    mFieldHalfHeight = mFieldHeight >> 1;

    InitCamera(depth);
    InitScene(numStars);
}

//-------------------------------------
void
Stars::InitCamera(uint32_t depth) {
    // Move the camera so that the coordinates (x, y, 0) for the Z=0 plane match the pixels
    float fov = (mCamera.GetFOV() * 0.5f) * Float32::DEGTORAD;
    float distance = (mWindowHeight * 0.5f) * Cos(fov) / Sin(fov);
    mCamera.SetPositionZ(distance);

    mCamera.SetViewport(0, 0, mWindowWidth, mWindowHeight);
    mCamera.SetViewportDepth(1, distance + depth);

    mDepth = uint32_t(Floor(mCamera.GetViewportFar()));

    // Get max and min Z to colorize stars
    mat4 mvp = mCamera.GetViewProjectionMatrix() * mStars.GetMatrixWorld();
    vec4 near = mvp * vec4(0, 0, 0, 1);
    vec4 far  = mvp * vec4(0, 0, -mCamera.GetViewportFar(), 1);
    near /= near.w;
    far  /= far.w;
    mDepthNear = near.z;
    mDepthFar  = far.z;
}

//-------------------------------------
void
Stars::InitScene(uint32_t numStars) {
    vec3        star;

    mStars.mVertexPos.reserve(numStars);
    mStars.mVertexPosTrans.resize(numStars);
    mStars.mVertexColor.resize(numStars);
    for (size_t i = 0; i < numStars; ++i) {
        mStars.mVertexPos.emplace_back(ResetStar(star));
    }

    mDebugStar = vec3(0, 0, -float(mDepth));
}

//-------------------------------------
vec3 &
Stars::ResetStar(vec3 &star) const {
    star.x =  float(FastRand2::Rand() % mFieldWidth)  - mFieldHalfWidth;
    star.y =  float(FastRand2::Rand() % mFieldHeight) - mFieldHalfHeight;
    star.z = -float(FastRand2::Rand() % mDepth);

    return star;
}

//-------------------------------------
void
Stars::OnEnterFrame(CWindow *window) {
    ManageInput();
    Animate();
    Render();
}

//-------------------------------------
void
Stars::Animate() {
    // Move stars
    const float speed = float(100.0 * mWindow->GetTimeDelta());
    for (vec3& star : mStars.mVertexPos) {
        star.z += speed;
    }
}

//-------------------------------------
void
Stars::Render() {
    uint32_t    *colorBuffer = mWindow->GetRenderer().GetColorBuffer();

    mStars.Transform(mCamera);

    size_t numStars = mStars.mVertexPosTrans.size();
    for (size_t i = 0; i < numStars; ++i) {
        const vec3 &star = mStars.mVertexPosTrans[i];
        uint32_t x = int(star.x + 0.5f);
        uint32_t y = int(star.y + 0.5f);

        if (x < mWindowWidth && y < mWindowHeight && star.z >= mDepthFar && star.z <= mDepthNear) {
            uint32_t v = uint32_t(Remap(mDepthFar, mDepthNear, 0, 255, star.z));

            colorBuffer[y * mWindowWidth + x] = MFB_RGB(v, v, v);
        }
        else {
            vec3 &pos = mStars.mVertexPos[i];
            pos.x =  float(FastRand2::Rand() % mFieldWidth)  - mFieldHalfWidth;
            pos.y =  float(FastRand2::Rand() % mFieldHeight) - mFieldHalfHeight;
            pos.z = -float(mDepth);
        }
    }

    //--
    if(mShowDebugStar) {
        vec3 pos = mCamera.Project(mDebugStar);
        uint32_t x = int(pos.x + 0.5f);
        uint32_t y = int(pos.y + 0.5f);
        if (x < mWindowWidth && y < mWindowHeight) {
            colorBuffer[y * mWindowWidth + x] = MFB_RGB(255, 0, 0);
        }
    }
}

//-------------------------------------
void
Stars::ManageInput() {
    uint8_t *keys = const_cast<uint8_t *>(mWindow->GetKeyBuffer());
    int speed = 1;

    if (keys[KB_KEY_LEFT_SHIFT]) {
        speed = 10;
    }

    // X
    if(keys[KB_KEY_LEFT]) {
        mDebugStar.x -= speed;
    }
    if (keys[KB_KEY_RIGHT]) {
        mDebugStar.x += speed;
    }

    // Y
    if (keys[KB_KEY_UP]) {
        mDebugStar.y -= speed;
    }
    if (keys[KB_KEY_DOWN]) {
        mDebugStar.y += speed;
    }

    // Z
    if (keys[KB_KEY_Q]) {
        mDebugStar.z -= speed;
    }
    if (keys[KB_KEY_A]) {
        mDebugStar.z += speed;
    }

     // print
     if(keys[KB_KEY_P]) {
         keys[KB_KEY_P] = false;
         vec3 p = mCamera.Project(mDebugStar);
         printf("%4.3f %4.3f %4.3f -> %4.3f %4.3f %4.3f\n"
             , mDebugStar.x, mDebugStar.y, mDebugStar.z
             , p.x, p.y, p.z
         );
     }

     // UnProject
     if (keys[KB_KEY_U]) {
         keys[KB_KEY_U] = false;
         vec3 p = mCamera.Project(mDebugStar);
         vec3 u = mCamera.UnProject(p);
         printf("U: %4.3f %4.3f %4.3f\n"
             , u.x, u.y, u.z
         );
     }

    // to bottom
    if (keys[KB_KEY_B]) {
        keys[KB_KEY_B] = false;
        float   far = -mCamera.GetViewportFar();
        if (keys[KB_KEY_LEFT_SHIFT])
            mDebugStar.z = far;
        else
            mDebugStar.Set(0, 0, far);
    }

    // to front
    if (keys[KB_KEY_F]) {
        keys[KB_KEY_F] = false;
        float   near = 0;
        if (keys[KB_KEY_LEFT_SHIFT])
            mDebugStar.z = near;
        else
            mDebugStar.Set(0, 0, near);
    }

    // debug star on/off
    if (keys[KB_KEY_D]) {
        keys[KB_KEY_D] = false;
        mShowDebugStar = !mShowDebugStar;
    }

    // debug FPS on/off
    if (keys[KB_KEY_F1]) {
        keys[KB_KEY_F1] = false;
        mShowFPS = !mShowFPS;
        printf("Show FPS: %s\n", mShowFPS ? "Enabled" : "Disabled");
    }
}

//-------------------------------------
void
Stars::OnExitFrame(CWindow *window) {
    static uint32_t    sCounter = 0;
    static float       sTimeClearA = 0;
    static float       sTimeUserA = 0;
    static float       sTimeUpdateWinA = 0;
    static float       sTimeLastFrameA = 0;

    float   timeClear     = float(mWindow->GetTimeClear());
    float   timeUser      = float(mWindow->GetTimeUser());
    float   timeUpdateWin = float(mWindow->GetTimeUpdateWin());
    float   timeLastFrame = float(mWindow->GetTimeLastFrame());

    if (sCounter < 120) {
        ++sCounter;
        sTimeClearA     += timeClear;
        sTimeUserA      += timeUser;
        sTimeUpdateWinA += timeUpdateWin;
        sTimeLastFrameA += timeLastFrame;
    }
    else {
        sTimeClearA     = (sTimeClearA     * 1000.0f) / sCounter;
        sTimeUserA      = (sTimeUserA      * 1000.0f) / sCounter;
        sTimeUpdateWinA = (sTimeUpdateWinA * 1000.0f) / sCounter;
        sTimeLastFrameA = (sTimeLastFrameA * 1000.0f) / sCounter;


        if(mShowFPS) {
            float fps = (1.0f / sTimeLastFrameA) * 1000.0f;
            printf("[ Clear: %.2f, User: %.2f, Update: %.2f, Frame: %.2f, FPS: %2.2f]\n", sTimeClearA, sTimeUserA, sTimeUpdateWinA, sTimeLastFrameA, fps);
        }

        sCounter        = 0;
        sTimeClearA     = 0;
        sTimeUserA      = 0;
        sTimeUpdateWinA = 0;
        sTimeLastFrameA = 0;
    }
}
