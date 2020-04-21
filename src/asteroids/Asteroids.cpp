#include "Asteroids.h"
#include <engine/CWindow.h>

using namespace MindShake;

Asteroids::Asteroids(CWindow *window) : mDrawer(window) {
    mWindow = window;
    mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
};

Asteroids::~Asteroids() {
};

void
Asteroids::OnEnterFrame(CWindow *window) {
    uint32_t *colorBuffer = mWindow->GetRenderer().GetColorBuffer();

    Animate(colorBuffer);
    Render(colorBuffer);
};

void
Asteroids::Animate(uint32_t *colorBuffer) {
};

void
Asteroids::Render(uint32_t *colorBuffer) {
    mDrawer.Fill(0x7f);
};