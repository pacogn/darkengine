#include "Asteroids.h"
#include <engine/CWindow.h>

#include <Common/Math/math_funcs.h>
#include <Common/Math/constants.h>

using namespace MindShake;

Asteroids::Asteroids(CWindow *window) : mRenderer(window->GetRenderer()) {
    mWindow = window;

    vecAsteroids.emplace_back(
        new sSpaceObject({70.0f, 40.0f, 20.0f, -50.0f, (int)1, 0.0f})
    );

    player.x = mRenderer.GetWidth() / 2.0f;
    player.y = mRenderer.GetHeight() / 2.0f;
    player.dx = 0;
    player.dy = 0;
    player.angle = 0;

    // mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
    mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
};

Asteroids::~Asteroids() {
    for (auto *a : vecAsteroids)
    {
        delete a;
    } 
};

void
Asteroids::OnEnterFrame(CWindow *window) {

    mRenderer.Clear(0x00);

    HandleUserInput();

    // render asteroids
    for (auto *a : vecAsteroids)
    {
        Animate(*a);
        Render(*a);
    }

    RenderPlayer();
};

void
Asteroids::HandleUserInput() {
    uint8_t *keys = const_cast<uint8_t *>(mWindow->GetKeyBuffer());

    // Reset
    if (keys[KB_KEY_R])
    {

        player.x = mRenderer.GetWidth() / 2.0f;
        player.y = mRenderer.GetHeight() / 2.0f;
        player.dx = 0;
        player.dy = 0;
        player.angle = 0;
    }

    // Steer
    if (keys[KB_KEY_J])
    {
        printf("Chaning angle Left\n");
        player.angle -= 5.0f * mWindow->GetDeltaTime();
    }

    if (keys[KB_KEY_L])
    {
        printf("Chaning angle Right\n");
        player.angle += 5.0f * mWindow->GetDeltaTime();
    }

    // Thrust
    if (keys[KB_KEY_F])
    {
        // ACCELERATION changes VELOCITY (with respecto of time)
        printf("Accelerate\n");
        player.dx += Sin(player.angle) * F * mWindow->GetDeltaTime();
        player.dy += -Cos(player.angle) * F * mWindow->GetDeltaTime();
    }

    // VELOCITY changes POSITION (with respect of time)
    player.x += player.dx * mWindow->GetDeltaTime();
    player.y += player.dy * mWindow->GetDeltaTime();

    printf("angle: %4.2f\n", player.angle);
    printf("x1: %4.2f y1: %4.2f\n", player.x, player.y);
    printf("dx: %4.2f dy: %4.2f\n", player.x, player.y);

    mRenderer.WrapCoordinates(player.x, player.y, player.x, player.y);
    printf("x2: %4.2f y:2%4.2f\n", player.x, player.y);
    printf("------------------\n");
};

void Asteroids::RenderPlayer()
{
    mRenderer.DrawRectangle(player.x, player.y, 100, 100, MFB_RGB(255, 255, 0));
};

void Asteroids::Animate(sSpaceObject &a)
{
    // a = (v2 - v1) / t

    // v2 = a*t + v1
    // p2 = v*t + p1

    a.x += a.dx * mWindow->GetDeltaTime();
    a.y += a.dy * mWindow->GetDeltaTime();

    mRenderer.WrapCoordinates(a.x, a.y, a.x, a.y);
};

void Asteroids::Render(sSpaceObject &a)
{
    mRenderer.DrawRectangle(a.x, a.y, 100, 100, MFB_RGB(0, 255, 0));
};

//TODO: where should i put this? utils file?? transformation class?