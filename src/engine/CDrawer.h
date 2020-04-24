#pragma once

#include <cstdint>
#include <engine/CColor.h>

class CWindow;

class CDrawer
{
public:
    CDrawer(CWindow *window);
    ~CDrawer();

    void Clear(ColorI color);
    void Draw(uint32_t x, uint32_t y, ColorI color);

protected:
    CWindow *mWindow { nullptr };
    uint32_t *colorBuffer { nullptr };

private:
    uint32_t resolution;
    uint32_t width;
    uint32_t height;

    void SetPixel(uint32_t x, uint32_t y, ColorI color);
};