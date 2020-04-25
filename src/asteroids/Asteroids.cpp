#include "Asteroids.h"
#include <engine/CWindow.h>
#include <engine/CRenderer.h>
#include <CRendererAsteroids.h>

#include <Common/Math/math_funcs.h>
#include <Common/Math/constants.h>

using namespace MindShake;

Asteroids::Asteroids(CWindow *window) : mRenderer(window->GetRenderer()) {
    mWindow = window;

    vecAsteroids.emplace_back(
        new sSpaceObject({70.0f, 40.0f, 20.0f, -50.0f, (int)1, 0.0f})
    );

    player = new Player(
        mRenderer.GetWidth() / 2.0f, mRenderer.GetHeight() / 2.0f,
        0, 0,
        0
    );


    // init asteroids;
    int verts = 20;
    for (int i=0; i < verts; i++) {
        float radius = 5.0f;
        float a = ((float)i / (float)verts) * 6.28318f;

        vecModelAsteroid.push_back(make_pair(radius * Sin(a), radius * Cos(a)));
    }

    // mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
    mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
};

Asteroids::~Asteroids() {
    for (auto *a : vecAsteroids)
    {
        delete a;
    }

    delete player;
};

void
Asteroids::OnEnterFrame(CWindow *window) {

    mRenderer.Clear(0x00);

    HandleUserInput();

    // render asteroids
    for (auto *a : vecAsteroids)
    {
        a->x += a->dx * mWindow->GetDeltaTime();
        a->y += a->dy * mWindow->GetDeltaTime();

        mRenderer.WrapCoordinates(a->x, a->y, a->x, a->y);

        // HERE! POR QUE PETA!!
        mRenderer.DrawWireframeModel(vecModelAsteroid, a->x, a->y, 1, 0xffffff);
    }

    player->Render(&mRenderer);
};

void
Asteroids::HandleUserInput() {
   uint8_t *keys = const_cast<uint8_t *>(mWindow->GetKeyBuffer());

    // Quit
    if (keys[KB_KEY_Q])
    {
        exit(0);
    }

    // Reset
    if (keys[KB_KEY_R])
    {
    }

    // Steer
    if (keys[KB_KEY_J])
    {
        player->angle -= 5.0f * mWindow->GetDeltaTime();
    }

    if (keys[KB_KEY_K])
    {
        player->angle += 5.0f * mWindow->GetDeltaTime();
    }

    // Thrust
    if (keys[KB_KEY_F])
    {
        // ACCELERATION changes VELOCITY (with respecto of time)
        player->acc->x += Sin(player->angle) * F * mWindow->GetDeltaTime();
        player->acc->y += -Cos(player->angle) * F * mWindow->GetDeltaTime();
    }

    // VELOCITY changes POSITION (with respect of time)
    player->pos->x += player->acc->x * mWindow->GetDeltaTime();
    player->pos->y += player->acc->y * mWindow->GetDeltaTime();

    mRenderer.WrapCoordinates(player->pos->x, player->pos->y, player->pos->x, player->pos->y);
};
