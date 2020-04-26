#include "Asteroids.h"
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

    // anit asteroids;
    int verts = 20;
    for (int i=0; i < verts; i++) {
        float rnd = ((float)rand() / (float)RAND_MAX);
        float radius = (rnd/5.0f) + 0.8f;
        float a = ((float)i / (float)verts) * 6.28318f;

        vecModelAsteroid.push_back(make_pair(radius * Sin(a), radius * Cos(a)));
    }

    // mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
    mWindow->AddOnEnterFrame(this, &Asteroids::OnEnterFrame);
};

Asteroids::~Asteroids() {
    for (auto *a : vecAsteroids) delete a;
    for (auto *b : vecBullets) delete b;
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
    for (int i = 0; i < (int)vecBullets.size(); ++i)
    {
        auto* b = vecBullets[i];

        b->x += b->dx * deltaTime;
        b->y += b->dy * deltaTime;

        // delete bullet if out of boundries of the screen
        // take into account the size of the bullet
        if (b->x < 0 || (b->x + b->nSize) >= mRenderer.GetWidth() || b->y < 0 || (b->y + b->nSize) >= mRenderer.GetHeight())
        {
            delete vecBullets[i];
            vecBullets.erase(vecBullets.begin() + i);
            --i;
            break;
        }

        // Collition detection of the bullet
        for (int j = 0; j < (int)vecAsteroids.size(); ++j)
        {
            auto* a = vecAsteroids[j];

            // Check if we hit the asteroid
            if (IsPointInsideCircle(a->x, a->y, a->nSize, b->x, b->y))
            {
                // delete bullet, it will get removed when purging bullets off the screen
                b->x = -100; // delete bullet, it will get removed when purging bullets off the screen

                // if asteroid is big enough, split it
                if (a->nSize > 8)
                {
                    // calculate random angles of ejection... apply physics here!
                    float angle1 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
                    float angle2 = ((float)rand() / (float)RAND_MAX) * 6.283185f;

                    // creating two new ones
                    vecNewAsteroids.push_back(new sSpaceObject({
                        a->x, a->y,
                        (1.0f/a->nSize)*3000.0f * Sin(angle1), -(1.0f/a->nSize)*3000.0f * Cos(angle1),
                        (int) a->nSize >> 1,
                        (float) (rand()%360)
                    }));

                    vecNewAsteroids.push_back(new sSpaceObject({
                        a->x, a->y,
                        (1.0f/a->nSize)*3000.0f * Sin(angle2), -(1.0f/a->nSize)*3000.0f * Cos(angle2),
                        (int) a->nSize >> 1,
                        (float) (rand()%360)
                    }));
                }

                // when done, we mark the original asteroid to be deleted
                a->x = -100;
            }
        }

        // Add recently created asteroids if there is a hit
        for (auto &a : vecNewAsteroids) 
            vecAsteroids.emplace_back(a);

        // remove offscreen asteroids
        if (vecAsteroids.size() > 0)
            ClenseAsteroids();
        else
        {
            // LEVEL COMPLETE!
            player->Reset();
            vecAsteroids.push_back(SpawnAsteroid(64));
            vecAsteroids.push_back(SpawnAsteroid(64));
        }

        // translate bullet into world coordinates
        mRenderer.WrapCoordinates(b->x, b->y, b->x, b->y);
        mRenderer.DrawRectangle(b->x, b->y, b->nSize, b->nSize, 0xCCCCCC);
    }

    // Check ship collision with asteroids
    for (auto &a : vecAsteroids) {
        if (IsPointInsideCircle(a->x, a->y, a->nSize, player->pos->x, player->pos->y)) {
            player->Hit();
        }
    }

    player->Render(&mRenderer);
};

void Asteroids::ClenseAsteroids()
{
    for (size_t i = 0; i < vecAsteroids.size(); ++i)
    {
        if (vecAsteroids[i]->x < -99)
        {
            delete vecAsteroids[i];
            vecAsteroids.erase(vecAsteroids.begin() + i);
        }
    }
};

void
Asteroids::ResetStatus(int nAsteroids)
{
    for (auto *a : vecAsteroids) a->x = -101.01111f;
    ClenseAsteroids();

    player->Reset(mRenderer.GetHalfWidth(), mRenderer.GetHalfHeight());

    for (int i = 0; i <= nAsteroids; ++i)
        vecAsteroids.emplace_back(SpawnAsteroid());
};

sSpaceObject *
Asteroids::SpawnAsteroid(int size)
{
    float x = (rand() % (mRenderer.GetWidth() - 20)) +20;
    float y = (rand() % (mRenderer.GetHeight() - 20)) +20;

    return SpawnAsteroid(x, y, size);
}

sSpaceObject *
Asteroids::SpawnAsteroid(float x, float y, int size)
{
    float angle = ((float)rand() / (float)RAND_MAX) * 6.283185f;

    float dx =  (1.0f / size) * 3000.0f * Sin(angle);
    float dy = -(1.0f / size) * 3000.0f * Cos(angle);

    return (new sSpaceObject({x, y, dx, dy, size, angle}));
}

void Asteroids::HandleUserInput()
{
    uint8_t *keys = const_cast<uint8_t *>(mWindow->GetKeyBuffer());
    float deltaTime = mWindow->GetDeltaTime();

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
        if (keys[KB_KEY_J])
            player->SteerLeft(deltaTime);
        if (keys[KB_KEY_K])
            player->SteerRight(deltaTime);

        // Thrust
        if (keys[KB_KEY_SPACE])
            player->Thrust(deltaTime);

        // Fire!
        if (keys[KB_KEY_F])
        {
            keys[KB_KEY_F] = false;

            vecBullets.emplace_back(new sSpaceObject({
                player->pos->x,
                player->pos->y,
                player->vel->x + (500.0f * Sin(player->angle)),
                player->vel->y - (500.0f * Cos(player->angle)),
                5, 5
            }));
        }
    }

    player->Update(mWindow->GetDeltaTime());
};
