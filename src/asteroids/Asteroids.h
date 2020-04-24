#pragma once

#include <engine/CRenderer.h>
#include <vector>
#include <cstdint>

class CWindow;

using std::vector;

struct sSpaceObject
{
    float x;
    float y;
    float dx;
    float dy;
    int nSize;
};

class Asteroids
{
public:
    Asteroids(CWindow *window);
    ~Asteroids();

    vector<sSpaceObject> vecAsteroids;

    void OnEnterFrame(CWindow *window);

    void Animate(sSpaceObject &a);
    void Render(sSpaceObject &a);

    CRenderer &rRenderer;
protected:
    CWindow *mWindow {nullptr};

};