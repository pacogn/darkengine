#include "Asteroids.h"
#include "Player.h"
#include <engine/CWindow.h>
#include <engine/CRenderer.h>
#include <CRendererAsteroids.h>

#include <Common/Math/math_funcs.h>
#include <Common/Math/constants.h>

using namespace MindShake;

Asteroids::Asteroids(CWindow *window) : mRenderer(window->GetRenderer()) {
    mWindow = window;

    vecAsteroids.emplace_back(SpawnAsteroid());

    player = new Player(
        mRenderer.GetHalfWidth(), mRenderer.GetHalfHeight(),
        0, 0,
        0
    );

    // init asteroids;
    int verts = 20;
    for (int i=0; i < verts; i++) {
        float rnd = ((float)rand() / (float)RAND_MAX);
        float radius = (rnd/5.0f) + 0.8f;
        float a = ((float)i / (float)verts) * 6.28318f;

        vecModelAsteroid.emplace_back(radius * Sin(a), radius * Cos(a));
    }

    // mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
    mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
};

Asteroids::~Asteroids() {
    vecAsteroids.clear();
    vecBullets.clear();
    for (auto *a : poolAsteroids) delete a;
    for (auto *b : poolBullets)   delete b;
    poolAsteroids.clear();
    poolBullets.clear();
    delete player;
};

void
Asteroids::OnEnterFrame(CWindow *window) {
    vector<sSpaceObject *> vecNewAsteroids;

    mRenderer.Clear(0x00);

    HandleUserInput();

    float deltaTime = mWindow->GetDeltaTime();

    // render asteroids
    for (auto *a : vecAsteroids)
    {
        a->x += a->dx * deltaTime;
        a->y += a->dy * deltaTime;
        a->angle += 0.25f * deltaTime;
        mRenderer.WrapCoordinates(a->x, a->y, a->x, a->y);

        mRenderer.DrawWireframeModel(vecModelAsteroid, a->x, a->y, a->angle, a->nSize, 0xffffff);
    }

    // render bullets
    for (auto *b : vecBullets)
    {
        b->x += b->dx * deltaTime;
        b->y += b->dy * deltaTime;

        // delete bullet if out of boundaries of the screen
        // take into account the size of the bullet
        if (b->x < 0 || (b->x + b->nSize) >= mRenderer.GetWidth() || b->y < 0 || (b->y + b->nSize) >= mRenderer.GetHeight())
        {
            b->isDead = true;
            continue;
        }

        // Collision detection of the bullet
        for (auto* a : vecAsteroids)
        {
            // Check if we hit the asteroid
            if (IsPointInsideCircle(a->x, a->y, a->nSize, b->x, b->y))
            {
                // delete bullet, it will get removed when purging bullets off the screen
                b->isDead = true; // delete bullet, it will get removed when purging bullets off the screen

                // if asteroid is big enough, split it
                if (a->nSize > 8)
                {
                    // calculate random angles of ejection... apply physics here!
                    //float angle1 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
                    //float angle2 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
                    float angle1 = a->angle + 90;
                    float angle2 = a->angle - 90;

                    vecNewAsteroids.emplace_back(SpawnAsteroid(a->x, a->y, angle1, a->nSize >> 1));
                    vecNewAsteroids.emplace_back(SpawnAsteroid(a->x, a->y, angle2, a->nSize >> 1));
                }

                // when done, we mark the original asteroid to be deleted
                a->isDead = true;
                b->isDead = true;
                break;
            }
        }

        // Add recently created asteroids if there is a hit
        for (auto &a : vecNewAsteroids) 
            vecAsteroids.emplace_back(a);

        // remove off screen asteroids
        if (!vecAsteroids.empty())
        {
            // Clean dead asteroids
            vecAsteroids.erase([](const auto &v) {
                return v->isDead;
            });
        }
        else
        {
            // LEVEL COMPLETE!
            player->Reset();
            vecAsteroids.emplace_back(SpawnAsteroid(64));
            vecAsteroids.emplace_back(SpawnAsteroid(64));
        }

        // translate bullet into world coordinates
        mRenderer.WrapCoordinates(b->x, b->y, b->x, b->y);
        mRenderer.DrawRectangle(b->x, b->y, b->nSize, b->nSize, 0xCCCCCC);
    }

    // Clean dead bullets
    vecBullets.erase([](const auto &v) {
        return v->isDead;
    });

    // Check ship collision with asteroids
    for (auto &a : vecAsteroids) {
        if (IsPointInsideCircle(a->x, a->y, a->nSize, player->pos->x, player->pos->y)) {
            player->Hit();
        }
    }

    player->Render(&mRenderer);
};

