#include "CDrawer.h"

#include <engine/CWindow.h>

CDrawer::CDrawer(CWindow *window) {
    mWindow = window;
    colorBuffer = mWindow->GetRenderer().GetColorBuffer();
    resolution = mWindow->GetRenderer().GetWidth() * mWindow->GetRenderer().GetHeight();
}

CDrawer::~CDrawer() {
}

void
CDrawer::Fill(uint32_t color) {
    memset(colorBuffer, color, sizeof(uint32_t) * resolution);
}