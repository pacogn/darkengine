#pragma once

#include <cstdint>

class CWindow;

class CDrawer
{
public:
    CDrawer(CWindow *window);
    ~CDrawer();

    void Fill(uint32_t color);

protected:
    CWindow *mWindow { nullptr };
};