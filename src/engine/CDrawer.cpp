#include "CDrawer.h"

#include <engine/CWindow.h>

CDrawer::CDrawer(CWindow *window) {
    mWindow = window;
}

CDrawer::~CDrawer() {
}

void
CDrawer::Fill(uint32_t color) {
    memset(mWindow, color, sizeof(uint32_t)*sizeof(mWindow));
}