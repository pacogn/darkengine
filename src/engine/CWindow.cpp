#include "CWindow.h"
//-------------------------------------
#include <Common/Math/math_funcs.h>
//-------------------------------------

using namespace MindShake;

//-------------------------------------
#if defined(_MSC_VER)
    #pragma warning(disable: 4100)
#endif

//-------------------------------------
CWindow::CWindow(const char *title, uint32_t width, uint32_t height, uint32_t flags)
    :CWindow(title, width, height, flags, new CRenderer(width, height))
{
}

CWindow::CWindow(const char *title, unsigned width, unsigned height, unsigned flags, CRenderer *Renderer) {
    mWindow = mfb_open_ex(title, width, height, flags);
    if (mWindow) {
        mfb_set_active_callback(mWindow, this, &CWindow::OnActive);
        mfb_set_resize_callback(mWindow, this, &CWindow::OnResize);
        //mfb_set_keyboard_callback(mWindow, this, &CWindow::OnKeyboard);
        //mfb_set_char_input_callback(mWindow, this, &CWindow::OnCharInput);
        //mfb_set_mouse_button_callback(mWindow, this, &CWindow::OnMouseButton);
        //mfb_set_mouse_move_callback(mWindow, this, &CWindow::OnMouseMove);
        //mfb_set_mouse_scroll_callback(mWindow, this, &CWindow::OnMouseScroll);
    }

    mRenderer = Renderer;
}

//-------------------------------------
CWindow::~CWindow() {
    if (mWindow) {
        mfb_close(mWindow);
        mWindow = nullptr;
    }
}

//-------------------------------------
void 
CWindow::AddOnEnterFrame(Event event) {
    mEnterFrame.emplace_back(event);
}

//-------------------------------------
void 
CWindow::AddOnExitFrame(Event event) {
    mExitFrame.emplace_back(event);
}

//-------------------------------------
void 
CWindow::Run() {
    if (mWindow) {
        for (;;) {
            mTimeFrameIni = mTimer.GetTime();
            if (mIsActive) {
                // mRenderer.Clear(0x00);
                mTimeClear = mTimer.GetTime() - mTimeFrameIni;

                double timeUserIni = mTimer.GetTime();
                for(auto &enterFrame : mEnterFrame)
                    enterFrame(this);
                mTimeUser = mTimer.GetTime() - timeUserIni;
            }

            double timeUpdateIni = mTimer.GetTime();
            mfb_update_state state = mfb_update(mWindow, mRenderer->GetColorBuffer());
            if (state != STATE_OK) {
                break;
            }
            mTimeUpdateWin = mTimer.GetTime() - timeUpdateIni;

            for (auto &exitFrame : mExitFrame)
                exitFrame(this);

#if defined(TARGET_PLATFORM_WINDOWS) || defined(TARGET_PLATFORM_LINUX)
            VerticalSync();
#endif
            mTimeFrame = mTimer.GetTime() - mTimeFrameIni;
            mTimeDelta = Min(mTimeFrame, (1.0f / mFPS) * 1.2f);
        }
    }
}

//-------------------------------------
const uint8_t *
CWindow::GetMouseData(int &x, int &y, float &scrollX, float &scrollY) {
    x       = mfb_get_mouse_x(mWindow);
    y       = mfb_get_mouse_x(mWindow);
    scrollX = mfb_get_mouse_scroll_x(mWindow);
    scrollY = mfb_get_mouse_scroll_y(mWindow);

    return mfb_get_mouse_button_buffer(mWindow);
}

//-------------------------------------
void 
CWindow::OnActive(struct mfb_window *window, bool isActive) {
    mIsActive = isActive;
}

//-------------------------------------
void 
CWindow::OnResize(struct mfb_window *window, int width, int height) {
}

//-------------------------------------
void 
CWindow::VerticalSync() {
    double      time, maxTime;

    if (mFPS != 0) {
        maxTime = (1.0f / mFPS);
        time = mTimer.GetTime();
        while (time - mTimeFrameIni < maxTime) {
            mTimer.WaitMillis(0);
            time = mTimer.GetTime();
        }
    }
}
