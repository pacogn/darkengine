#pragma once

#include <engine/CRenderer.h>
#include <Common/Core/containers/TVector.h>
#include <cstdint>
#include <memory>

class CWindow;
class Player;

using MindShake::TVector;
using std::pair;

//-------------------------------------
struct sSpaceObject
{
    float   x;
    float   y;
    float   dx;
    float   dy;
    int     nSize;
    float   angle;
    bool    isDead;
};

//-------------------------------------
class Asteroids
{
public:
                    Asteroids(CWindow *window);
                    ~Asteroids();

    void            OnEnterFrame(CWindow *window);

    void            HandleUserInput();
    void            Animate(sSpaceObject &a);
    void            Render(sSpaceObject &a);
    void            RenderPlayer();
    void            ResetStatus(int nAsteroids = 1);
    void            RemoveAllBullets();
    sSpaceObject *  SpawnAsteroid(int size = 64);
    sSpaceObject *  SpawnAsteroid(float x, float y, float speed, int size = 64);
    sSpaceObject *  SpawnBullet();

    bool            IsPointInsideCircle(float cx, float cy, float radius, float x, float y);

protected:
    CWindow                 *mWindow {nullptr};

    TVector<sSpaceObject *> poolAsteroids;
    TVector<sSpaceObject *> vecAsteroids;
    TVector<sSpaceObject *> poolBullets;
    TVector<sSpaceObject *> vecBullets;
    Player                  *player { nullptr };
    int                     nLevel = 0;

    CRenderer               &mRenderer;

    vector<pair<float, float>> vecModelAsteroid;
};