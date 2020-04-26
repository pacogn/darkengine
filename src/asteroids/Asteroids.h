#pragma once

#include <engine/CRenderer.h>
#include <vector>
#include <cstdint>

#include <Player.h>

class CWindow;

using std::vector;

struct sSpaceObject
{
    float x;
    float y;
    float dx;
    float dy;
    int nSize;
    float angle;
};

class Asteroids
{
public:
    Asteroids(CWindow *window);
    ~Asteroids();

    vector<sSpaceObject *> vecAsteroids;
    vector<sSpaceObject *> vecBullets;
    Player *player;
    int nLevel = 0;

    void OnEnterFrame(CWindow *window);

    void HandleUserInput();
    void Animate(sSpaceObject &a);
    void Render(sSpaceObject &a);
    void RenderPlayer();
    void ResetStatus(int nAsteroids = 1);
    void CleanseAsteroids();
    void RemoveAllBullets();
    sSpaceObject *
    SpawnAsteroid(int size = 64);
    sSpaceObject *SpawnAsteroid(float x, float y, int size = 64);

    CRenderer &mRenderer;

    vector<pair<float,float>> vecModelAsteroid;

    bool IsPointInsideCircle(float cx, float cy, float radius, float x, float y)
    {
        return Sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
    }

protected:
    CWindow *mWindow {nullptr};
};