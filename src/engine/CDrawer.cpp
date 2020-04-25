#include "CDrawer.h"

#include <engine/CWindow.h>

CDrawer::CDrawer(CWindow *window) {
    mWindow = window;
    colorBuffer = mWindow->GetRenderer().GetColorBuffer();
    width = mWindow->GetRenderer().GetWidth();
    height = mWindow->GetRenderer().GetHeight();
    resolution = width * height;
}

CDrawer::~CDrawer() {
}

void
CDrawer::Clear(ColorI color) {
    memset(colorBuffer, (uint32_t) color, sizeof(uint32_t) * resolution);
}

void
CDrawer::Draw(uint32_t x, uint32_t y, ColorI color) {
    // this method in the future, will implement the color with
    // a different type, with it, we will be able tos p
}

void
CDrawer::SetPixel(uint32_t x, uint32_t y, ColorI color) {
    colorBuffer[y * width + x] =  color;
}