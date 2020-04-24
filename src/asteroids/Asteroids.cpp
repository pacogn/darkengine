#include "Asteroids.h"
#include <engine/CWindow.h>

using namespace MindShake;

Asteroids::Asteroids(CWindow *window) : rRenderer(window->GetRenderer()) {
    mWindow = window;

    vecAsteroids.push_back({70.0f, 40.0f, 20.0f, -50.0f, (int)1});
    mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
};

Asteroids::~Asteroids() {
};

void
Asteroids::OnEnterFrame(CWindow *window) {

    rRenderer.Clear(0x00);
    for (auto &a : vecAsteroids)
    {
        Animate(a);
        Render(a);
    }
};

void
Asteroids::Animate(sSpaceObject &a) {
    // a = (v2 - v1) / t

    // v2 = a*t + v1
    // p2 = v*t + p1

    a.x += a.dx * mWindow->GetDeltaTime();
    a.y += a.dy * mWindow->GetDeltaTime();

    rRenderer.WrapCoordinates(a.x, a.y, a.x, a.y);
};

void
Asteroids::Render(sSpaceObject &a)
{
    //TODO: redefine pixel size in drawing functions.
    rRenderer.DrawRectangle(a.x, a.y, 100, 100, MFB_RGB(0,255,0));
};


//TODO: where should i put this? utils file?? transformation class?