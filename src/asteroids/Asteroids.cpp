#include "Asteroids.h"
#include <engine/CWindow.h>

using namespace MindShake;

Asteroids::Asteroids(CWindow *window) : rRenderer(window->GetRenderer()) {
    mWindow = window;

    vecAsteroids.push_back({20.0f, 20.0f, 10.0f, -10.0f, (int)1});
    mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
};

Asteroids::~Asteroids() {
};

void
Asteroids::OnEnterFrame(CWindow *window) {
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

    if (a.x > mWindow->GetRenderer().GetWidth())
    {
        a.dx *= -1.0;
    }

    if (a.y > mWindow->GetRenderer().GetHeight())
    {
        a.dy *= -1.0;
    }
};

void
Asteroids::Render(sSpaceObject &a) {
    rRenderer.SetPixel(a.x, a.y, 0x22);
};