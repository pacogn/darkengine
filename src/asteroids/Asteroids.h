#pragma once

#include <vector>
#include <cstdint>

class CWindow;

using std::vector;

class Asteroids
{
public:
    Asteroids(CWindow *window);
    ~Asteroids();

    void OnEnterFrame(CWindow *window);

    void Animate(uint32_t *colorBuffer);
    void Render(uint32_t *colorBuffer);

protected:
    CWindow *mWindow{nullptr};
};