#include "CRenderer.h"
//-------------------------------------
#include <Core/memory/memory.h>
#include <engine/CRenderer.h>
#include <Common/Math/math_funcs.h>
//-------------------------------------
#include <memory.h>
#include <stdlib.h>
#include <vector>

using namespace MindShake;
using namespace std;

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
    SetPixel(x, y, color);
};

//-------------------------------------
void
CRenderer::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color, uint32_t pattern) {
    int32_t i, length;
    int32_t dx, dy;

    length = Abs(x2 - x1);
    if (Abs(y2 - y1) > length) {
        length = Abs(y2 - y1);
    }
    if (length == 0) {
        return;
    }

    dx = ((x2 - x1) << 16) / length;
    dy = ((y2 - y1) << 16) / length;
    x1 <<= 16;
    y1 <<= 16;
    for (i = 0; i < length; ++i) {
        pattern = (pattern << 1) | (pattern >> 31);
        if(pattern & 1) {
            Draw(x1 >> 16, y1 >> 16, color);
        }
        x1 += dx;
        y1 += dy;
    }
}


//-------------------------------------
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

void
CRenderer::DrawWireframeModel(
    const vector<pair<float, float>> &vecModelCoordinates,
    float x, float y,
    float a,
    float s,
    uint32_t color 
)
{
    vector<pair<float, float>> vecTransformedCoordinates;
    int verts = vecModelCoordinates.size();
    vecTransformedCoordinates.resize(verts);

    // Order matters
    // 1. Rotate
    for (int i = 0; i < verts; i++)
    {
        vecTransformedCoordinates[i].first  = vecModelCoordinates[i].first * Cos(a) - vecModelCoordinates[i].second * Sin(a);
        vecTransformedCoordinates[i].second = vecModelCoordinates[i].first * Sin(a) + vecModelCoordinates[i].second * Cos(a);
    }

    // 2. Scaling
    for (int i = 0; i < verts; i++)
    {
        vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first * s;
        vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second * s;
    }

    // 3. Translate
    for (int i = 0; i < verts; i++)
    {
        vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
        vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;
    }

    for (int i = 0; i < verts+1; i++)
    {
        int j = (i + 1);
        CRenderer::DrawLine(
            vecTransformedCoordinates[i % verts].first, vecTransformedCoordinates[i % verts].second,
            vecTransformedCoordinates[j % verts].first, vecTransformedCoordinates[j % verts].second,
            color
        );
    }
}