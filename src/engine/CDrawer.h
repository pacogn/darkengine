#pragma once

#include <cstdint>

class CWindow;

class CDrawer
{
public:
    CDrawer(CWindow *window);
    ~CDrawer();

    void Fill(uint32_t color);
    int resolution;

protected:
    CWindow *mWindow { nullptr };
    uint32_t *colorBuffer { nullptr };
};