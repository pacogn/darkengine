#include "CRenderer.h"
//-------------------------------------
#include <Core/memory/memory.h>
//-------------------------------------
#include <memory.h>
#include <stdlib.h>

using namespace MindShake;

//-------------------------------------
CRenderer::CRenderer(uint32_t width, uint32_t height)
{
    mWidth = width;
    mHeight = height;

    mColorBuffer = (uint32_t *)AlignedMalloc(width * height * sizeof(uint32_t), 64);
}

//-------------------------------------
CRenderer::~CRenderer()
{
    if (mColorBuffer != nullptr)
    {
        AlignedFree(mColorBuffer);
    }
}

//-------------------------------------
void CRenderer::Clear(uint8_t i)
{
    memset(mColorBuffer, i, mWidth * mHeight * 4);
}

//-------------------------------------
void CRenderer::SetPixel(int32_t x, int32_t y, uint32_t color)
{
    if(uint32_t(x) < mWidth && uint32_t(y) < mHeight) 
        mColorBuffer[y * mWidth + x] = color;
};

//-------------------------------------
void CRenderer::Draw(int32_t x, int32_t y, uint32_t color)
{
    if (true) {
        float fx, fy;
        WrapCoordinates(x, y, fx, fy);
        SetPixel(fx, fy, color);
    }
    else {
        SetPixel(x, y, color);
    }
};

// MAGIC PPL VOODOO PPL!!
//-------------------------------------
void CRenderer::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color, uint32_t pattern)
{
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1;
    dy = y2 - y1;

    auto rol = [&](void) { pattern = (pattern << 1) | (pattern >> 31); return pattern & 1; };

    // straight lines idea by gurkanctn
    if (dx == 0) // Line is vertical
    {
        if (y2 < y1)
            std::swap(y1, y2);
        for (y = y1; y <= y2; y++)
            if (rol())
                Draw(x1, y, color);
        return;
    }

    // maybe in horizontal lines there is a chance to do a memcpy?
    if (dy == 0) // Line is horizontal
    {
        if (x2 < x1)
            std::swap(x1, x2);
        for (x = x1; x <= x2; x++)
            if (rol())
                Draw(x, y1, color);
        return;
    }

    // Line is Funk-aye
    dx1 = abs(dx);
    dy1 = abs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }

        if (rol())
            Draw(x, y, color);

        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0)
                px = px + 2 * dy1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    y = y + 1;
                else
                    y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            if (rol())
                Draw(x, y, color);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }

        if (rol())
            Draw(x, y, color);

        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    x = x + 1;
                else
                    x = x - 1;
                py = py + 2 * (dx1 - dy1);
            }
            if (rol())
                Draw(x, y, color);
        }
    }
}

void
CRenderer::DrawRectangle(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color, uint32_t pattern)
{
    for (int32_t y1 = y; y1 < y + height; y1++) {
            DrawLine(x, y1, x + width, y1, color, pattern);
    }
}

/**
 * Wraps Coordinates into a toroidal map
 *
 * Makes it so when the input coordenate of is not inside the
 * ColorBuffer it will wrap the coordinates to the other side
 * of the buffer.
 *
 * @param ix X input coordinate
 * @param iy Y input coordinate
 * @param ox X output coordinate
 * @param oy Y output coordinate
 */
void
CRenderer::WrapCoordinates(float ix, float iy, float &ox, float &oy)
{
    ox = ix;
    oy = iy;

    if (ix < 0.0f) ox = ix + (float)mWidth;
    if (ix >= mWidth) ox = ix - (float)mWidth;

    if (iy < 0.0f) oy = iy + (float)mHeight;
    if (iy >= mHeight) oy = iy - (float)mHeight;
}