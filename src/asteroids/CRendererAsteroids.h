#pragma once

#include <vector>
#include <stdlib.h>
#include <engine/CRenderer.h>

using namespace std;

class CRendererAsteroids : public CRenderer
{
public:
    CRendererAsteroids(uint32_t width, uint32_t height):CRenderer(width, height) {};

    /**
     * Proyect specific implementation of the Draw class
     * Not cost effective since calling a function to draw a
     * pixel is not prudent... :)
     */
    void Draw(int32_t x, int32_t y, uint32_t color)
    {
        float fx, fy;
        WrapCoordinates(x, y, fx, fy);
        CRenderer::Draw(fx,fy,color);
    }
};