void
Asteroids::ResetStatus(int nAsteroids) {
    vecAsteroids.clear();
    player->Reset(mRenderer.GetHalfWidth(), mRenderer.GetHalfHeight());

    for (int i = 0; i <= nAsteroids; ++i)
        vecAsteroids.emplace_back(SpawnAsteroid());
};

sSpaceObject *
Asteroids::SpawnAsteroid(int size) {
    float x     = (rand() % (mRenderer.GetWidth()  - 20)) + 20;
    float y     = (rand() % (mRenderer.GetHeight() - 20)) + 20;
    float angle = ((float) rand() / (float) RAND_MAX) * 6.283185f;

    return SpawnAsteroid(x, y, angle, size);
}

sSpaceObject *
Asteroids::SpawnAsteroid(float x, float y, float angle, int size) {
    sSpaceObject    *a;

    int32_t idx = poolAsteroids.find([](const auto &v) -> bool {
        return v->isDead;
    });
    if(idx != -1) {
        a = poolAsteroids[idx];
    }
    else {
        a = poolAsteroids.emplace_back(new sSpaceObject()).back();
    }
    float dx =  (1.0f / size) * 3000.0f * Sin(angle);
    float dy = -(1.0f / size) * 3000.0f * Cos(angle);
    *a = { x, y, dx, dy, size, angle, false };

    return a;
}

sSpaceObject *
Asteroids::SpawnBullet() {
    sSpaceObject *b;

    int32_t idx = poolBullets.find([](const auto &v) -> bool {
        return v->isDead;
    });
    if (idx != -1) {
        b = poolBullets[idx];
    }
    else {
        b = poolBullets.emplace_back(new sSpaceObject()).back();
    }

    *b = { 
        player->pos->x,
        player->pos->y,
        player->vel->x + (500.0f * Sin(player->angle)),
        player->vel->y - (500.0f * Cos(player->angle)),
        5, 5
    };

    return b;
}

bool 
Asteroids::IsPointInsideCircle(float cx, float cy, float radius, float x, float y) {
    return Sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
}

void 
Asteroids::HandleUserInput() {
    static float lastBulletTime = 0;
    const float  fireRate = 0.25f;
    uint8_t *keys = const_cast<uint8_t *>(mWindow->GetKeyBuffer());

    float   deltaTime = mWindow->GetDeltaTime();
    float   time      = mWindow->GetTime();

    // Quit
    if (keys[KB_KEY_Q])
        exit(0);

    // Reset
    if (keys[KB_KEY_R])
    {
        keys[KB_KEY_R] = false;
        if (!keys[KB_KEY_LEFT_SHIFT])
            ++nLevel;

        ResetStatus(nLevel);

        return;
    }

    if (!player->dead)
    {
        // Steer
        if (keys[KB_KEY_J] || keys[KB_KEY_LEFT])
            player->SteerLeft(deltaTime);
        if (keys[KB_KEY_K] || keys[KB_KEY_RIGHT])
            player->SteerRight(deltaTime);

        // Thrust
        if (keys[KB_KEY_SPACE])
            player->Thrust(deltaTime);

        // Fire!
        if(lastBulletTime + fireRate < time) 
        {
            if (keys[KB_KEY_F])
            {
                lastBulletTime = time;
                vecBullets.emplace_back(SpawnBullet());
            }
        }
    }

    player->Update(mWindow->GetDeltaTime());
};
