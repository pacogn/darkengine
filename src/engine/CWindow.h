#pragma once

#include "CRenderer.h"
//-------------------------------------
#include <Kernel/timer/CChronoTimer.h>
//-------------------------------------
#include <MiniFB.h>
//-------------------------------------
#include <vector>
#include <functional>

//-------------------------------------
using namespace std::placeholders;

//-------------------------------------
class CWindow {
    using CChronoTimer = MindShake::CChronoTimer;
    using Event        = std::function<void(CWindow *)>;
    using Events       = std::vector<Event>;
    using KeyEvent     = std::function<void(CWindow *, mfb_key, mfb_key_mod, bool)>;
    using KeyEvents    = std::vector<KeyEvent>;

public:
                CWindow(const char *title, unsigned width, unsigned height, unsigned flags);
                ~CWindow();

    CRenderer & GetRenderer()               { return mRenderer;     }

    template<typename T>
    void        AddOnEnterFrame(T *obj, void (T::*method)(CWindow *)) { AddOnEnterFrame(std::bind(method, obj, _1));  }
    void        AddOnEnterFrame(Event event);

    template<typename T>
    void        AddOnExitFrame(T* obj, void (T::* method)(CWindow*)) { AddOnExitFrame(std::bind(method, obj, _1)); }
    void        AddOnExitFrame(Event event);

    void        Run();

    void        SetFPS(uint32_t fps)        { mFPS = fps;}

// Getters
public:
    uint32_t    GetFPS() const              { return mFPS;          }
    double      GetTimeDelta() const        { return mTimeDelta;    }
    double      GetTimeClear() const        { return mTimeClear;    }
    double      GetTimeUser() const         { return mTimeUser;     }
    double      GetTimeUpdateWin() const    { return mTimeUpdateWin; }
    double      GetTimeLastFrame() const    { return mTimeFrame;    }

    const uint8_t *GetKeyBuffer() const     { return mfb_get_key_buffer(mWindow); }
    const uint8_t *GetMouseData(int &x, int &y, float &scrollX, float &scrollY);

// MiniFB interface
protected:
    void        OnActive(struct mfb_window *window, bool isActive);
    void        OnResize(struct mfb_window *window, int width, int height);

protected:
    void        VerticalSync();

private:
                CWindow(const CWindow &) = delete;
                CWindow(CWindow &&) = delete;

    CWindow &   operator=(const CWindow &) = delete;
    CWindow &   operator=(CWindow &&) = delete;

private:
    struct mfb_window   *mWindow      { nullptr };
    CRenderer       mRenderer;
    bool            mIsActive     { true };

    uint32_t        mFPS { 60 };
    CChronoTimer    mTimer;
    double          mTimeClear{};
    double          mTimeUser{};
    double          mTimeUpdateWin{};
    double          mTimeFrameIni{};
    double          mTimeFrame{};
    double          mTimeDelta{};
    Events          mEnterFrame;
    Events          mExitFrame;
    KeyEvents       mKeyEvents;
};
